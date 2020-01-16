#include <Servo.h>

// Prepare the servo/actuators object
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

// Define the analog input pin to measure flex sensor position:
const int flexpin1 = 4;
const float SR1 = 25791.85; // This can be changed
const float BR1 = 16186.11; // This can be changed

const int flexpin2 = 3;
const float SR2 = 2134.84; // This can be changed
const float BR2 = 1141.14; // This can be changed

const int flexpin3 = 2;
const float SR3 = 802.68; // This can be changed
const float BR3 = 1732.52; // This can be changed

const int flexpin4 = 1;
const float SR4 = 2750.77; // This can be changed
const float BR4 = 2647.06; // This can be changed

const int flexpin5 = 0;
const float SR5 = 6611.91; // This can be changed
const float BR5 = 4526.23; // This can be changed

// Ressitance value and VCC
const float VCC = 4.98;
const float R_DIV = 47500.0;

void setup() {
  // Prepare Serial for logging
  Serial.begin(9600);

  // Configure all pins
  pinMode(flexpin1, INPUT);
  pinMode(flexpin2, INPUT);
  pinMode(flexpin3, INPUT);
  pinMode(flexpin4, INPUT);
  pinMode(flexpin5, INPUT);

  // Attach all servo motors
  servo1.attach(3);
  servo2.attach(4);
  servo3.attach(5);
  servo4.attach(6);
  servo5.attach(8);
}

void loop() {
  // Read flex inputs
  int flexposition1 = analogRead(flexpin1); // Input value from the analog pin.
  int flexposition2 = analogRead(flexpin2); // Input value from the analog pin.
  int flexposition3 = analogRead(flexpin3); // Input value from the analog pin.
  int flexposition4 = analogRead(flexpin4); // Input value from the analog pin.
  int flexposition5 = analogRead(flexpin5); // Input value from the analog pin.

  // Convert the flex reading to wider range ohms
  float flexV1 = flexposition1 * VCC / 1023.0;
  float flexR1 = R_DIV * (VCC / flexV1 - 1.0);

  float flexV2 = flexposition2 * VCC / 1023.0;
  float flexR2 = R_DIV * (VCC / flexV2 - 1.0);

  float flexV3 = flexposition3 * VCC / 1023.0;
  float flexR3 = R_DIV * (VCC / flexV3 - 1.0);

  float flexV4 = flexposition4 * VCC / 1023.0;
  float flexR4 = R_DIV * (VCC / flexV4 - 1.0);

  float flexV5 = flexposition5 * VCC / 1023.0;
  float flexR5 = R_DIV * (VCC / flexV5 - 1.0);
  // End conversions

  //Map al flex readings to degree and constrain to 180 degrees rotation
  int servoposition1 = map(flexR1, SR1, BR1, 0, 180);;   // Output value to the servo.
  servoposition1 = constrain(servoposition1, 0, 180);

  int servoposition2 = map(flexR2, SR2, BR2, 180, 0);;   // Output value to the servo.
  servoposition2 = constrain(servoposition2, 0, 180);
  if(servoposition2 > 140) servoposition2 = 140;

  int servoposition3 = map(flexR3, SR3, BR3, 180, 0);;   // Output value to the servo.
  servoposition3 = constrain(servoposition3, 0, 180);

  int servoposition4 = map(flexR4, SR4, BR4, 180, 0);;   // Output value to the servo.
  servoposition4 = constrain(servoposition4, 0, 180);

  int servoposition5 = map(flexR5, SR5, BR5, 180, 0);;   // Output value to the servo.
  servoposition5 = constrain(servoposition5, 0, 180);
  // End mapping.

  // Write positions to the servo motors or actuators
  servo1.write(servoposition1);
  servo2.write(servoposition2);
  servo3.write(servoposition3);
  servo4.write(servoposition4);
  servo5.write(servoposition5);
  // End writing

  // Log all informations
  Serial.print("----------------------------------------");
  Serial.print("\nsensor1: " + String(flexposition1));
  Serial.print(" flexR1: " + String(flexR1));
  Serial.print("  servo1: " + String(servoposition1));
  Serial.print("\n");
  
  Serial.print("sensor2: " + String(flexposition2));
  Serial.print(" flexR2: " + String(flexR2));
  Serial.print("  servo2: " + String(servoposition2));
  Serial.print("\n");
  
  Serial.print("sensor3: " + String(flexposition3));
  Serial.print(" flexR4: " + String(flexR3));
  Serial.print("  servo3: " + String(servoposition3));
  Serial.print("\n");
  
  Serial.print("sensor4: " + String(flexposition4));
  Serial.print(" flexR4: " + String(flexR4));
  Serial.print("  servo4: " + String(servoposition4));
  Serial.print("\n");
  
  Serial.print("sensor5: " + String(flexposition5));
  Serial.print(" flexR5: " + String(flexR5));
  Serial.print("  servo5: " + String(servoposition5));
  Serial.print("\n--------------------------------------------------------------------");
  // End logging
  
  // Delay loop for 500 millisecond
  delay(500);
}
