#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <string.h>
#include "utils.h"

void generateTask(TaskFunction_t taskFunction, const char *taskName, void *taskParameters)
{
    portBASE_TYPE s1;
    s1 = xTaskCreate(taskFunction, taskName, configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    if (s1 != pdPASS)
    {
        // Serial.println("Task creation problem");
        while (1)
            ;
    }
}