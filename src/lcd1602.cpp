#include "LCD1602.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Arduino.h>
#include <Wire.h>
#include <utils.h>

void lcd1602_init(LCD1602 *display)
{
    display->sdaPin = LCD1602_SDA;
    display->sclPin = LCD1602_SCL;

    Wire.begin((uint32_t)display->sdaPin, (uint32_t)display->sclPin);

    Wire.beginTransmission(LCD1602_I2C_ADDR);
    SERIAL_PORT.println("Attempting 1!");
    if(Wire.endTransmission() == 0) {
        SERIAL_PORT.println("Found device 1!");
    }
}

void lcd1602_command(LCD1602* display, uint8_t command) {
    Wire.beginTransmission(LCD1602_I2C_ADDR);
    Wire.write(command);
    Wire.endTransmission();
}

void lcd1602_toggle(LCD1602* display) {
    if(display->enabled) lcd1602_command(display, 0x00);
    else lcd1602_command(display, 0x00);
}

void lcd1602_clear(LCD1602* display) {
    if(display->enabled) lcd1602_command(display, 0x01);
}
