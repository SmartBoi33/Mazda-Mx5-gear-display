#include <gtest/gtest.h>
#include <limits.h>
#include "command_type.h"
#include "state.h"

// Define struct for test cases
struct TestCase {
    const char* message;
    SystemState initial_state;
    CommandType command;
    SensorData sensor_data;
    SystemState expected_state;
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

TestCase test_cases[] = {
    {"Given GEAR_DETECTION_MODE, and an UNKNOWN_COMMAND, we expect to detect the correct gear based on the set mapping",
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
        {GEAR_DETECTION_MODE, WAITING, ' ', EMPTY_MAP, {{
            {'1', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'2', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'3', {{500, 600}, {500, 600}, {500, 600}, {500, 600}}},
            {'4', {{300, 400}, {300, 400}, {300, 400}, {300, 400}}},
            {'5', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'R', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
        }}, '3', ""}},

    {"Given GEAR_DETECTION_MODE and the command START_CALIBRATION  the next state should be CALIBRATION_MODE",
        {GEAR_DETECTION_MODE, WAITING, 'N', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        START_CALIBRATION,
        {},
        {CALIBRATION_MODE, WAITING, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of WAITING, the command ABORT_CALIBRATION,  the next state should be GEAR_DETECTION_MODE",
        {CALIBRATION_MODE, WAITING, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        ABORT_CALIBRATION,
        {},
        {GEAR_DETECTION_MODE, WAITING, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of RECORDING, the command ABORT_CALIBRATION,  the next state should be GEAR_DETECTION_MODE and reset the calibration mode state to WAITING",
        {CALIBRATION_MODE, RECORDING, 'N', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        ABORT_CALIBRATION,
        {},
        {GEAR_DETECTION_MODE, WAITING, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of CALIBRATE, the command ABORT_CALIBRATION, the next state should be GEAR_DETECTION_MODE and reset the calibration mode state to WAITING",
        {CALIBRATION_MODE, CALIBRATE, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        ABORT_CALIBRATION,
        {},
        {GEAR_DETECTION_MODE, WAITING, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""}},

    // Recording gear mappings for each gear
    {"Given CALIBRATION_MODE, the calibration mode state of WAITING, the command RECORD_GEAR_4, the next state should be CALIBRATION_MODE for RECORDING and the recorded gear 4",
        {CALIBRATION_MODE, WAITING, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        RECORD_GEAR_4,
        {},
        {CALIBRATION_MODE, RECORDING, '4', EMPTY_MAP, EMPTY_MAP, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of WAITING, the command RECORD_GEAR_1, the next state should be CALIBRATION_MODE for RECORDING and the recorded gear 1",
        {CALIBRATION_MODE, WAITING, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        RECORD_GEAR_1,
        {},
        {CALIBRATION_MODE, RECORDING, '1', EMPTY_MAP, EMPTY_MAP, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of WAITING, the command RECORD_GEAR_2, the next state should be CALIBRATION_MODE for RECORDING and the recorded gear 2",
        {CALIBRATION_MODE, WAITING, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        RECORD_GEAR_2,
        {},
        {CALIBRATION_MODE, RECORDING, '2', EMPTY_MAP, EMPTY_MAP, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of WAITING, the command RECORD_GEAR_3, the next state should be CALIBRATION_MODE for RECORDING and the recorded gear 3",
        {CALIBRATION_MODE, WAITING, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        RECORD_GEAR_3,
        {},
        {CALIBRATION_MODE, RECORDING, '3', EMPTY_MAP, EMPTY_MAP, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of WAITING, the command RECORD_GEAR_4, the next state should be CALIBRATION_MODE for RECORDING and the recorded gear 4",
        {CALIBRATION_MODE, WAITING, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        RECORD_GEAR_4,
        {},
        {CALIBRATION_MODE, RECORDING, '4', EMPTY_MAP, EMPTY_MAP, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of WAITING, the command RECORD_GEAR_5, the next state should be CALIBRATION_MODE for RECORDING and the recorded gear 5",
        {CALIBRATION_MODE, WAITING, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        RECORD_GEAR_5,
        {},
        {CALIBRATION_MODE, RECORDING, '5', EMPTY_MAP, EMPTY_MAP, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of WAITING, the command RECORD_GEAR_R, the next state should be CALIBRATION_MODE for RECORDING and the recorded gear R",
        {CALIBRATION_MODE, WAITING, ' ', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        RECORD_GEAR_R,
        {},
        {CALIBRATION_MODE, RECORDING, 'R', EMPTY_MAP, EMPTY_MAP, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of RECORDING, any recording gear, the command STOP_GEAR_RECORDING, the next state should be CALIBRATION_MODE for WAITING and we reset the recorded gear",
        {CALIBRATION_MODE, RECORDING, '3', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        STOP_GEAR_RECORDING,
        {},
        {CALIBRATION_MODE, WAITING, '3', EMPTY_MAP, EMPTY_MAP, 'N', ""}},

    // ALL ABOUT RECORDING DATA
    {"Given CALIBRATION_MODE, the calibration mode state of RECORDING, any recording gear, and the UNKNOWN_COMMAND command, the next state should hold the recorded data for the gear we are recording for",
        {CALIBRATION_MODE, RECORDING, '3', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        UNKNOWN_COMMAND,
        {{500, 500, 500, 500}},
        {CALIBRATION_MODE, RECORDING, '3', {{
            {'1', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'2', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'3', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'4', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'5', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'R', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}}
        }}, EMPTY_MAP, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of RECORDING, the command RECORD_GEAR_R, and recording gear 3, the next state should still be the previous state",
        {CALIBRATION_MODE, RECORDING, '3', EMPTY_MAP, EMPTY_MAP, 'N', ""},
        RECORD_GEAR_R,
        {{500, 500, 500, 500}},
        {CALIBRATION_MODE, RECORDING, '3', {{
            {'1', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'2', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'3', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'4', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'5', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'R', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}}
        }}, EMPTY_MAP, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of RECORDING, with new sensor values, the next state should hold the updated recorded data as expected",
        {CALIBRATION_MODE, RECORDING, '3', {{
            {'1', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'2', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'3', {{500, 500}, {500, 500}, {500, 500}, {500, 500}}},
            {'4', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'5', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'R', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}}
        }}, EMPTY_MAP, 'N', ""},
        UNKNOWN_COMMAND,
        {{400, 600, 550, 500}},
        {CALIBRATION_MODE, RECORDING, '3', {{
            {'1', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'2', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'3', {{400, 500}, {500, 600}, {500, 550}, {500, 500}}},
            {'4', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'5', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'R', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}}
        }}, EMPTY_MAP, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of RECORDING, with new sensor values, the next state should hold the updated recorded data as expected",
        {CALIBRATION_MODE, RECORDING, '3', {{
            {'1', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'2', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'3', {{400, 500}, {500, 600}, {500, 550}, {500, 500}}},
            {'4', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'5', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'R', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}}
        }}, EMPTY_MAP, 'N', ""},
        UNKNOWN_COMMAND,
        {{600, 400, 530, 500}},
        {CALIBRATION_MODE, RECORDING, '3', {{
            {'1', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'2', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'3', {{400, 600}, {400, 600}, {500, 550}, {500, 500}}},
            {'4', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'5', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'R', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}}
        }}, EMPTY_MAP, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of RECORDING, and the FINISH_CALIBRATION command, we write the mapping as the new mapping in state disregarding the new sensor values",
        {CALIBRATION_MODE, RECORDING, '3', {{
            {'1', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'2', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'3', {{400, 600}, {400, 600}, {500, 550}, {500, 500}}},
            {'4', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'5', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'R', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}}
        }}, EMPTY_MAP, 'N', ""},
        FINISH_CALIBRATION,
        {{230, 400, 456, 700}},
        {CALIBRATION_MODE, CALIBRATE, ' ', {{
            {'1', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'2', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'3', {{400, 600}, {400, 600}, {500, 550}, {500, 500}}},
            {'4', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'5', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'R', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}}
        }}, {{
            {'1', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'2', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'3', {{400, 600}, {400, 600}, {500, 550}, {500, 500}}},
            {'4', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'5', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'R', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}}
        }}, 'N', ""}},

    {"Given CALIBRATION_MODE, the calibration mode state of CALIBRATE, and the FINISH_CALIBRATION command, we exit the calibration mode and enter the gear detection mode",
        {CALIBRATION_MODE, CALIBRATE, ' ', {{
            {'1', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'2', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'3', {{400, 600}, {400, 600}, {500, 550}, {500, 500}}},
            {'4', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'5', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'R', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}}
        }}, {{
            {'1', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'2', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'3', {{400, 600}, {400, 600}, {500, 550}, {500, 500}}},
            {'4', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'5', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'R', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}}
        }}, 'N', ""},
        FINISH_CALIBRATION,
        {{230, 400, 456, 700}},
        {GEAR_DETECTION_MODE, WAITING, ' ', EMPTY_MAP, {{
            {'1', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'2', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'3', {{400, 600}, {400, 600}, {500, 550}, {500, 500}}},
            {'4', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'5', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'R', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}}
        }}, 'N', ""}},
};


// Define a test fixture for parameterized tests
class NextStateTest : public ::testing::TestWithParam<TestCase> {};

// Parameterized test
TEST_P(NextStateTest, HandlesStateTransitions) {
    const TestCase& tc = GetParam();
    SCOPED_TRACE(tc.message);  // ✅ Ensures `tc.message` is displayed for every assertion.

    SystemState result = next_state(tc.initial_state, tc.command, tc.sensor_data);

    EXPECT_EQ(result.mode, tc.expected_state.mode)
        << "Failure in Mode Transition: Expected mode " << tc.expected_state.mode
        << ", but got " << result.mode;

    EXPECT_EQ(result.calibration, tc.expected_state.calibration)
        << "Failure in Calibration State: Expected " << tc.expected_state.calibration
        << ", but got " << result.calibration;

    EXPECT_EQ(result.recording_gear, tc.expected_state.recording_gear)
        << "Failure in Recording Gear: Expected '" << tc.expected_state.recording_gear
        << "', but got '" << result.recording_gear << "'";

    EXPECT_EQ(result.current_gear, tc.expected_state.current_gear)
        << "Failure in Current Gear: Expected '" << tc.expected_state.current_gear
        << "', but got '" << result.current_gear << "'";

    EXPECT_STREQ(result.error_message, tc.expected_state.error_message)
        << "Failure in Error Message: Expected \"" << tc.expected_state.error_message
        << "\", but got \"" << result.error_message << "\"";

    // ✅ Validate recording_data mappings
    for (size_t i = 0; i < NUMBER_OF_GEARS; i++) {
        EXPECT_EQ(result.recording_data.mappings[i].gear, tc.expected_state.recording_data.mappings[i].gear)
            << "Failure in Recording Data: Expected gear '" << tc.expected_state.recording_data.mappings[i].gear
            << "', but got '" << result.recording_data.mappings[i].gear << "'";

        for (size_t j = 0; j < NUMBER_OF_SENSORS; j++) {
            EXPECT_EQ(result.recording_data.mappings[i].sensor_ranges[j].min, tc.expected_state.recording_data.mappings[i].sensor_ranges[j].min)
                << "Failure in Recording Data (Min): Expected " << tc.expected_state.recording_data.mappings[i].sensor_ranges[j].min
                << ", but got " << result.recording_data.mappings[i].sensor_ranges[j].min;

            EXPECT_EQ(result.recording_data.mappings[i].sensor_ranges[j].max, tc.expected_state.recording_data.mappings[i].sensor_ranges[j].max)
                << "Failure in Recording Data (Max): Expected " << tc.expected_state.recording_data.mappings[i].sensor_ranges[j].max
                << ", but got " << result.recording_data.mappings[i].sensor_ranges[j].max;
        }
    }

    // ✅ Validate current_gear_mapping mappings
    for (size_t i = 0; i < NUMBER_OF_GEARS; i++) {
        EXPECT_EQ(result.current_gear_mapping.mappings[i].gear, tc.expected_state.current_gear_mapping.mappings[i].gear)
            << "Failure in Current Gear Mapping: Expected gear '" << tc.expected_state.current_gear_mapping.mappings[i].gear
            << "', but got '" << result.current_gear_mapping.mappings[i].gear << "'";

        for (size_t j = 0; j < NUMBER_OF_SENSORS; j++) {
            EXPECT_EQ(result.current_gear_mapping.mappings[i].sensor_ranges[j].min, tc.expected_state.current_gear_mapping.mappings[i].sensor_ranges[j].min)
                << "Failure in Current Gear Mapping (Min): Expected " << tc.expected_state.current_gear_mapping.mappings[i].sensor_ranges[j].min
                << ", but got " << result.current_gear_mapping.mappings[i].sensor_ranges[j].min;

            EXPECT_EQ(result.current_gear_mapping.mappings[i].sensor_ranges[j].max, tc.expected_state.current_gear_mapping.mappings[i].sensor_ranges[j].max)
                << "Failure in Current Gear Mapping (Max): Expected " << tc.expected_state.current_gear_mapping.mappings[i].sensor_ranges[j].max
                << ", but got " << result.current_gear_mapping.mappings[i].sensor_ranges[j].max;
        }
    }
}

// Instantiate test cases
INSTANTIATE_TEST_SUITE_P(
    StateTests,  // Test suite name
    NextStateTest,  // Fixture class
    ::testing::ValuesIn(test_cases)  // Pass test cases dynamically
);

// Entry point for GoogleTest
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
