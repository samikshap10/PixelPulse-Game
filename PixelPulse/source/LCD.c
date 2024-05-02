/*
 * File: LCD.c
 * Author: Samiksha Patil
 * Description: This file contains functions for initializing and controlling an LCD display
 *              using the I2C protocol on the MKL25Z4 microcontroller.
 */
#include <MKL25Z4.H>
#include "I2C.h"
#include "LCD.h"
#include "fsl_debug_console.h"


static uint8_t run_position_1[] = {
    0x0C, 0x0C, 0x00, 0x0E, 0x1C, 0x0C, 0x1A, 0x13, // Run position 1
	0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x0E, // Run position 2
	0x0C, 0x0C, 0x00, 0x1E, 0x0D, 0x1F, 0x10, 0x00, // Jump
	0x1E, 0x0D, 0x1F, 0x10, 0x00, 0x00, 0x00, 0x00, // Jump lower
	0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, // Ground
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, // Ground right
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, // Ground left
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


void init_I2C_LCD(void)
{
LCD_Write_4bit_CMD(0x02); // set 4 bit
Delay(10000);
LCD_Write_4bit_CMD(0x20); // Function Set  - 4 bit Interface, 0 = 1 lines, 0 = 5x8 font
Delay(10000);
LCD_Write_4bit_CMD(0x0C); // Display Set, Cursor position and cursor blinking OFF
Delay(10000);
LCD_Write_4bit_CMD(0x01); // Clear Screen
Delay(10000);

}
void i2c_write_string(const char* str) {
    // Loop through each character in the string until the null terminator is reached
    for (size_t i = 0; str[i] != '\0'; ++i) {
        // Send each character over I2C
    	i2c_write_byte(str[i]);
    }
}

void create_custom_char(void){

	LCD_Write_4bit_CMD(0x40 | 0x00);
    for (int i = 0; i < 64; i++) {
    	i2c_write_byte(run_position_1[i]);
    }

    LCD_Write_4bit_CMD(0x80| 0x40);
    LCD_Write_4bit_CMD(0x01);

}

void testLCD(void){

    LCD_Write_4bit_CMD(0x80 | 0x00);
    i2c_write_string("LCD TEST LINE 1");

    LCD_Write_4bit_CMD(0x80 | 0x14);
    i2c_write_string("LCD TEST LINE 2");
    for(int i =0; i<=100; i++){
    	Delay(1000000000);
    }

}

void automatedTest(void){
	LCD_Write_4bit_CMD(0x01);
    LCD_Write_4bit_CMD(0x80 | 0x00);
    i2c_write_byte(0x00);

    LCD_Write_4bit_CMD(0x80 | 0x13);
    i2c_write_byte(0x01);

    LCD_Write_4bit_CMD(0x80 | 0x0A);
    i2c_write_byte(0x00);

    LCD_Write_4bit_CMD(0x80 | 0x1E);
    i2c_write_byte(0x01);

    LCD_Write_4bit_CMD(0x80 | 0x14);
    i2c_write_byte(0x00);

    LCD_Write_4bit_CMD(0x80 | 0x27);
    i2c_write_byte(0x01);

    LCD_Write_4bit_CMD(0x80 | 0x40);
    i2c_write_byte(0x00);

    LCD_Write_4bit_CMD(0x80 | 0x54);
    i2c_write_byte(0x01);

    for(int i =0; i<=100; i++){
    	Delay(1000000000);
    }
}

