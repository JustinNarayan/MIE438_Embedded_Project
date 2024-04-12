#include "drivetrain.h"
#include <Arduino.h>

void drivetrain_init(drivetrain *driver, L298N *left, L298N *right)
{
    driver->left_driver = left;
    driver->right_driver = right;

    L298N_init(driver->left_driver, DRIVETRAIN_LEFT_EN, DRIVETRAIN_LEFT_IN1, DRIVETRAIN_LEFT_IN2);
    L298N_init(driver->right_driver, DRIVETRAIN_RIGHT_EN, DRIVETRAIN_RIGHT_IN1, DRIVETRAIN_RIGHT_IN2);
}

void drivetrain_forward(drivetrain *driver, bool backward)
{
    if(backward) {
        L298N_backward(driver->left_driver, FORWARD_SPEED);
        L298N_backward(driver->right_driver, FORWARD_SPEED);
    } else {
        L298N_forward(driver->left_driver, FORWARD_SPEED);
        L298N_forward(driver->right_driver, FORWARD_SPEED);
    }
}

void drivetrain_turn_moving(drivetrain *driver, bool leadLeft, bool backward)
{
    // Determine which motor leads the turn
    L298N *lead, *follow;
    if(leadLeft) {
        lead = driver->left_driver;
        follow = driver->right_driver;
    } else {
        lead = driver->right_driver;
        follow = driver->left_driver;
    }

    // Run the motors
    if(backward) {
        L298N_backward(lead, TURN_SPEED_LEAD);
        L298N_backward(follow, TURN_SPEED_FOLLOW);
    } else {
        L298N_forward(lead, TURN_SPEED_LEAD);
        L298N_forward(follow, TURN_SPEED_FOLLOW);
    }
}

void drivetrain_turn_pivot(drivetrain *driver, bool leadLeft)
{
    // Determine which motor leads the turn
    L298N *lead, *follow;
    if(leadLeft) {
        lead = driver->left_driver;
        follow = driver->right_driver;
    } else {
        lead = driver->right_driver;
        follow = driver->left_driver;
    }

    // Run the motors
    L298N_backward(lead, TURN_SPEED_PIVOT);
    L298N_forward(follow, TURN_SPEED_PIVOT);
}

void drivetrain_halt(drivetrain *driver)
{
    L298N_halt(driver->left_driver);
    L298N_halt(driver->right_driver);
}
