#ifndef DRICETRAIN_H
#define DRIVETRAIN_H

#include <stdint.h>
#include <l298n.h>
#include <utils.h>

#define FORWARD_SPEED_LEFT 0xFF
#define FORWARD_SPEED_RIGHT 0xFF
#define TURN_SPEED_LEAD 0xFF
#define TURN_SPEED_FOLLOW 0xCF
#define TURN_SPEED_PIVOT 0xFF

typedef struct
{
    L298N* left_driver;
    L298N* right_driver;
} drivetrain;

void drivetrain_init(drivetrain *driver, L298N *left, L298N *right);
void drivetrain_forward(drivetrain *driver, bool backward);
void drivetrain_turn_moving(drivetrain *driver, bool leadLeft, bool backward);
void drivetrain_turn_pivot(drivetrain *driver, bool leadLeft);
void drivetrain_halt(drivetrain *driver);

#endif