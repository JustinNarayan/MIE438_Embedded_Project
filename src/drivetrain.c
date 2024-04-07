#include "drivetrain.h"
#include <Arduino.h>

void drivetrain_init(drivetrain *driver)
{
    L298N_init(driver->left_driver, DRIVETRAIN_LEFT_EN, DRIVETRAIN_LEFT_IN1, DRIVETRAIN_LEFT_IN2);
    L298N_init(driver->right_driver, DRIVETRAIN_RIGHT_EN, DRIVETRAIN_RIGHT_IN1, DRIVETRAIN_RIGHT_IN2);
}

void drivetrain_halt(drivetrain *driver)
{
    L298N_halt(driver->left_driver);
    L298N_halt(driver->right_driver);
}
