#ifndef LCD_H
#define LCD_H
#include <stdint.h>
#include "delay.h"
#include "I2C.h"

void init_I2C_LCD(void);
void create_custom_char(void);
void testLCD(void);
void i2c_write_string(const char* str);
void automatedTest(void);
#endif
