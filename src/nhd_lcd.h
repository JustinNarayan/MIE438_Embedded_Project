#ifndef NHD_LCD_H
#define NHD_LCD_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint8_t csPin;
    uint8_t rstPin;
    uint8_t regPin;
    uint8_t sclPin;
    uint8_t siPin;
} NHD_LCD;

void NHD_LCD_init(NHD_LCD *display, uint8_t csPin, uint8_t rstPin, uint8_t regPin, uint8_t sclPin, uint8_t siPin);
void NHD_LCD_begin(NHD_LCD *display);
void NHD_LCD_send(NHD_LCD *display, uint8_t message, bool is_data);
void NHD_LCD_display(NHD_LCD *display, unsigned char *lcd_string);

#endif