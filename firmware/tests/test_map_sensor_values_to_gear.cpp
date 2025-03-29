#include <gtest/gtest.h>
#include "gear.h"
#include "gear_mappings.h"

// Define the struct for test cases
struct TestCase {
    const char* message;
    SensorData sensor_data;
    char expected_gear;
};

// Define test cases correctly using `SensorData`
TestCase test_cases[] = {
    // Successful mapping
    {"For given sensor values {505, 525, 510, 535}, we expect First gear", {{505, 525, 510, 535}}, '1'},
    {"For given sensor values {516, 536, 495, 505}, we expect Second gear", {{516, 536, 495, 505}}, '2'},
    {"For given sensor values {527, 547, 505, 515}, we expect Third gear", {{527, 547, 505, 515}}, '3'},
    {"For given sensor values {538, 558, 520, 530}, we expect Fourth gear", {{538, 558, 520, 530}}, '4'},
    {"For given sensor values {549, 569, 535, 545}, we expect Fifth gear", {{549, 569, 535, 545}}, '5'},
    {"For given sensor values {520, 560, 490, 500}, we expect Reverse gear", {{520, 560, 490, 500}}, 'R'},

    // default mapping
    {"For given sensor values {400, 400, 400, 400}, which do not match any mappings, we expect the default gear", {{400, 400, 400, 400}}, 'N'},
    {"For given sensor values {600, 600, 600, 600}, which do not match any mappings, we expect the default gear", {{600, 600, 600, 600}}, 'N'},
    {"For given sensor values {450, 650, 350, 750}, which do not match any mappings, we expect the default gear", {{450, 650, 350, 750}}, 'N'}
};

SensorToGearMappings gear_mappings = {
    .mappings = {
        {'R', {{520, 530}, {550, 565}, {490, 500}, {500, 510}}},  // Reverse
        {'1', {{505, 515}, {520, 530}, {510, 520}, {530, 540}}},  // First Gear
        {'2', {{516, 526}, {531, 541}, {495, 505}, {500, 510}}},  // Second Gear
        {'3', {{527, 537}, {542, 552}, {505, 515}, {515, 525}}},  // Third Gear
        {'4', {{538, 548}, {553, 563}, {520, 530}, {525, 535}}},  // Fourth Gear
        {'5', {{549, 559}, {564, 574}, {535, 545}, {540, 550}}}   // Fifth Gear
    }
};

// Define a test fixture class for parameterized tests
class GearMappingTest : public ::testing::TestWithParam<TestCase> {};

// Define the parameterized test
TEST_P(GearMappingTest, MatchesExpectedGear) {
    const TestCase& tc = GetParam();
    EXPECT_EQ(map_sensor_values_to_gear(tc.sensor_data.values, gear_mappings.mappings), tc.expected_gear)
        << tc.message;
}

// Instantiate test cases
INSTANTIATE_TEST_SUITE_P(
    GearTests,  // Test suite name
    GearMappingTest,  // Fixture class
    ::testing::ValuesIn(test_cases)  // Pass test case array
);

// Entry point for GoogleTest
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
