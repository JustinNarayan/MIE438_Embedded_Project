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
    pinMode(BTN_STOP_PIN, INPUT_PULLUP);
    pinMode(BTN_ENABLE_DISABLE, INPUT_PULLUP);

    // Initialize status
    controller->direction = DIRECTION_NONE;
    controller->turn = TURN_NONE;
    controller->halt = false;
    controller->display = false;

    // Initialize button states
    currentState.forward = false;
    currentState.backward = false;
    currentState.left = false;
    currentState.right = false;
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

    // // Update turn
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

    // Update halt
    controller->halt = currentState.stop;

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
    currentState.stop = isButtonPressed(BTN_STOP_PIN);
    currentState.enable_disable = isButtonPressed(BTN_ENABLE_DISABLE);
}

static bool isButtonPressed(uint8_t pin)
{
    return digitalRead(pin) == LOW;
}