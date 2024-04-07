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

void generateTask(TaskFunction_t taskFunction, const char *taskName,
                  void *taskParameters);

#endif
