#include <gtest/gtest.h>
#include "display.h"

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
