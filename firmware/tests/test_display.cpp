#include <gtest/gtest.h>
#include "display.h"

TEST(RefreshRateTest, Hertz1) {
    EXPECT_EQ(get_delay_for_refresh_rate(1), 1000);
}

TEST(RefreshRateTest, Hertz10) {
    EXPECT_EQ(get_delay_for_refresh_rate(10), 100);
}

TEST(RefreshRateTest, Hertz25) {
    EXPECT_EQ(get_delay_for_refresh_rate(25), 40);
}

TEST(RefreshRateTest, Hertz30) {
    EXPECT_EQ(get_delay_for_refresh_rate(30), 33);
}

TEST(RefreshRateTest, Hertz60) {
    EXPECT_EQ(get_delay_for_refresh_rate(60), 16);
}

TEST(RefreshRateTest, Hertz120) {
    EXPECT_EQ(get_delay_for_refresh_rate(120), 8);
}

// Test should_rerender function
TEST(ShouldRerenderTest, DifferentGears) {
    ASSERT_TRUE(should_rerender('1', 'N'));  // Different gears should rerender
}

TEST(ShouldRerenderTest, SameGear) {
    ASSERT_FALSE(should_rerender('1', '1'));  // Same gear should not rerender
}

// Entry point for the GoogleTest framework
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
