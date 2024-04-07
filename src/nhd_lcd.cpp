#include "NHD_LCD.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Arduino.h>

static uint8_t _buffer[512]; // Buffer to hold pixel data

void NHD_LCD_init(NHD_LCD *display, uint8_t csPin, uint8_t rstPin, uint8_t regPin, uint8_t sclPin, uint8_t siPin)
{
    display->csPin = csPin;   // chip select
    display->rstPin = rstPin; // reset
    display->regPin = regPin; // register select
    display->sclPin = sclPin; // serial clock
    display->siPin = siPin;   // serial in / data
}

void NHD_LCD_begin(NHD_LCD *display)
{
    // configure port as output?
    pinMode(display->csPin, OUTPUT);
    pinMode(display->rstPin, OUTPUT);
    pinMode(display->regPin, OUTPUT);
    pinMode(display->sclPin, OUTPUT);
    pinMode(display->siPin, OUTPUT);

    // Boot sequence
    digitalWrite(display->rstPin, LOW);
    delay(100);
    digitalWrite(display->rstPin, HIGH);
    delay(100);

    // Recommended initialization commands
    NHD_LCD_send(display, 0xA0, 0); // adc select normal
    NHD_LCD_send(display, 0xAE, 0); // display off
    NHD_LCD_send(display, 0xC0, 0); // com scan normal
    NHD_LCD_send(display, 0xA2, 0); // lcd 1/9 bias
    NHD_LCD_send(display, 0x2F, 0); // internal power supply operating mode
    NHD_LCD_send(display, 0x21, 0); // internal resistor ratio
    NHD_LCD_send(display, 0x81, 0); // v0 output voltage register
    NHD_LCD_send(display, 0x3F, 0); // for v0, maximum value 0b0011 1111
}

void NHD_LCD_send(NHD_LCD *display, uint8_t message, bool is_data)
{
    digitalWrite(display->csPin, LOW);      // active low chip select
    digitalWrite(display->regPin, is_data); // send commands

    // Using recommended timing from https://github.com/NewhavenDisplay/NHD-C12832A1Z_Example and https://newhavendisplay.com/content/specs/NHD-C12832A1Z-FSW-FBW-3V3.pdf
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(display->siPin, (message & 0x80) >> 7); // msb
        message << 1;

        digitalWrite(display->sclPin, LOW);
        delay(2);
        digitalWrite(display->sclPin, HIGH);
        delay(2);
        digitalWrite(display->sclPin, LOW);
    }
    digitalWrite(display->csPin, HIGH);

    digitalWrite(display->csPin, HIGH);
}

// to clear the display, pass in NULL for lcd_string
// otherwise, lcd_string is an array of "pixel groups"
// each "pixel group" corresponds to 1 (of 128) columns and 8 (of 32) rows
// stacked left to right, top to bottom
// i.e. 0xFFFF0000 would be the top four rows of this column as on, the rest as off
// overall, there will be 512 entries in LCD string, each for 8 pixels
void NHD_LCD_display(NHD_LCD *display, unsigned char *lcd_string)
{
    unsigned char page = 0xB0;

    NHD_LCD_send(display, 0xAE, 0); // turn off display
    NHD_LCD_send(display, 0x40, 0); // set display start address to 0b0000 0000

    // iterate through all positions in RAM
    // 128 pixels across by 32 pixels down, 8 pixels per page => 4 pages
    for (unsigned int i = 0; i < 4; i++)
    {
        NHD_LCD_send(display, page, 0); // send page address (from the recommended github)
        NHD_LCD_send(display, 0x10, 0); // column address, upper four bits = 0b0000
        NHD_LCD_send(display, 0x00, 0); // column address, lower four bits = 0b0000

        // iterate across row
        for (unsigned int j = 0; j < 128; j++)
        {
            if (lcd_string == NULL)
            {
                NHD_LCD_send(display, 0x00, 1); // clear these pixels
            }
            else
            {
                NHD_LCD_send(display, *lcd_string, 1); // display these pixel for the image
                lcd_string++;
            }
        }
        page++; // Go to next page
    }

    NHD_LCD_send(display, 0xAF, 0); // turn on display
}