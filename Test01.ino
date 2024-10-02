const float RANGE_DEFAULT_1 = 528;
const float RANGE_DEFAULT_2 = 506;
const float RANGE_DEFAULT_3 = 532;
const float RANGE_DEFAULT_4 = 512;
const float THRESHOLD_1 = 0.01;
const float THRESHOLD_2 = 0.02;
const float THRESHOLD_3 = 0.02;
const float THRESHOLD_4 = 0.06;

char gear;
char buf[5];

void setup() {
  pinMode(A0, INPUT); /* Sensor left */
  pinMode(A1, INPUT); /* Sensor top */
  pinMode(A2, INPUT); /* Sensor right */
  pinMode(A3, INPUT); /* Sensor bottom */
  Serial.begin(9600);
  //clear display
}

void loop(){
  //Read signals
  int hall_value_1 = analogRead(A0); // 0 - 1023
  int hall_value_2 = analogRead(A3);
  int hall_value_3 = analogRead(A1);
  int hall_value_4 = analogRead(A2);

  
  //Normalize and decide signals
  float normalized_1 = normalize(hall_value_1, RANGE_DEFAULT_1);
  float normalized_2 = normalize(hall_value_2, RANGE_DEFAULT_2);
  float normalized_3 = normalize(hall_value_3, RANGE_DEFAULT_3);
  float normalized_4 = normalize(hall_value_4, RANGE_DEFAULT_4);

  bool decided_normalized_1 = decide(normalized_1, THRESHOLD_1);
  bool decided_normalized_2 = decide(normalized_2, THRESHOLD_2);
  bool decided_normalized_3 = decide(normalized_3, THRESHOLD_3);
  bool decided_normalized_4 = decide(normalized_4, THRESHOLD_4);

  //Combine into single gear position state
  char * state = toState(decided_normalized_1, decided_normalized_2, decided_normalized_3, decided_normalized_4);
  int binary_state = strtol(state, NULL, 2);

  //Signals to gear
  switch (binary_state) {
  case 0b1000:
    gear = '1';
    break;
  case 0b0001:
    gear = '2';
    break;
  case 0b1100:
    gear = '3';
    break;
  case 0b0011:
    gear = '4';
    break;
  case 0b0100:
    gear = '5';
    break;
  case 0b0010:
    gear = 'R';
    break;
  default:
    gear = 'N';
    
  }
  //Display gear
  

  // print("Raw Values:", hall_value_1, hall_value_2, hall_value_3, hall_value_4, "Normalized Values", normalized_1, normalized_2, normalized_3, normalized_4, "Decided Normalized Values:", decided_normalized_1, decided_normalized_2, decided_normalized_3, decided_normalized_4, ", State:", state, ", Gear:", gear);
  Serial.print(hall_value_1);
  Serial.print(" ");
  Serial.print(hall_value_2);
  Serial.print(" ");
  Serial.print(hall_value_3);
  Serial.print(" ");
  Serial.print(hall_value_4);
  Serial.print(" ");
  Serial.print(500);
  Serial.print(" ");
  Serial.println(600);

  delay(50);
}

template<typename... Args>
void print(Args... args) {
  ((Serial.print(args), Serial.print(" ")), ...);
  Serial.println();
}

float normalize(int sensor_value, float range_default){
  float shifted_value = sensor_value - range_default;
  float normalized_value = shifted_value / range_default;
  return normalized_value;
}

bool decide(float value, float threshold){
  return value >= threshold;

}

char * toState(bool value_1, bool value_2, bool value_3, bool value_4){
  char foo[5] = {
    value_1 ? '1' : '0',
    value_2 ? '1' : '0',
    value_3 ? '1' : '0',
    value_4 ? '1' : '0',
    '\0'
  };
  memcpy(buf,foo,5);
  return buf;
}