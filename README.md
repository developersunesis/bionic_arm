# Bionic Arm (using Gloves)
 A minute replication of the human arm

<hr/>

### DEFINITION
Bionic Arm means an artificial arm. This project is a very minute/minor replication of the human arm’s capability. We were able to successfully implement fingers movement.

This process was achieved using 3D printed arm (material used, Polylactic acid (PLA), micro controller (Arduino Nano), flex/bend sensors (as the input component) and servo motors/actuators (as the output component).

<em><b>3D-Printed Arm</b></em>: The arm was printed from the 3D models. Then coupled together. Find the 3D models here.

<em><b>Arduino Nano</b></em>: is a Nano module of Arduino (micro controller). This serves as the processing centre of the I/O components.

<em><b>Flex/Bend sensor</b></em>: is an analog component, we can obtain degrees of bend from this component up to 180 degrees.
Actuators/Servo motors: this an output component, it reads values in degrees and rotates by the speculated degree.

<hr/>

### HOW IT WORKS
The bend degree of the glove fingers (from the flex sensors which are attached on the gloves) are sent to the micro controller, (the reading ranges from analog components which includes flex sensor is 0 - 1024).

The values from each sensor (which is a number from 0- 1024) is mapped to degrees between and including 0 – 180. Then, the mapped value is written to the specified servo motor which then moves the finger its attached to.

This process is repeated continuously. See [Bionic Arm Project.pdf](/Bionic%20Arm%20Project.pdf) for diagram

<hr/>

### CIRCURT SIMULATION
![alt text](/simulation.png "Circuit simulation")

<hr/>

### Tools/Materials used
1. Arduino IDE
2. Micro controller (Arduino Nano) 3. 3D printed arm
3. 5 servo motors/actuators
4. 5 bend/flex sensors
5. 5 resistors
6. Double-Faced Circuit board
7. Six6-Wattbatteries
8. Heavy-duty glove
9. Fishing line
10. 3D printed arm

    Others
11. Jumper wires
12. Soldering Iron and solder
13. Glue gun
14. Probably scissors, pliers, screwdrivers and blade

##### Attached in the root folder of this document are:
bionic_arm
This directory contains the main code that controls the micro controller. And it’s the program currently been run on the micro controller.

Source: **bionic_arm/bionic_arm.ino**
```c++
#include <Servo.h>

// Prepare the servo/actuators object
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

// Define the analog input pin to measure flex sensor position:
const int flexpin1 = 4;
const float SR1 = 25791.85; 
const float BR1 = 16186.11; 

const int flexpin2 = 3;
const float SR2 = 2134.84; 
const float BR2 = 1141.14; 

const int flexpin3 = 2;
const float SR3 = 802.68; 
const float BR3 = 1732.52; 

const int flexpin4 = 1;
const float SR4 = 2750.77; 
const float BR4 = 2647.06; 

const int flexpin5 = 0;
const float SR5 = 6611.91; 
const float BR5 = 4526.23; 

// Resitance value and VCC
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
```
test_case
This directory contains the test code used to obtain the values of the flex sensor.

Source: **test_case.ino**
```c++
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

```
**ISSUES AND OBSERVATIONS**
See [Bionic Arm Project.pdf](/Bionic%20Arm%20Project.pdf)

#### LICENSE
```java
MIT License

Copyright (c) 2020 developersunesis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

```