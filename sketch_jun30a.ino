#include <AFMotor.h>
#include <Servo.h>

// L293 Connection

// Bluetooth (HC-06 JY-MCU) State pin on pin 2 of Arduino
const int BTState = 2;
// Calculate Battery Level
const float maxBattery = 8.0; // Change value to your max battery voltage level!
int perVolt;                  // Percentage variable
float voltage = 0.0;          // Read battery voltage
int level;
// Use it to make a delay... without delay() function!
long previousMillis =
    -1000 * 10; // -1000*10=-10sec. to read the first value. If you use 0 then
                // you will take the first value after 10sec.
long interval = 1000 * 10; // interval at which to read battery voltage, change
                           // it if you want! (10*1000=10sec)
unsigned long currentMillis; // unsigned long currentMillis;
// Useful Variables
int i = 0;
int j = 0;
int state;
int vSpeed = 200; // Default speed, from 0 to 255
AF_DCMotor motor1(4);
Servo myservo; // create servo object to control a servo
int pos = 90;  // variable to store the servo position

void setup() {
  // Set pins as outputs:

  myservo.attach(10);

  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // Stop car when connection lost or bluetooth disconnected
  if (digitalRead(BTState) == LOW) {
    state = 'S';
  }

  // Save income data to variable 'state'
  if (Serial.available() > 0) {
    state = Serial.read();
  }

  // Change speed if state is equal from 0 to 4. Values must be from 0 to 255
  // (PWM)
  if (state == '0') {
    vSpeed = 0;
  } else if (state == '1') {
    vSpeed = 100;
  } else if (state == '2') {
    vSpeed = 180;
  } else if (state == '3') {
    vSpeed = 200;
  } else if (state == '4') {
    vSpeed = 255;
  }

  /***********************Forward****************************/
  // If state is equal with letter 'F', car will go forward!
  if (state == 'F') {
    motor1.run(FORWARD);
    motor1.setSpeed(vSpeed);

  }
  /**********************Forward Left************************/
  // If state is equal with letter 'G', car will go forward left
  else if (state == 'G') {
    motor1.run(FORWARD);
    motor1.setSpeed(vSpeed);
    myservo.write(10);
  }
  /**********************Forward Right************************/
  // If state is equal with letter 'I', car will go forward right
  else if (state == 'I') {
    motor1.run(FORWARD);
    motor1.setSpeed(vSpeed);
    myservo.write(150);
  }
  /***********************Backward****************************/
  // If state is equal with letter 'B', car will go backward
  else if (state == 'B') {
    motor1.run(BACKWARD);
    motor1.setSpeed(vSpeed);

  }
  /**********************Backward Left************************/
  // If state is equal with letter 'H', car will go backward left
  else if (state == 'H') {
    motor1.run(BACKWARD);
    motor1.setSpeed(vSpeed);
    myservo.write(10);

  }
  /**********************Backward Right************************/
  // If state is equal with letter 'J', car will go backward right
  else if (state == 'J') {
    motor1.run(BACKWARD);
    motor1.setSpeed(vSpeed);
    myservo.write(150);
  }
  /***************************Left*****************************/
  // If state is equal with letter 'L', wheels will turn left
  else if (state == 'L') {

    myservo.write(10);
    motor1.setSpeed(0);
  }
  /***************************Right*****************************/
  // If state is equal with letter 'R', wheels will turn right
  else if (state == 'R') {

    myservo.write(150);
    motor1.setSpeed(0);

    /************************Stop*****************************/
    // If state is equal with letter 'S', stop the car
    if (state == 'S') {
      myservo.write(90);
      motor1.setSpeed(0);
    }
    /***********************Battery*****************************/
    // Read battery voltage every 10sec.
    currentMillis = millis();
    if (currentMillis - (previousMillis) > (interval)) {
      previousMillis = currentMillis;
      // Read voltage from analog pin A0 and make calibration:
      voltage = (analogRead(A0) * 5.015 / 1024.0) * 11.132;
      // Calculate percentage...
      perVolt = (voltage * 100) / maxBattery;
      if (perVolt <= 75) {
        level = 0;
      } else if (perVolt > 75 && perVolt <= 80) {
        level = 1;
      } //        Battery level
      else if (perVolt > 80 && perVolt <= 85) {
        level = 2;
      } // Min ------------------------   Max
      else if (perVolt > 85 && perVolt <= 90) {
        level = 3;
      } //    | 0 | 1 | 2 | 3 | 4 | 5 | >
      else if (perVolt > 90 && perVolt <= 95) {
        level = 4;
      } //    ------------------------
      else if (perVolt > 95) {
        level = 5;
      }
      Serial.println(level);
    }
  }
}
