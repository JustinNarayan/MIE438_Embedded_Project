#include "l298n.h"
#include <Arduino.h>

void L298N_init(L298N *motor_driver, uint8_t enPin, uint8_t in1Pin, uint8_t in2Pin)
{
    motor_driver->enPin = enPin;
    motor_driver->in1Pin = in1Pin;
    motor_driver->in2Pin = in2Pin;

    pinMode(motor_driver->enPin, OUTPUT);
    pinMode(motor_driver->in1Pin, OUTPUT);
    pinMode(motor_driver->in2Pin, OUTPUT);
}

void L298N_forward(L298N *motor_driver, uint8_t speed)
{
    digitalWrite(motor_driver->in1Pin, HIGH);
    digitalWrite(motor_driver->in2Pin, LOW);
    analogWrite(motor_driver->enPin, speed);
}

void L298N_backward(L298N *motor_driver, uint8_t speed)
{
    digitalWrite(motor_driver->in1Pin, LOW);
    digitalWrite(motor_driver->in2Pin, HIGH);
    analogWrite(motor_driver->enPin, speed);
}

void L298N_halt(L298N *motor_driver)
{
    digitalWrite(motor_driver->in1Pin, LOW);
    digitalWrite(motor_driver->in2Pin, LOW);
    analogWrite(motor_driver->enPin, 0);
}
