#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>

// Button mapping
#define BTN_FORWARD_PIN 2
#define BTN_BACKWARD_PIN 3
#define BTN_LEFT_PIN 4
#define BTN_RIGHT_PIN 5
#define BTN_STOP_PIN 6
#define BTN_TOGGLE_DISPLAY 7
#define BTN_ENABLE_DISABLE 8

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
void controller_init(Controller *controller, uint8_t display_num_images);

// Controller update function (call in main loop)
void controller_update(Controller *status);

#endif
