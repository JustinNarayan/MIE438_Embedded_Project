#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <STM32FreeRTOS.h>

// UART
#define SERIAL_PORT Serial1

// LED
#define LED_PIN LED_BUILTIN
#define LED_PRIORITY 0 // lowest priority
#define LED_TIME 500 // Blink interval in milliseconds

// Drivetrain
#define DRIVETRAIN_UPDATE_TIME 50
#define DRIVETRAIN_UPDATE_PRIORITY (configMAX_PRIORITIES-2) // second-highest priority

#define DRIVETRAIN_LEFT_IN1 PE2
#define DRIVETRAIN_LEFT_IN2 PE4
#define DRIVETRAIN_LEFT_EN PB0 // PWM

#define DRIVETRAIN_RIGHT_IN1 PE6
#define DRIVETRAIN_RIGHT_IN2 PE5
#define DRIVETRAIN_RIGHT_EN PB2 // PWM

// Arm
#define APPENDAGE_UPDATE_TIME 50
#define APPENDAGE_UPDATE_PRIORITY (configMAX_PRIORITIES-3)

#define APPENDAGE_LIFT_IN1 PD7
#define APPENDAGE_LIFT_IN2 PD6
#define APPENDAGE_LIFT_EN PA3 // PWM

#define APPENDAGE_GRAB_IN1 PD5 
#define APPENDAGE_GRAB_IN2 PD4
#define APPENDAGE_GRAB_EN PA2 // PWM

// Controller
#define CONTROLLER_POLL_TIME 25
#define CONTROLLER_POLL_PRIORITY (configMAX_PRIORITIES-1) // highest priority

#define BTN_STOP_PIN D15
#define BTN_ENABLE_DISABLE D14

#define BTN_FORWARD_PIN D13
#define BTN_BACKWARD_PIN D12
#define BTN_LEFT_PIN D11
#define BTN_RIGHT_PIN D10

#define BTN_LIFT_PIN D9
#define BTN_FALL_PIN D8

#define BTN_GRAB_PIN D7
#define BTN_RELEASE_PIN D6

// LCD
#define LCD_UPDATE_TIME 50
#define LCD_UPDATE_PRIORITY 0

#define LCD1602_SCL PF1
#define LCD1602_SDA PF0

void generateTask(TaskFunction_t taskFunction, const char *taskName,
                  void *taskParameters, UBaseType_t priority);

#endif
