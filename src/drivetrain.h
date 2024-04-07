#ifndef DRICETRAIN_H
#define DRIVETRAIN_H

#include <stdint.h>
#include <l298n.h>
#include <utils.h>

#define FORWARD_SPEED 180
#define TURN_SPEED 100

typedef struct
{
    L298N* left_driver;
    L298N* right_driver;
} drivetrain;

void drivetrain_init(drivetrain *driver);
void drivetrain_halt(drivetrain *driver);

#endif