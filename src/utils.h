#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <STM32FreeRTOS.h>

// UART
#define SERIAL_PORT Serial1

// LED
#define LED_PIN LED_BUILTIN
#define LED_TIME 500 // Blink interval in milliseconds

// Drivetrain
#define DRIVETRAIN_UPDATE_TIME 50

#define DRIVETRAIN_LEFT_IN1 PE4
#define DRIVETRAIN_LEFT_IN2 PE2
#define DRIVETRAIN_LEFT_EN A4

#define DRIVETRAIN_RIGHT_IN1 PE5
#define DRIVETRAIN_RIGHT_IN2 PE6
#define DRIVETRAIN_RIGHT_EN A5

// Arm
#define APPENDAGE_LIFT_IN1 PD7
#define APPENDAGE_LIFT_IN2 PD6
#define APPENDAGE_LIFT_EN A0

#define APPENDAGE_GRAB_IN1 PD5 
#define APPENDAGE_GRAB_IN2 PPD4
#define APPENDAGE_GRAB_EN A1

// Controller
#define CONTROLLER_POLL_TIME 25
#define BTN_FORWARD_PIN D5
#define BTN_BACKWARD_PIN D6
#define BTN_LEFT_PIN D4
#define BTN_RIGHT_PIN D7
#define BTN_STOP_PIN D3
#define BTN_ENABLE_DISABLE D2

// LCD
#define LCD_UPDATE_TIME 50
#define LCD1602_SCL PF1
#define LCD1602_SDA PF0

// Line Sensor
#define ROB09454_PIN D12

void generateTask(TaskFunction_t taskFunction, const char *taskName,
                  void *taskParameters);

#endif
