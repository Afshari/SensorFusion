
#if RUN_STATUS == RUN_APP || RUN_STATUS == RUN_DEBUG

#include <QCoreApplication>

#elif RUN_STATUS == RUN_TEST

#include "ekf_test.h"
#include <gtest/gtest.h>

#endif

int main(int argc, char *argv[])
{

#if RUN_STATUS == RUN_APP || RUN_STATUS == RUN_DEBUG

    QCoreApplication a(argc, argv);

    return a.exec();

#elif RUN_STATUS == RUN_TEST

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

#endif

}
