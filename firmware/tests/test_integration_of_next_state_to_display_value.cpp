#include <gtest/gtest.h>
#include "command_type.h"
#include "state.h"

// Define struct for integration test cases
struct IntegrationTestCase {
    const char* message;
    SystemState prev_state;
    CommandType command;
    SensorData sensor_data;
    char expected_output;
};

SensorToGearMappings const EMPTY_MAP = SensorToGearMappings{
    {
        {'1', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
        {'2', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
        {'3', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
        {'4', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
        {'5', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
        {'R', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}}
    }
};

// Define test cases
IntegrationTestCase integration_test_cases[] = {
    {"Defaults to N in GEAR_DETECTION_MODE",
        {GEAR_DETECTION_MODE, WAITING, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        UNKNOWN_COMMAND,
        {{550, 550, 550, 550}},
        'N'
    },

    {"Detects gear correctly in GEAR_DETECTION_MODE",
        {GEAR_DETECTION_MODE, WAITING, ' ', EMPTY_MAP, {{
            {'1', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'2', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'3', {{500, 600}, {500, 600}, {500, 600}, {500, 600}}},
            {'4', {{300, 400}, {300, 400}, {300, 400}, {300, 400}}},
            {'5', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'R', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
        }}, 'N', ""},
        UNKNOWN_COMMAND,
        {{550, 550, 550, 550}},
        '3'
    },

    {"Detects gear correctly in GEAR_DETECTION_MODE",
        {GEAR_DETECTION_MODE, WAITING, ' ', EMPTY_MAP, {{
            {'1', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'2', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'3', {{500, 600}, {500, 600}, {500, 600}, {500, 600}}},
            {'4', {{300, 400}, {300, 400}, {300, 400}, {300, 400}}},
            {'5', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'R', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
        }}, 'N', ""},
        UNKNOWN_COMMAND,
        {{350, 350, 350, 350}},
        '4'
    },

    {"Starts calibration on START_CALIBRATION command",
        {GEAR_DETECTION_MODE, WAITING, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        START_CALIBRATION,
        {},
        'C'
    },

    {"Stops calibration on ABORT_CALIBRATION command",
        {CALIBRATION_MODE, RECORDING, '3', EMPTY_MAP, {{
            {'1', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'2', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'3', {{500, 600}, {500, 600}, {500, 600}, {500, 600}}},
            {'4', {{300, 400}, {300, 400}, {300, 400}, {300, 400}}},
            {'5', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'R', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
        }}, 'N', ""},
        ABORT_CALIBRATION,
        {{350, 350, 350, 350}},
        '4'
    },

    {"Handles transition from CALIBRATION_MODE to GEAR_DETECTION_MODE",
        {CALIBRATION_MODE, CALIBRATE, ' ', EMPTY_MAP, EMPTY_MAP, '2', ""},
        FINISH_CALIBRATION,
        {{350, 350, 350, 350}},
        'N'
    },

    {"Detects neutral gear correctly",
        {GEAR_DETECTION_MODE, WAITING, ' ', EMPTY_MAP, {{
            {'1', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'2', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'3', {{500, 600}, {500, 600}, {500, 600}, {500, 600}}},
            {'4', {{300, 400}, {300, 400}, {300, 400}, {300, 400}}},
            {'5', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'R', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
        }}, '1', ""},
        UNKNOWN_COMMAND,
        {{925, 925, 925, 925}},
        'N'
    },

    {"Detects reverse gear correctly",
        {GEAR_DETECTION_MODE, WAITING, ' ', EMPTY_MAP, {{
            {'1', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'2', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'3', {{500, 600}, {500, 600}, {500, 600}, {500, 600}}},
            {'4', {{300, 400}, {300, 400}, {300, 400}, {300, 400}}},
            {'5', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'R', {{900, 950}, {900, 950}, {900, 950}, {900, 950}}},
        }}, 'N', ""},
        UNKNOWN_COMMAND,
        {{925, 925, 925, 925}},
        'R'
    },
};

// Define test fixture
class IntegrationTest : public ::testing::TestWithParam<IntegrationTestCase> {};

// Parameterized test
TEST_P(IntegrationTest, HandlesStateTransitions) {
    const IntegrationTestCase& tc = GetParam();
    SCOPED_TRACE(tc.message);

    SystemState next = next_state(tc.prev_state, tc.command, tc.sensor_data);
    char display_value = to_display_value(next);

    EXPECT_EQ(display_value, tc.expected_output)
        << "Failure: Expected '" << tc.expected_output << "', but got '" << display_value << "'";
}

// Instantiate test cases
INSTANTIATE_TEST_SUITE_P(
    IntegrationTests,
    IntegrationTest,
    ::testing::ValuesIn(integration_test_cases)
);

// Entry point for GoogleTest
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
