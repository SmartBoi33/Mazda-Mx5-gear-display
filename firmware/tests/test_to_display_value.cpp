#include <gtest/gtest.h>
#include "state.h"

// Define struct for test cases
struct DisplayTestCase {
    const char* message;
    SystemState state;
    char expected_display;
};

// Define test cases for `to_display_value`
DisplayTestCase display_test_cases[] = {
    // default state
    {
        "Default state should display the gear",
        {GEAR_DETECTION_MODE, WAITING, '3', ""},
        '3'
    },
    // gear detection state
    {
        "GEAR_DETECTION_MODE with gear 'N' should display 'N'",
        {GEAR_DETECTION_MODE, WAITING, 'N', ""},
        'N'
    },
    {
        "GEAR_DETECTION_MODE with gear '1' should display '1'",
        {GEAR_DETECTION_MODE, RECORDING, '1', "some error message"},
        '1'
    },
    {
        "GEAR_DETECTION_MODE with gear '2' should display '2'",
        {GEAR_DETECTION_MODE, WAITING, '2', ""},
        '2'
    },
    {
        "GEAR_DETECTION_MODE with gear '3' should display '3'",
        {GEAR_DETECTION_MODE, CALIBRATE, '3', ""},
        '3'
    },
    {
        "GEAR_DETECTION_MODE with gear '4' should display '4'",
        {GEAR_DETECTION_MODE, WAITING, '4', "some error message"},
        '4'
    },
    {
        "GEAR_DETECTION_MODE with gear '5' should display '5'",
        {GEAR_DETECTION_MODE, RECORDING, '5', ""},
        '5'
    },
    {
        "GEAR_DETECTION_MODE with gear 'R' should display 'R'",
        {GEAR_DETECTION_MODE, CALIBRATE, 'R', "some error message"},
        'R'
    },
    // calibration mode
    {
        "CALIBRATION_MODE in WAITING should display 'C'",
        {CALIBRATION_MODE, WAITING, 'N', ""},
        'C'
    },
    {
        "CALIBRATION_MODE in RECORDING should display the set recording gear e.g. 'R'",
        {CALIBRATION_MODE, RECORDING, 'R', 'N', ""},
        'R'
    },
    {
        "CALIBRATION_MODE in RECORDING should display the set recording gear e.g. '1'",
        {CALIBRATION_MODE, RECORDING, '1', '4', "some error"},
        '1'
    },
    {
        "CALIBRATION_MODE in CALIBRATE should display 'C'",
        {CALIBRATION_MODE, CALIBRATE, 'N', ""},
        'C'
    },
    {
        "ERROR state should display 'E'",
        {ERROR, WAITING, 'N', "Some error"},
        'E'
    },
};

// Run test cases using GoogleTest
TEST(ToDisplayValueTest, DisplayMapping) {
    for (const auto& tc : display_test_cases) {
        char result = to_display_value(tc.state);
        EXPECT_EQ(result, tc.expected_display) << tc.message;
    }
}

// Entry point for GoogleTest
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
