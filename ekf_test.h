#ifndef TST_EKF_TEST_H
#define TST_EKF_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(efk_test, ekf_test)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

#endif // TST_EKF_TEST_H
