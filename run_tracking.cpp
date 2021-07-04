#include "inc/run_tracking.h"

RunTracking::RunTracking(QObject *parent) : QObject(parent) {

}


void RunTracking::step(const string &data,
                       const shared_ptr<KFTracking>& kf, const shared_ptr<InputParser>& parser) {

    int code = parser->getCode(data);
    shared_ptr<vector<int>> indices = parser->getIndices( data, ":" );

    if(code == 100) {

        int start_index = (*indices)[2];
        int len         = (*indices)[3] - (*indices)[2] - 1;

        shared_ptr<map<string, float>> params = parser->getTrackingParams(data, start_index, len);

        kf->init( (*params)["init_x"], (*params)["init_y"], (*params)["std_x"],
                  (*params)["std_y"],  (*params)["dt"],     (*params)["process_noise"] );
    }

    if(code == 100 || code == 101) {

        int start_index = (*indices)[1];
        int len         = (*indices)[2] - (*indices)[1] - 1;
        unique_ptr<VectorXd> z = parser->getTrackingInput(data, start_index, len);

        kf->predict();
        kf->update( z );
    }
}




