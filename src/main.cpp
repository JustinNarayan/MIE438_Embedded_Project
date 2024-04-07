#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <utils.h>
#include <l298n.h>
#include <drivetrain.h>
#include <controller.h>

#define ALERT_TIME 500

// Static variables
static Controller controller;
static L298N leftMotor;
static L298N rightMotor;
static drivetrain driver;

static void blinkTask(void *parameters)
{
  while (1)
  { 
    SERIAL_PORT.println("HIGH");
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(LED_TIME / portTICK_PERIOD_MS);
    SERIAL_PORT.println("LOW");
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


static void initTask(void *parameters)
{
  // Enable LED
  pinMode(LED_PIN, OUTPUT);

  // Instantiate drivetrain
  drivetrain_init(&driver, &leftMotor, &rightMotor);

  // Instantiate controller
  controller_init(&controller);

  // Create blink task
  generateTask(blinkTask, "Blink", NULL);

  // Create controller poll task
  generateTask(pollControllerTask, "Controller poll", NULL);

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
