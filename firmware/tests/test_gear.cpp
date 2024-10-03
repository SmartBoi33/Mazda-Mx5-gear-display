#include <gtest/gtest.h>
#include "gear.h"
#include "gear_mappings.h"

// Define the struct for test cases
struct TestCase {
    const char* message;
    int sensor_values[NUM_SENSORS];
    char expected_gear;
};

TestCase test_cases[] = {
    {"For given sensor values {537, 499, 538, 511}, we expect Neutral gear (Center)", {537, 499, 538, 511}, 'N'},
    {"For given sensor values {532, 504, 534, 508}, we expect Neutral gear (Left)", {532, 504, 534, 508}, 'N'},
    {"For given sensor values {536, 494, 537, 514}, we expect Neutral gear (Right)", {536, 494, 537, 514}, 'N'},
    {"For given sensor values {551, 490, 526, 517}, we expect First gear", {551, 490, 526, 517}, '1'},
    {"For given sensor values {528, 509, 522, 470}, we expect Second gear", {528, 509, 522, 470}, '2'},
    {"For given sensor values {553, 579, 528, 519}, we expect Third gear", {553, 579, 528, 519}, '3'},
    {"For given sensor values {529, 508, 564, 484}, we expect Fourth gear", {529, 508, 564, 484}, '4'},
    {"For given sensor values {551, 458, 524, 518}, we expect Fifth gear", {551, 458, 524, 518}, '5'},
    {"For given sensor values {529, 506, 567, 498}, we expect Reverse gear", {529, 506, 567, 498}, 'R'}
};

// Loop through each test case and run
TEST(GearMappingTest, TestGearMapping) {
    for (int i = 0; i < sizeof(test_cases) / sizeof(TestCase); ++i) {
        const TestCase& tc = test_cases[i];
        EXPECT_EQ(map_sensor_values_to_gear(tc.sensor_values, gear_mappings), tc.expected_gear) << tc.message;
    }
}

// Entry point for GoogleTest
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
