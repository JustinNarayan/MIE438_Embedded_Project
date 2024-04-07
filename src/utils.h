#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <STM32FreeRTOS.h>

// UART
#define SERIAL_PORT Serial1

// LED
#define LED_PIN LED_BUILTIN
#define LED_TIME 100 // Blink interval in milliseconds

// Drivetrain
#define DRIVETRAIN_LEFT_IN1 PB0
#define DRIVETRAIN_LEFT_IN2 PB0
#define DRIVETRAIN_LEFT_EN PB0

#define DRIVETRAIN_RIGHT_IN1 PB0
#define DRIVETRAIN_RIGHT_IN2 PB0
#define DRIVETRAIN_RIGHT_EN PB0

// Controller
#define BTN_FORWARD_PIN 2
#define BTN_BACKWARD_PIN 3
#define BTN_LEFT_PIN 4
#define BTN_RIGHT_PIN 5
#define BTN_STOP_PIN 6
#define BTN_TOGGLE_DISPLAY 7
#define BTN_ENABLE_DISABLE 8
#define NUM_IMAGES 1

void generateTask(TaskFunction_t taskFunction, const char *taskName,
                  void *taskParameters);

#endif
