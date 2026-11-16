#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#define CS _LATA2
#define DC _LATA3
#define RST _LATB4
#define BL _LATA4

#include <stdint.h>

void display_init(void);
void display_reset(void);
void display_cmd(uint8_t dc, uint8_t cmd);
void display_clear(uint16_t color);

#endif
