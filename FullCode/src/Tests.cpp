#include <Arduino.h>
#include "Constants.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "Tests.h"

void motorTest()
{
  // analogWrite(LEFT_MOTOR_A, 0);
  // analogWrite(LEFT_MOTOR_B, 0);
  // analogWrite(RIGHT_MOTOR_A, 0);
  // delay(50);
  // analogWrite(RIGHT_MOTOR_B, DEFAULT_SPEED);
  // clearDisplay();
  // display.print("right back");
  // display.display();
  // delay(2000);

  // analogWrite(LEFT_MOTOR_A, 0);
  // analogWrite(LEFT_MOTOR_B, 0);
  // analogWrite(RIGHT_MOTOR_B, 0);
  // delay(50);
  // analogWrite(RIGHT_MOTOR_A, DEFAULT_SPEED);
  // clearDisplay();
  // display.print("right forward");
  // display.display();
  // delay(2000);

  // analogWrite(LEFT_MOTOR_A, 0);
  // analogWrite(RIGHT_MOTOR_A, 0);
  // analogWrite(RIGHT_MOTOR_B, 0);
  // delay(50);
  // analogWrite(LEFT_MOTOR_B, DEFAULT_SPEED);
  // clearDisplay();
  // display.print("left back");
  // display.display();
  // delay(2000);

  // analogWrite(LEFT_MOTOR_B, 0);
  // analogWrite(RIGHT_MOTOR_A, 0);
  // analogWrite(RIGHT_MOTOR_B, 0);
  // delay(50);
  // analogWrite(LEFT_MOTOR_A, DEFAULT_SPEED);
  // clearDisplay();
  // display.print("left forward");
  // display.display();
  // delay(2000);
}

void oledTest()
{
  // delay(2000);
  // clearDisplay();
  // display.print("Hello, world!");
  // display.display();
}

void servoTest()
{
  //   for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 degree
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }
  // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }
}

void otherServoTest()
{
  // myservo.write(DEPOSIT_POSITION);
  // display.clearDisplay();
  // display.setCursor(0, 0);
  // display.println("deposit position");
  // display.display();
  // delay(2000);
  // myservo.write(CLOSED_POSITION);
  // display.clearDisplay();
  // display.setCursor(0, 0);
  // display.println("closed position");
  // display.display();
  // delay(2000);
}