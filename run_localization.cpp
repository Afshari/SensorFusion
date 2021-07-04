#include "inc/run_localization.h"

RunLocalization::RunLocalization(QObject *parent) : QObject(parent) {

}


void RunLocalization::step(const string &data, const shared_ptr<EKFLocalization>& ekf,
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
        unique_ptr<VectorXd> u = parser->getLocalizationControlInput(data, start_index, len);

        ekf->predict( u );

        start_index = (*indices)[2];
        len = (*indices)[3] - (*indices)[2] - 1;
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


























