#ifndef APPENDAGE_H
#define APPENDAGE_H

#include <stdint.h>
#include <l298n.h>
#include <utils.h>

#define LIFT_SPEED 0xDF
#define FALL_SPEED 0x4F
#define GRAB_SPEED 0x4F
#define RELEASE_SPEED 0x4F

#define LIFT_TIME 200 // ms
#define FALL_TIME 150
#define GRAB_TIME 150
#define RELEASE_TIME 150

typedef struct
{
    L298N* lift_driver;
    L298N* grab_driver;
} appendage;

void appendage_init(appendage *arm, L298N *lift, L298N *grab);
void appendage_lift(appendage *arm);
void appendage_fall(appendage *arm);
void appendage_grab(appendage *arm);
void appendage_release(appendage *arm);
void appendage_halt(appendage *arm);

#endif