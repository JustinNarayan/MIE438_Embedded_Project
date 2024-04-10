#ifndef LCD1602_H
#define LCD1602_H

#include <stdint.h>
#include <stdbool.h>

#define ROWS 2
#define COLS 16
#define LCD1602_I2C_ADDR 0x27

typedef struct
{
    uint8_t sdaPin;
    uint8_t sclPin;
    bool enabled;
    uint8_t cursorPosition;
} LCD1602;

void lcd1602_init(LCD1602 *display);
void lcd1602_command(LCD1602 *display, uint8_t command);

void lcd1602_toggle(LCD1602 *display);
void lcd1602_clear(LCD1602 *display);

#endif