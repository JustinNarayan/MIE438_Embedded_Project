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

// Record which buttons are pressed
typedef struct
{
    bool forward;
    bool backward;
    bool left;
    bool right;
    bool stop;
    bool toggle_display;
    bool enable_disable;
} ButtonState;

// Status struct
typedef struct
{
    Direction direction;
    Turn turn;
    uint8_t halt;
    uint8_t display;
    uint8_t image;
} Controller;

// Controller initialization function
void controller_init(Controller *controller);

// Controller update function (call in main loop)
void controller_update(Controller *status);

#endif