#include "controller.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <Arduino.h>
#include <utils.h>

static ButtonState currentState;
static ButtonState previousState;

static void updateButtonState();
static bool isButtonPressed(uint8_t pin);

void controller_init(Controller *controller)
{
    // Initialize GPIO pins for buttons
    pinMode(BTN_FORWARD_PIN, INPUT_PULLUP);
    pinMode(BTN_BACKWARD_PIN, INPUT_PULLUP);
    pinMode(BTN_LEFT_PIN, INPUT_PULLUP);
    pinMode(BTN_RIGHT_PIN, INPUT_PULLUP);
    
    pinMode(BTN_LIFT_PIN, INPUT_PULLUP);
    pinMode(BTN_FALL_PIN, INPUT_PULLUP);
    pinMode(BTN_GRAB_PIN, INPUT_PULLUP);
    pinMode(BTN_RELEASE_PIN, INPUT_PULLUP);

    pinMode(BTN_STOP_PIN, INPUT_PULLUP);
    pinMode(BTN_ENABLE_DISABLE, INPUT_PULLUP);

    // Initialize status
    controller->direction = DIRECTION_NONE;
    controller->turn = TURN_NONE;
    controller->lift = LIFT_MOTOR_NONE;
    controller->grab = GRAB_MOTOR_NONE;
    controller->halt = false;
    controller->display = false;

    // Initialize button states
    currentState.forward = false;
    currentState.backward = false;
    currentState.left = false;
    currentState.right = false;
    currentState.lift = false;
    currentState.fall = false;
    currentState.grab = false;
    currentState.release = false;
    currentState.stop = false;
    currentState.enable_disable = false;

    previousState = currentState;
}

void controller_update(Controller *controller)
{
    if (!controller)
        return;

    updateButtonState();

    // Update direction
    if (!currentState.stop && (currentState.forward && !currentState.backward))
    {
        controller->direction = DIRECTION_FORWARD;
    }
    else if (!currentState.stop && (currentState.backward && !currentState.forward))
    {
        controller->direction = DIRECTION_BACKWARD;
    }
    else
    {
        controller->direction = DIRECTION_NONE;
    }

    // Update turn
    if (!currentState.stop && (currentState.left && !currentState.right))
    {
        controller->turn = TURN_LEFT;
    }
    else if (!currentState.stop && (currentState.right && !currentState.left))
    {
        controller->turn = TURN_RIGHT;
    }
    else
    {
        controller->turn = TURN_NONE;
    }

    // Update lift
    if (!currentState.stop && (currentState.lift && !currentState.fall))
    {
        controller->lift = LIFT_MOTOR_LIFT;
    }
    else if (!currentState.stop && (currentState.fall && !currentState.lift))
    {
        controller->lift = LIFT_MOTOR_FALL;
    }
    else
    {
        controller->lift = LIFT_MOTOR_NONE;
    }

    // Update grab
    if (!currentState.stop && (currentState.grab && !currentState.release))
    {
        controller->grab = GRAB_MOTOR_GRAB;
    }
    else if (!currentState.stop && (currentState.release && !currentState.grab))
    {
        controller->grab = GRAB_MOTOR_RELEASE;
    }
    else
    {
        controller->grab = GRAB_MOTOR_NONE;
    }

    // Update halt
    controller->halt = currentState.stop;

    // Update LCD 
    if (currentState.enable_disable && !previousState.enable_disable)
    {
        controller->display = !controller->display; // Toggle display
    }
}

static void updateButtonState()
{
    previousState = currentState;

    currentState.forward = isButtonPressed(BTN_FORWARD_PIN);
    currentState.backward = isButtonPressed(BTN_BACKWARD_PIN);
    currentState.left = isButtonPressed(BTN_LEFT_PIN);
    currentState.right = isButtonPressed(BTN_RIGHT_PIN);
    
    currentState.lift = isButtonPressed(BTN_LIFT_PIN);
    currentState.fall = isButtonPressed(BTN_FALL_PIN);
    currentState.grab = isButtonPressed(BTN_GRAB_PIN);
    currentState.release = isButtonPressed(BTN_RELEASE_PIN);

    currentState.stop = isButtonPressed(BTN_STOP_PIN);
    currentState.enable_disable = isButtonPressed(BTN_ENABLE_DISABLE);
}

static bool isButtonPressed(uint8_t pin)
{
    return digitalRead(pin) == LOW;
}