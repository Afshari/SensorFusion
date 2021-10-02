

#include <gtest/gtest.h>
#include <QTest>

#include "tests/inc/gmock_input_parser.h"
#include "tests/inc/gmock_ekf_localization.h"
#include "tests/inc/gmock_pf_localization.h"
#include "tests/inc/gmock_kf_tracking.h"

#include "tests/inc/qtest_ekf_localization.h"
#include "tests/inc/qtest_run_localization.h"
#include "tests/inc/qtest_input_parser.h"
#include "tests/inc/qtest_kf_tracking.h"
#include "tests/inc/qtest_kf_passive_suspension.h"
#include "tests/inc/qtest_run_suspension_estimator.h"
#include "tests/inc/qtest_pf_object.h"
#include "tests/inc/qtest_pf_particle.h"

int main(int argc, char *argv[]) {


    QTestEKFLocalization q_ekf_localization;
    QTest::qExec(&q_ekf_localization);

    QTestRunLocalization q_run_localization;
    QTest::qExec(&q_run_localization);

    QTestInputParser q_input_parser;
    QTest::qExec(&q_input_parser);

    QTestKFTracking q_kf_tracking;
    QTest::qExec(&q_kf_tracking);

    QTestKFPassiveSuspension q_kf_passive_suspension;
    QTest::qExec(&q_kf_passive_suspension);

    QTestRunSuspensionEstimator q_run_suspension_estimator;
    QTest::qExec(&q_run_suspension_estimator);

    QTestPFObject q_pf_object;
    QTest::qExec(&q_pf_object);

    QTestPFParticle q_pf_particle;
    QTest::qExec(&q_pf_particle);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
