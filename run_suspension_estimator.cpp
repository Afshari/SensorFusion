#include "inc/run_suspension_estimator.h"

RunSuspensionEstimator::RunSuspensionEstimator(QObject *parent) : QObject(parent) {

}

std::string RunSuspensionEstimator::step(const string &data,
                                  const shared_ptr<KFPassiveSuspension>& estimator, const shared_ptr<InputParser>& parser) {


    int code = parser->getCode(data);
    shared_ptr<vector<int>> indices = parser->getIndices( data, ":" );

    std::string response = "";
    std::ostringstream stringStream;

    if(code == 100 || code == 101) {

        int start_index = (*indices)[1];
        int len = (*indices)[2] - (*indices)[1] - 1;
        shared_ptr<vector<VectorXd>> observations = parser->getSuspensionObservations(data, start_index, len);

        for(auto z : *observations) {

            estimator->predict();
            estimator->update( make_unique<VectorXd>( z ) );

            shared_ptr<Vector4d> x = estimator->get_x();

            if(stringStream.str().empty() == false)
                stringStream << ";";

            stringStream << (*x)(0) << "," << (*x)(1);
        }

        return stringStream.str();
    }

    return "";
}
