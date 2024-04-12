#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <utils.h>
#include <l298n.h>
#include <drivetrain.h>
#include <appendage.h>
#include <controller.h>
#include <lcd1602.h>
#include <rob_09454.h>

// Static variables
static Controller controller;
static L298N leftMotor, rightMotor;
static L298N liftMotor, grabMotor;
static drivetrain driver;
static appendage arm;
static LCD1602 display;
static ROB_09454 sensor;

static void blinkTask(void *parameters)
{
  while (1)
  { 
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(LED_TIME / portTICK_PERIOD_MS);
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(LED_TIME / portTICK_PERIOD_MS);
  }
}


static void pollControllerTask(void* parameters) {
  while(1) {
    controller_update(&controller);
    vTaskDelay(CONTROLLER_POLL_TIME / portTICK_PERIOD_MS);
  }
}

static void drivetrainUpdateTask(void* parameters) {
  while(1) {
    // Process the controls

    if(controller.halt) {
      drivetrain_halt(&driver);
    } else {

      if(controller.direction == DIRECTION_NONE) {
        if(controller.turn == TURN_NONE) {
          drivetrain_halt(&driver);
        } else {
          drivetrain_turn_pivot(&driver, controller.turn == TURN_LEFT);
        }
      } else {
        if(controller.turn == TURN_NONE) {
          drivetrain_forward(&driver, controller.direction == DIRECTION_BACKWARD);
        } else {
          drivetrain_turn_moving(&driver, controller.turn == TURN_LEFT, controller.direction == DIRECTION_BACKWARD);
        }
      }

    }

    vTaskDelay(DRIVETRAIN_UPDATE_TIME / portTICK_PERIOD_MS);
  }
}

static void lcdUpdateTask(void* parameters) {
  while(1) {
    if(controller.display != display.enabled) {
      lcd1602_toggle(&display);
    }

    vTaskDelay(LCD_UPDATE_TIME / portTICK_PERIOD_MS);
  }
}

static void initTask(void *parameters)
{

  vTaskDelay(1000 / portTICK_PERIOD_MS);

  // Enable LED
  pinMode(LED_PIN, OUTPUT);

  // Initializations
  drivetrain_init(&driver, &leftMotor, &rightMotor);
  appendage_init(&arm, &liftMotor, &grabMotor);
  controller_init(&controller);
  lcd1602_init(&display);

  // Create blink task
  generateTask(blinkTask, "Blink", NULL);

  // Create controller poll task
  generateTask(pollControllerTask, "Controller poll", NULL);

  // Create update tasks
  generateTask(drivetrainUpdateTask, "Drivetrain update", NULL);
  // generateTask(armUpdateTask, "Arm update", NULL);
  generateTask(lcdUpdateTask, "LCD update", NULL);

  SERIAL_PORT.println("Completed init");
  vTaskDelete(NULL);
}

void setup()
{
  // As the very first thing, initialize UART
  SERIAL_PORT.begin(9600);

  // Create init task
  generateTask(initTask, "Init", NULL);

  // Create FreeRTOS scheduler
  vTaskStartScheduler();

  // We should never reach this point
  SERIAL_PORT.println("Insufficient RAM for FreeRTOS");
  while (1)
    ;
}

void loop()
{
  // Empty loop, not used because FreeRTOS is managing tasks
  // SERIAL_PORT.println("No FreeRTOS tasks scheduled!");
}
