#include <Arduino.h>
#include "Constants.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "Tests.h"
#include <stdio.h>
#include <Servo.h>
#define getName(var, str) sprintf(str, "%s", #var)

TwoWire Wire1(PB9, PB8); // Use STM32 I2C2
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);

int DEFAULT_SPEED = 165 -5; //reasign speed values
int MAX_SPEED = 205 -5;
int SLOW_SPEED = 110;

int pos = 0;
int stopCount = 0;
int startTime = 0;

int tapeSenseValue1 = 0;
int tapeSenseValue2 = 0;
int tapeSenseValue3 = 0;
int tapeSenseValue4 = 0;
int tapeSenseValue5 = 0;
int lastSensorHigh = 0;
int sweeperStatus = 0;
int leftMotorSpeed = 0;
int rightMotorSpeed = 0;
bool driveCalled = false;

Servo myservo;
void getAndPrintTapeSensorValuesAndSpeeds(int leftMotorSpeed, int rightMotorSpeed)
{
  tapeSenseValue1 = analogRead(TAPE_SENSOR_1);
  tapeSenseValue2 = analogRead(TAPE_SENSOR_2);
  tapeSenseValue3 = analogRead(TAPE_SENSOR_3);
  tapeSenseValue4 = analogRead(TAPE_SENSOR_4);
  tapeSenseValue5 = analogRead(TAPE_SENSOR_5);
  // debugging
  // display.clearDisplay();
  // display.setCursor(0, 0);
  // display.print("TSV 1:");
  // display.println(tapeSenseValue1);
  // display.print("TSV 2:");
  // display.println(tapeSenseValue2);
  // display.print("TSV 3:");
  // display.println(tapeSenseValue3);
  // display.print("TSV 4:");
  // display.println(tapeSenseValue4);
  // display.print("TSV 5:");
  // display.println(tapeSenseValue5);
  // display.print("LeftMotor:");
  // display.println(leftMotorSpeed);
  // display.print("RightMotor:");
  // display.println(rightMotorSpeed);
  // display.print("Sweeper Status: ");
  // if (sweeperStatus == 0)
  // {
  //   display.println("OFF");
  // }
  // else
  // {
  //   display.println("ON");
  // }
  // display.display();
}
void sweeperOn()
{
  pwm_start(SWEEPER_MOTOR_RIGHT, 1, 2000, TimerCompareFormat_t::RESOLUTION_12B_COMPARE_FORMAT);
  pwm_start(SWEEPER_MOTOR_LEFT, 1, 2000, TimerCompareFormat_t::RESOLUTION_12B_COMPARE_FORMAT);
  sweeperStatus = 1;
}

void drive(int leftMotorSpeed, int rightMotorSpeed)
{
  driveCalled = true;
  if (leftMotorSpeed < 0)
  {
    analogWrite(LEFT_MOTOR_A, 0);
    analogWrite(LEFT_MOTOR_B, -leftMotorSpeed);
  }
  else
  {
    analogWrite(LEFT_MOTOR_B, 0);
    analogWrite(LEFT_MOTOR_A, leftMotorSpeed);
  }

  if (rightMotorSpeed < 0)
  {
    analogWrite(RIGHT_MOTOR_A, 0);
    analogWrite(RIGHT_MOTOR_B, -rightMotorSpeed);
  }
  else
  {
    analogWrite(RIGHT_MOTOR_B, 0);
    analogWrite(RIGHT_MOTOR_A, rightMotorSpeed);
  }
}

