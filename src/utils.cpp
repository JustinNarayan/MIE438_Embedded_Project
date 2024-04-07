#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <string.h>
#include "utils.h"

void generateTask(TaskFunction_t taskFunction, const char *taskName, void *taskParameters)
{
    portBASE_TYPE s1;
    s1 = xTaskCreate(taskFunction, taskName, 4096, NULL, configMAX_PRIORITIES, NULL);

    if (s1 != pdPASS)
    {
        SERIAL_PORT.println("Task creation problem");
        while (1)
            ;
    }
}