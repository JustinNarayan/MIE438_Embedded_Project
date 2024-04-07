#include "controller.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <Arduino.h>

static Controller status;
static ButtonState currentState;
static ButtonState previousState;

static void updateButtonState();
static bool isButtonPressed(uint8_t pin);

uint8_t image_count;

void controller_init(Controller *controller, uint8_t display_num_images)
{
    // Initialize GPIO pins for buttons
    pinMode(BTN_FORWARD_PIN, INPUT_PULLUP);
    pinMode(BTN_BACKWARD_PIN, INPUT_PULLUP);
    pinMode(BTN_LEFT_PIN, INPUT_PULLUP);
    pinMode(BTN_RIGHT_PIN, INPUT_PULLUP);
    pinMode(BTN_STOP_PIN, INPUT_PULLUP);
    pinMode(BTN_TOGGLE_DISPLAY, INPUT_PULLUP);
    pinMode(BTN_ENABLE_DISABLE, INPUT_PULLUP);

    image_count = display_num_images;

    // Initialize status
    controller->direction = DIRECTION_NONE;
    controller->turn = TURN_NONE;
    controller->halt = false;
    controller->display = true; // Default to display on
    controller->image = 0;

    // Initialize button states
    currentState.forward = false;
    currentState.backward = false;
    currentState.left = false;
    currentState.right = false;
    currentState.stop = false;
    currentState.toggle_display = false;
    currentState.enable_disable = false;

    previousState = currentState;
}

void controller_update(Controller *controller)
{
    if (!controller)
        return;

    updateButtonState();

    // Update direction
    if (currentState.forward && !currentState.backward)
    {
        controller->direction = DIRECTION_FORWARD;
    }
    else if (currentState.backward && !currentState.forward)
    {
        controller->direction = DIRECTION_BACKWARD;
    }
    else
    {
        controller->direction = DIRECTION_NONE;
    }

    // Update turn
    if (currentState.left && !currentState.right)
    {
        controller->turn = TURN_LEFT;
    }
    else if (currentState.right && !currentState.left)
    {
        controller->turn = TURN_RIGHT;
    }
    else
    {
        controller->turn = TURN_NONE;
    }

    // Update halt
    controller->halt = currentState.stop;

    // Update display
    if (currentState.enable_disable && !previousState.enable_disable)
    {
        controller->display = !controller->display; // Toggle display
    }

    // Update image
    if (currentState.toggle_display && !previousState.toggle_display)
    {
        controller->image = (controller->image + 1) % image_count;
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
    currentState.toggle_display = isButtonPressed(BTN_TOGGLE_DISPLAY);
    currentState.enable_disable = isButtonPressed(BTN_ENABLE_DISABLE);
}

static bool isButtonPressed(uint8_t pin)
{
    return digitalRead(pin) == LOW;
}