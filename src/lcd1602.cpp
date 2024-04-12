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
    display->enabled = 0;

    Wire.begin((uint32_t)display->sdaPin, (uint32_t)display->sclPin);

    Wire.beginTransmission(LCD1602_I2C_ADDR);
    SERIAL_PORT.printf("Attempting to contact I2C device %x!\n", LCD1602_I2C_ADDR);
    if(Wire.endTransmission() == 0) {
        SERIAL_PORT.printf("Found I2C device %x!\n", LCD1602_I2C_ADDR);
    }

    // Init commands
    // lcd1602_command(display, 0x38); // 8-bit MPU, 2-line, small font
    // lcd1602_command(display, 0x01); // clear
    lcd1602_command(display, 0x0C); // display on, cursor on, blink on

    // lcd1602_command(display, 0x02); // return home (cursor?)
    // lcd1602_command(display, 0x38); // 8-bit MPU, 2-line, small font
    // lcd1602_command(display, 0x06); // increment rightward, do not shift
}

void lcd1602_command(LCD1602* display, uint8_t command) {
    Wire.beginTransmission(LCD1602_I2C_ADDR);
    Wire.write(command);
    Wire.endTransmission();
}

void lcd1602_toggle(LCD1602* display) {
    if(display->enabled) {
        lcd1602_command(display, 0x00);
        display->enabled = 0;
    } else {
        lcd1602_command(display, 0x0C);
        display->enabled = 1;
    }
}

void lcd1602_clear(LCD1602* display) {
    // if(display->enabled) lcd1602_command(display, 0x01);
}
