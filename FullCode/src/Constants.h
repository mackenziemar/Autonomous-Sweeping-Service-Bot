#ifndef _PINASSIGNMENTS_H
#define _PINASSIGNMENTS_H

//Tape
#define TAPE_THRESHOLD1 500 //reassign threshold values
#define TAPE_THRESHOLD2 500
#define TAPE_THRESHOLD3 500
#define TAPE_THRESHOLD4 500
#define TAPE_THRESHOLD5 500

#define TAPE_SENSOR_1 PA4
#define TAPE_SENSOR_2 PA3
#define TAPE_SENSOR_3 PA2
#define TAPE_SENSOR_4 PA1
#define TAPE_SENSOR_5 PA0

//Motors
#define RIGHT_MOTOR_A PB7
#define RIGHT_MOTOR_B PA8
#define LEFT_MOTOR_A PA9
#define LEFT_MOTOR_B PA10

#define SWEEPER_MOTOR_LEFT PA_6
#define SWEEPER_MOTOR_RIGHT PA_7

//Deposit
// #define SERVO_PIN PB1
#define SERVO_PIN PB6 //FOR RAVELCLAW


#define DEPOSIT_POSITION 90 //figure out later
#define CLOSED_POSITION 0

//OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // This display does not have a reset pin accessible
#define SDA PB9
#define SLC PB8

//Direction Code
#define FORWARD 0
#define FORWARD_LEFT_SMALL 1
#define FORWARD_RIGHT_SMALL 2
#define FORWARD_LEFT_LARGE 3
#define FORWARD_RIGHT_LARGE 4
#define FORWARD_LEFT_XLARGE 5
#define FORWARD_RIGHT_XLARGE 6
#define BACKWARD 7
#define STOP 8

// Gryffindor errs
// #define RIGHT_MOTOR_A_ERR 2
// #define RIGHT_MOTOR_B_ERR 10
// #define LEFT_MOTOR_A_ERR 0
// #define LEFT_MOTOR_B_ERR 0

// // Slytherin errs
// #define RIGHT_MOTOR_A_ERR 1
// #define RIGHT_MOTOR_B_ERR 0
// #define LEFT_MOTOR_A_ERR 10
// #define LEFT_MOTOR_B_ERR 20

// Ravenclaw errs
#define RIGHT_MOTOR_A_ERR 0
#define RIGHT_MOTOR_B_ERR 3
#define LEFT_MOTOR_A_ERR 7
#define LEFT_MOTOR_B_ERR 7

// // Hufflepuff errs
// #define RIGHT_MOTOR_A_ERR 1
// #define RIGHT_MOTOR_B_ERR -5
// #define LEFT_MOTOR_A_ERR 25
// #define LEFT_MOTOR_B_ERR 30

#endif