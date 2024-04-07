#ifndef L298N_H
#define L298N_H

#include <stdint.h>

typedef struct
{
    uint8_t enPin;
    uint8_t in1Pin;
    uint8_t in2Pin;
} L298N;

void L298N_init(L298N *motor_driver, uint8_t enPin, uint8_t in1Pin, uint8_t in2Pin);
void L298N_forward(L298N *motor_driver, uint8_t speed);
void L298N_backward(L298N *motor_driver, uint8_t speed);
void L298N_halt(L298N *motor_driver);

#endif