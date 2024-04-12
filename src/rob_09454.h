#ifndef ROB_09454_H
#define ROB_09454_H

#include <stdint.h>
#include <utils.h>

typedef struct {
  uint8_t pin;
} ROB_09454;

void ROB_09454_init(ROB_09454 *sensor, uint8_t pin);
int ROB_09454_read(ROB_09454 *sensor);

#endif
