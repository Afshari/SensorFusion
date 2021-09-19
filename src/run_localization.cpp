#include "inc/run_localization.h"

RunLocalization::RunLocalization(QObject *parent) : QObject(parent) {

}


void RunLocalization::step(const string &data,
                           const shared_ptr<EKFLocalization>& ekf,
                           const shared_ptr<InputParser>& parser) {

    int code = parser->getCode(data);
    shared_ptr<vector<int>> indices = parser->getIndices( data, ":" );

    if(code == 100) {

        int start_index = (*indices)[1];
        int len = (*indices)[2] - (*indices)[1] - 1;

        shared_ptr<map<string, float>> params = parser->getLocalizationParams(data, start_index, len);

        ekf->setParams( (*params)["std_vel"],     (*params)["std_steer"],   (*params)["std_range"],
                        (*params)["std_bearing"], (*params)["start_angle"], (*params)["prior_cov_pos"],
                        (*params)["prior_cov_angle"] );

        start_index = (*indices)[3];
        len = data.length() - (*indices)[3];
        shared_ptr<vector<Vector2d>> landmarks = parser->getObservations(data, start_index, len);
        ekf->setLandmarks( landmarks );
    }


    if(code == 100 || code == 101) {

        int start_index = (*indices)[1];
        int len = (*indices)[2] - (*indices)[1] - 1;
        shared_ptr<VectorXd> u = parser->getLocalizationControlInput(data, start_index, len);

        ekf->predict( u );

        if(code == 100) {
            start_index = (*indices)[2];
            len = (*indices)[3] - (*indices)[2] - 1;
        } else if(code == 101) {
            start_index = (*indices)[1];
            len = data.length() - (*indices)[1];
        }

        shared_ptr<vector<Vector2d>> observations = parser->getObservations(data, start_index, len);
        shared_ptr<vector<Vector2d>> landmarks = ekf->getLandmarks();

        for(auto i = 0U; i < observations->size(); i++) {

            auto lnd = landmarks->at(i);
            auto obs = observations->at(i);

            ekf->update( make_unique<VectorXd>( obs ),
                         make_unique<VectorXd>( lnd ) );
        }
    }

}


void RunLocalization::step(const string &data,
                           const shared_ptr<PFLocalization>&  pf,
                           const shared_ptr<InputParser>& parser) {

    bool isValid;
    string curr_data;
    tie(isValid, curr_data) = parser->checkInput(data);

    if(isValid == false) {
        std::cout << "Corrupted" << std::endl;
        return;
    }

    int code = parser->getCode(curr_data);
    auto indices = parser->getIndices( curr_data, ":" );

    if(code == 100) {

        int start_index = (*indices)[1];
        int len =  curr_data.length() - (*indices)[1];

        shared_ptr<Vector3d> params = parser->getPFLocalizationParams(curr_data, start_index, len);
        pf->setRobotParam(params);
        pf->generateParticles();
    }


    if(code == 101) {

        int start_index = (*indices)[1];
        int len = (*indices)[2] - (*indices)[1] - 1;
        shared_ptr<VectorXd> u = parser->getLocalizationControlInput(curr_data, start_index, len);
        // std::cout << "u: " << *u << std::endl;

        start_index = (*indices)[2];
        len = (*indices)[3] - (*indices)[2] - 1;
        shared_ptr<vector<Vector2d>> robotMeas = parser->getLocalizationMeasurements(curr_data, start_index, len);
        pf->setRobotMeasurements(robotMeas);

        start_index = (*indices)[3];
        len = curr_data.length() - (*indices)[3];
        string particles_measurements_str = curr_data.substr(start_index, len);
        auto particles_indices = parser->getIndices( particles_measurements_str, ";" );

        for(uint i = 0; i < particles_indices->size(); i++) {
            shared_ptr<vector<Vector2d>> meas;
            if(i < particles_indices->size() - 1) {
                meas = parser->getLocalizationMeasurements(
                            particles_measurements_str,
                            particles_indices->at(i),
                            particles_indices->at(i + 1) - particles_indices->at(i) - 1 );
            } else {
                meas = parser->getLocalizationMeasurements(
                            particles_measurements_str,
                            particles_indices->at(i),
                            particles_measurements_str.length() - particles_indices->at(i) );
            }
            pf->setParticleMeasurements(i, meas);
            pf->updateParticleWeight(i, robotMeas);
        }

        pf->resample();
        pf->robotMove((*u)[0], (*u)[1]);
        for(uint i = 0; i < pf->numberOfParticles(); i++) {
            pf->predictParticle(i, (*u)[0], (*u)[1]);
        }
    }

}
























