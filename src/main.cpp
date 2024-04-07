#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <utils.h>
#include <l298n.h>
#include <drivetrain.h>

static void blinkLED(void *parameters)
{
  uint32_t ledTime = *((uint32_t *)parameters);
  while (1)
  { 
    digitalWrite(LED_PIN, HIGH);              // Turn LED on
    vTaskDelay(ledTime); // Delay for LED_TIME ms
    digitalWrite(LED_PIN, LOW);               // Turn LED off
    vTaskDelay(ledTime); // Delay for LED_TIME ms
  }
}

static void initTask(void *parameters)
{
  // Enable LED
  pinMode(LED_PIN, OUTPUT);

  uint32_t ledTimeParam = LED_TIME;

  // Create blink task
  generateTask(blinkLED, "Blink", &ledTimeParam);

  // drivetrain* driver;
  // drivetrain_init(driver);

  while (1)
  { 
    SERIAL_PORT.println("!");
    vTaskDelay(4000 / portTICK_PERIOD_MS);
  }

  // Delete this init task
  vTaskDelete(NULL);
}

void setup()
{
  // As the very first thing, initialize UART
  SERIAL_PORT.begin(9600);
  SERIAL_PORT.println("Serial communication initialized.");

  // Create init task
  generateTask(initTask, "Init", NULL);

  // Create FreeRTOS scheduler
  vTaskStartScheduler();

  // We should never reach this point
  SERIAL_PORT.println("Insufficient RAM for FreeRTOS/");
  while (1)
    ;
}

void loop()
{
  // Empty loop, not used because FreeRTOS is managing tasks
  SERIAL_PORT.println("Should not be here! FreeRTOS should be managing tasks.");
}
