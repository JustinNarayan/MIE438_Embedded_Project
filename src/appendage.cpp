#include "appendage.h"
#include <Arduino.h>

void appendage_init(appendage *arm, L298N *lift, L298N *grab)
{
    arm->lift_driver = lift;
    arm->grab_driver = grab;

    L298N_init(arm->lift_driver, APPENDAGE_LIFT_EN, APPENDAGE_LIFT_IN1, APPENDAGE_LIFT_IN2);
    L298N_init(arm->grab_driver, APPENDAGE_GRAB_EN, APPENDAGE_GRAB_IN1, APPENDAGE_GRAB_IN2);
}

void appendage_lift(appendage *arm)
{
    L298N_forward(arm->lift_driver, LIFT_SPEED);
    delay(LIFT_TIME);
    L298N_halt(arm->lift_driver);
}

void appendage_fall(appendage *arm)
{
    L298N_backward(arm->lift_driver, FALL_SPEED);
    delay(FALL_TIME);
    L298N_halt(arm->lift_driver);
}

void appendage_grab(appendage *arm)
{
    L298N_forward(arm->grab_driver, GRAB_SPEED);
    delay(GRAB_TIME);
    L298N_halt(arm->grab_driver);
}

void appendage_release(appendage *arm)
{
    L298N_backward(arm->grab_driver, RELEASE_SPEED);
    delay(RELEASE_TIME);
    L298N_halt(arm->grab_driver);
}


void appendage_halt(appendage *arm)
{
    L298N_halt(arm->lift_driver);
    L298N_halt(arm->grab_driver);
}
