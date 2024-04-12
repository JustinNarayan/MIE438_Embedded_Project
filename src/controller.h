#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>

// Enum for direction and turn
typedef enum
{
    DIRECTION_NONE,
    DIRECTION_FORWARD,
    DIRECTION_BACKWARD
} Direction;

typedef enum
{
    TURN_NONE,
    TURN_LEFT,
    TURN_RIGHT
} Turn;

typedef enum
{
    LIFT_MOTOR_LIFT,
    LIFT_MOTOR_FALL,
    LIFT_MOTOR_NONE
} LiftMotor;

typedef enum
{
    GRAB_MOTOR_GRAB,
    GRAB_MOTOR_RELEASE,
    GRAB_MOTOR_NONE
} GrabMotor;

// Record which buttons are pressed
typedef struct
{
    bool forward;
    bool backward;
    bool left;
    bool right;
    bool lift;
    bool fall;
    bool grab;
    bool release;
    bool stop;
    bool enable_disable;
} ButtonState;

// Status struct
typedef struct
{
    Direction direction;
    Turn turn;
    LiftMotor lift;
    GrabMotor grab;
    uint8_t halt;
    uint8_t display;
} Controller;

// Controller initialization function
void controller_init(Controller *controller);

// Controller update function
void controller_update(Controller *status);

#endif