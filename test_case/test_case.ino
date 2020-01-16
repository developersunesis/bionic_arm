#include <Servo.h>

// Prepare the servo/actuators object
Servo servo;

// Set analog input number
const int FLEX_PIN = 1;
const float VCC = 4.98;
const float R_DIV = 47500.0;

const float STRAIGHT_RESISTANCE = 233.30;
const float BEND_RESISTANCE = 186.46; 

void setup()
{
  Serial.begin(9600);
  pinMode(FLEX_PIN, INPUT);

  // set digital output number / servo motor number
  servo.attach(5);
}

void loop()
{
  int flexADC = analogRead(FLEX_PIN);
  Serial.println("Analog Read: " + String(flexADC));
  
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  Serial.println("Flex Resistance: " + String(flexR) + " ohms");

  float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 180, 0);
  angle = constrain(angle, 0, 180);
  servo.write(angle);
  
  Serial.println("Angle: " + String(angle) + " degrees");
  Serial.println();

  delay(1000);
}
