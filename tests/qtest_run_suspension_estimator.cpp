#include "inc/qtest_run_suspension_estimator.h"

QTestRunSuspensionEstimator::QTestRunSuspensionEstimator(QObject *parent) : QObject(parent) {

}


void QTestRunSuspensionEstimator::testRunStep_1() {

    RunSuspensionEstimator run_suspension_estimator;

    std::string data = "101:45,23,11,55,32,11";

    shared_ptr<KFPassiveSuspension> suspension_estimator = make_shared<KFPassiveSuspension>( );
    shared_ptr<InputParser> parser = make_shared<InputParser>();

    std::string response = run_suspension_estimator.step(data, suspension_estimator, parser);
}




