#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <utils.h>
#include <l298n.h>
#include <drivetrain.h>
#include <controller.h>
#include <lcd1602.h>

#define ALERT_TIME 500

// Static variables
static Controller controller;
static L298N leftMotor;
static L298N rightMotor;
static drivetrain driver;
static LCD1602 display;

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

static void alertTask(void *parameters)
{
  while (1)
  { 
    SERIAL_PORT.println("ALERT");
    vTaskDelay(ALERT_TIME / portTICK_PERIOD_MS);
  }
}

static void pollControllerTask(void* parameters) {
  while(1) {
    controller_update(&controller);
  }
}

static void outputControllerTask(void* parameters) {
  while(1) {
    if(controller.direction == DIRECTION_FORWARD)
      SERIAL_PORT.print("Forward\t");
    else if(controller.direction == DIRECTION_BACKWARD)
      SERIAL_PORT.print("Backward\t");
    else
      SERIAL_PORT.print("None\t");

    if(controller.turn == TURN_LEFT)
      SERIAL_PORT.print("Left\t");
    else if(controller.turn == TURN_RIGHT)
      SERIAL_PORT.print("Right\t");
    else
      SERIAL_PORT.print("None\t");

    SERIAL_PORT.println();

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

static void motorTestTask(void* parameters) {
  while(1) {
    SERIAL_PORT.println("Forward!");
    L298N_forward(&leftMotor, 0x10);
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    SERIAL_PORT.println("Halt!");
    L298N_halt(&leftMotor);
    vTaskDelay(500 / portTICK_PERIOD_MS);

    SERIAL_PORT.println("Backward!");
    L298N_forward(&leftMotor, 0x10);
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    SERIAL_PORT.println("Halt!");
    L298N_halt(&leftMotor);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

static void initTask(void *parameters)
{

  vTaskDelay(1000 / portTICK_PERIOD_MS);


  // Enable LED
  pinMode(LED_PIN, OUTPUT);

  // Instantiate drivetrain
  // drivetrain_init(&driver, &leftMotor, &rightMotor);

  // Instantiate controller
  controller_init(&controller);

  // Instantiate LCD
  // lcd1602_init(&display);

  // Create blink task
  generateTask(blinkTask, "Blink", NULL);

  // Create controller poll task
  generateTask(pollControllerTask, "Controller poll", NULL);
  
  // Generate controller output task
  generateTask(outputControllerTask, "Controller output", NULL);

  // Generate motor test task
  // L298N_init(&leftMotor, PD0, PD1, PG0);
  // generateTask(motorTestTask, "Motor test", NULL);

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
