#include "ROB_09454.h"
#include <Arduino.h>

void ROB_09454_init(ROB_09454 *sensor, uint8_t pin) {
  sensor->pin = pin;
  pinMode(sensor->pin, INPUT);
}

uint8_t ROB_09454_read(ROB_09454 *sensor) {
  return digitalRead(sensor->pin);
}
