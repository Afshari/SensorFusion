

#include <gtest/gtest.h>
#include <QTest>

#include "tests/inc/ekf_test.h"
#include "tests/inc/qtest_ekf_localization.h"

int main(int argc, char *argv[]) {

//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();


    QTestEKFLocalization q_ekf_localization;
    QTest::qExec(&q_ekf_localization);


}