void setup()
{
  pinMode(RIGHT_MOTOR_A, OUTPUT);
  pinMode(RIGHT_MOTOR_B, OUTPUT);
  pinMode(LEFT_MOTOR_A, OUTPUT);
  pinMode(LEFT_MOTOR_B, OUTPUT);
  pinMode(PA6, OUTPUT);
  pinMode(PA7, OUTPUT);

  pinMode(TAPE_SENSOR_1, INPUT_ANALOG);
  pinMode(TAPE_SENSOR_2, INPUT_ANALOG);
  pinMode(TAPE_SENSOR_3, INPUT_ANALOG);
  pinMode(TAPE_SENSOR_4, INPUT_ANALOG);
  pinMode(TAPE_SENSOR_5, INPUT_ANALOG);

  pinMode(SERVO_PIN, OUTPUT);
  myservo.attach(SERVO_PIN);
  myservo.write(CLOSED_POSITION);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  delay(1000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  int count = 0;
  do
  {
    getAndPrintTapeSensorValuesAndSpeeds(0, 0);
    count = 0;
    if (tapeSenseValue1 < 400)
    {
      count++;
    }
    if (tapeSenseValue2 < 400)
    {
      count++;
    }
    if (tapeSenseValue3 < 400)
    {
      count++;
    }
    if (tapeSenseValue4 < 400)
    {
      count++;
    }
    if (tapeSenseValue5 < 400)
    {
      count++;
    }
  } while (count < 4);

  delay(1000);
  sweeperOn();
  drive(DEFAULT_SPEED + LEFT_MOTOR_A_ERR, DEFAULT_SPEED + RIGHT_MOTOR_B_ERR); // TURN BACK ON
  delay(500);
  startTime = millis();
}

void sweeperOff()
{
  sweeperStatus = 0;
  analogWrite(SWEEPER_MOTOR_RIGHT, 0);
  analogWrite(SWEEPER_MOTOR_LEFT, 0);
}

void stop()
{
  analogWrite(LEFT_MOTOR_A, 0);
  analogWrite(RIGHT_MOTOR_A, 0);
  analogWrite(RIGHT_MOTOR_B, 0);
  analogWrite(LEFT_MOTOR_B, 0);
  delay(10);
}

void clearDisplay()
{
  display.clearDisplay();
  display.setCursor(0, 0);
}

void park()
{
  stop();
  delay(1000);
  do
  {
    drive(-(SLOW_SPEED + LEFT_MOTOR_B_ERR), -(SLOW_SPEED + RIGHT_MOTOR_B_ERR));
    getAndPrintTapeSensorValuesAndSpeeds(-(SLOW_SPEED + LEFT_MOTOR_B_ERR), -(SLOW_SPEED + RIGHT_MOTOR_B_ERR));
  } while (!(tapeSenseValue1 > TAPE_THRESHOLD1 && tapeSenseValue5 > TAPE_THRESHOLD5));

  stop();
  delay(1000);

  drive(0, -(DEFAULT_SPEED + LEFT_MOTOR_B_ERR + 20));
  delay(3000);
  drive(-(DEFAULT_SPEED + LEFT_MOTOR_B_ERR + 20), -(DEFAULT_SPEED + RIGHT_MOTOR_B_ERR + 20));
  delay(500);
  drive(-(DEFAULT_SPEED + LEFT_MOTOR_B_ERR + 20), 0);
  delay(1000);

  stop();
  delay(250);
}

void followTapeForward()
{
  driveCalled = false;

  if (tapeSenseValue3 > TAPE_THRESHOLD3)
  {
    lastSensorHigh = 3;
    leftMotorSpeed = DEFAULT_SPEED + LEFT_MOTOR_A_ERR;
    rightMotorSpeed = DEFAULT_SPEED + RIGHT_MOTOR_A_ERR;
  }
  else if (tapeSenseValue2 > TAPE_THRESHOLD2)
  {
    if (lastSensorHigh == 1)
    {
      leftMotorSpeed = DEFAULT_SPEED + LEFT_MOTOR_A_ERR;
      rightMotorSpeed = DEFAULT_SPEED + RIGHT_MOTOR_A_ERR;
    }
    else
    {
      rightMotorSpeed += (rightMotorSpeed + 180) * 0.06;
    }
    lastSensorHigh = 2;
  }
  else if (tapeSenseValue4 > TAPE_THRESHOLD4)
  {
    if (lastSensorHigh == 5)
    {
      leftMotorSpeed = DEFAULT_SPEED + LEFT_MOTOR_A_ERR;
      rightMotorSpeed = DEFAULT_SPEED + RIGHT_MOTOR_A_ERR;
    }
    else
    {
      leftMotorSpeed += (leftMotorSpeed + 180) * 0.06;
    }
    lastSensorHigh = 4;
  }
  else if (tapeSenseValue1 > TAPE_THRESHOLD1)
  {
    lastSensorHigh = 1;
    leftMotorSpeed -= (leftMotorSpeed + 180) * 0.19;
    rightMotorSpeed += (rightMotorSpeed + 180) * 0.19;
  }
  else if (tapeSenseValue5 > TAPE_THRESHOLD5)
  {
    lastSensorHigh = 5;
    leftMotorSpeed += (leftMotorSpeed + 180) * 0.19;
    rightMotorSpeed -= (rightMotorSpeed + 180) * 0.19;
  }
  else if (lastSensorHigh == 1 || lastSensorHigh == 5)
  {
    drive(-(DEFAULT_SPEED + LEFT_MOTOR_B_ERR), -(DEFAULT_SPEED + RIGHT_MOTOR_B_ERR));
  }

  if (!driveCalled)
  {
    if (leftMotorSpeed < -MAX_SPEED)
    {
      leftMotorSpeed = -MAX_SPEED;
    }
    else if (leftMotorSpeed > MAX_SPEED)
    {
      leftMotorSpeed = MAX_SPEED;
    }

    if (rightMotorSpeed < -MAX_SPEED)
    {
      rightMotorSpeed = -MAX_SPEED;
    }
    else if (rightMotorSpeed > MAX_SPEED)
    {
      rightMotorSpeed = MAX_SPEED;
    }

    drive(leftMotorSpeed, rightMotorSpeed);
  }

  getAndPrintTapeSensorValuesAndSpeeds(leftMotorSpeed, rightMotorSpeed);
}

void depositCans()
{
  myservo.write(DEPOSIT_POSITION);
  delay(500);
  int time = millis();

  while (millis() - time < 5000)
  {
    myservo.write(DEPOSIT_POSITION + 30);
    delay(300);
    myservo.write(DEPOSIT_POSITION);
    delay(300);
    myservo.write(DEPOSIT_POSITION - 30);
    delay(300);
  }
}

bool check = false;
int count = 0;
int checkTime = 0;

void loop()
{ //assume sensors are numbered from left to right from POV of someone following robot from behind
  if (tapeSenseValue2 > TAPE_THRESHOLD2 && tapeSenseValue4 > TAPE_THRESHOLD4 && tapeSenseValue3 > TAPE_THRESHOLD3 && check == false)
  {

    check = true;
    checkTime = millis();
    MAX_SPEED = 155;
    DEFAULT_SPEED = 115;
  }
  if (tapeSenseValue1 > TAPE_THRESHOLD1 && tapeSenseValue5 > TAPE_THRESHOLD5 && millis() - checkTime > 2500 /*&& tapeSenseValue3 > TAPE_THRESHOLD3  && (millis() - startTime) > 25000*/)
  {
    count++;
    if (count == 1)
    {
      park();
      depositCans();
      exit(0);
    }
  }
  else
  {
    followTapeForward();
  }
}