#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <utils.h>
#include <l298n.h>
#include <drivetrain.h>
#include <appendage.h>
#include <controller.h>
#include <lcd1602.h>
#include <rob_09454.h>

#define DEBUG_TASKS 0
#define DEBUG_DRIVETRAIN_COMMANDS 0
#define DEBUG_APPENDAGE_COMMANDS 0

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
    if(DEBUG_TASKS) SERIAL_PORT.println("Blink");

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(LED_TIME / portTICK_PERIOD_MS);
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(LED_TIME / portTICK_PERIOD_MS);
  }
}

static void pollControllerTask(void* parameters) {
  while(1) {
    if(DEBUG_TASKS) SERIAL_PORT.println("C");

    controller_update(&controller);
    vTaskDelay(CONTROLLER_POLL_TIME / portTICK_PERIOD_MS);
  }
}

static void drivetrainUpdateTask(void* parameters) {
  while(1) {
    if(DEBUG_TASKS) SERIAL_PORT.println("D");

    // Process the controls

    if(controller.halt) {
      drivetrain_halt(&driver);

      // Debug
      if(DEBUG_DRIVETRAIN_COMMANDS) SERIAL_PORT.println("Halt");

    } else {

      if(controller.direction == DIRECTION_NONE) {
        if(controller.turn == TURN_NONE) {
          drivetrain_halt(&driver);
          
          // Debug
          // if(DEBUG_DRIVETRAIN_COMMANDS) SERIAL_PORT.print("None\t");
        } else {
          drivetrain_turn_pivot(&driver, controller.turn == TURN_LEFT);

          // Debug
          if(DEBUG_DRIVETRAIN_COMMANDS) {
            if(controller.turn == TURN_LEFT)
              SERIAL_PORT.println(".Left\t");
            else
              SERIAL_PORT.println(".Right\t");
          }
        }

        // if(DEBUG_DRIVETRAIN_COMMANDS) SERIAL_PORT.println("None\t");
      } else {
        if(controller.turn == TURN_NONE) {
          drivetrain_forward(&driver, controller.direction == DIRECTION_BACKWARD);
        
          // Debug
          if(DEBUG_DRIVETRAIN_COMMANDS) {
            // SERIAL_PORT.print("None\t");

            if(controller.direction == DIRECTION_BACKWARD)
                SERIAL_PORT.println("Back\t");
              else
                SERIAL_PORT.println("For\t");
          }

        } else {
          drivetrain_turn_moving(&driver, controller.turn == TURN_LEFT, controller.direction == DIRECTION_BACKWARD);

          if(DEBUG_DRIVETRAIN_COMMANDS) {
            if(controller.turn == TURN_LEFT)
              SERIAL_PORT.print("^Left\t");
            else
              SERIAL_PORT.print("^Right\t");

            if(controller.direction == DIRECTION_BACKWARD)
              SERIAL_PORT.println("Back\t");
            else
              SERIAL_PORT.println("For\t");
          }
        }
      }
    }

    vTaskDelay(DRIVETRAIN_UPDATE_TIME / portTICK_PERIOD_MS);
  }

}

static void appendageUpdateTask(void* parameters) {
  while(1) {
    if(DEBUG_TASKS) SERIAL_PORT.println("A");

    // Process the controls

    if(controller.halt) {
      appendage_halt(&arm);

      if(DEBUG_APPENDAGE_COMMANDS)
        SERIAL_PORT.println("Halt");
    } else {

      if(controller.lift == LIFT_MOTOR_NONE) {
          // We have found that it needs to just idle at a low frequency  
          appendage_rest(&arm);
      } else {
        if(controller.lift == LIFT_MOTOR_LIFT) {
          appendage_lift(&arm);

          if(DEBUG_APPENDAGE_COMMANDS)
            SERIAL_PORT.println("Lift");

          
        } else {
          appendage_fall(&arm);

          if(DEBUG_APPENDAGE_COMMANDS)
            SERIAL_PORT.println("Fall");

        }
      }

      if(controller.grab == GRAB_MOTOR_NONE) {
          appendage_halt_grab(&arm);
      } else {
        if(controller.grab == GRAB_MOTOR_GRAB) {
          appendage_grab(&arm);

          if(DEBUG_APPENDAGE_COMMANDS)
            SERIAL_PORT.println("Grab");

        } else {
          appendage_release(&arm);

          if(DEBUG_APPENDAGE_COMMANDS)
            SERIAL_PORT.println("Release");
        }
      }
    }

    vTaskDelay(APPENDAGE_UPDATE_TIME / portTICK_PERIOD_MS);
  }
}

static void lcdUpdateTask(void* parameters) {
  while(1) {
    if(DEBUG_TASKS) SERIAL_PORT.println("L");

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
  generateTask(blinkTask, "Blink", NULL, LED_PRIORITY);

  // Create controller poll task
  generateTask(pollControllerTask, "Controller poll", NULL, CONTROLLER_POLL_PRIORITY);

  // Create update tasks
  generateTask(drivetrainUpdateTask, "Drivetrain update", NULL, DRIVETRAIN_UPDATE_PRIORITY);
  generateTask(appendageUpdateTask, "Appendage update", NULL, APPENDAGE_UPDATE_PRIORITY);
  generateTask(lcdUpdateTask, "LCD update", NULL, LED_PRIORITY);

  SERIAL_PORT.println("Completed init");
  vTaskDelete(NULL);
}

void setup()
{
  // As the very first thing, initialize UART
  SERIAL_PORT.begin(9600);

  // Create init task
  generateTask(initTask, "Init", NULL, 0);

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
