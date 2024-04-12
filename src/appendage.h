#ifndef APPENDAGE_H
#define APPENDAGE_H

#include <stdint.h>
#include <l298n.h>
#include <utils.h>

#define LIFT_SPEED 0xFF
#define FALL_SPEED 0x28
#define REST_SPEED 0x00
#define GRAB_SPEED 0x60
#define RELEASE_SPEED 0x60

typedef struct
{
    L298N* lift_driver;
    L298N* grab_driver;
} appendage;

void appendage_init(appendage *arm, L298N *lift, L298N *grab);
void appendage_lift(appendage *arm);
void appendage_fall(appendage *arm);
void appendage_rest(appendage *arm);
void appendage_grab(appendage *arm);
void appendage_release(appendage *arm);
void appendage_halt_lift(appendage *arm);
void appendage_halt_grab(appendage *arm);
void appendage_halt(appendage *arm);

#endif