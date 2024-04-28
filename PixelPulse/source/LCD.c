#include <MKL25Z4.H>
#include "I2C.h"
#include "LCD.h"
#include "fsl_debug_console.h"

//void init_I2C_LCD(void)
//{
//
//	i2c_write_byte(0x20, 0x80, 0x30);
//	Delay(100);
//	i2c_write_byte(0x20, 0x80, 0x30);
//	Delay(100);
//	i2c_write_byte(0x20, 0x80, 0x30);
//	Delay(100);
//	i2c_write_byte(0x20, 0x80, 0x20);
//	Delay(100);
//	i2c_write_byte(0x20, 0x80, 0x28);
//	Delay(100);
//	i2c_write_byte(0x20, 0x80, 0x01);
//	Delay(100);
//	i2c_write_byte(0x20, 0x80, 0x06);
//	Delay(100);
//
//}

void init_I2C_LCD(void)
{
//PRINTF(" IN INIT\n\r");
// Delay(100);
LCD_Write_4bit_CMD(0x02); // set 4 bit
Delay(10000);
//LCD_Write_4bit_CMD(0x20); // set 4 bit
//Delay(100);
//LCD_Write_4bit_CMD(0x20); // set 4 bit
//Delay(100);
//LCD_Write_4bit_CMD(0x20); // Function Set - 4 bits mode
//Delay(100);
LCD_Write_4bit_CMD(0x28); // Function Set  - 4 bit Interface, 1 = 2 lines, 0 = 5x8 font
Delay(10000);
LCD_Write_4bit_CMD(0x0F); // Clear Screen
Delay(10000);
LCD_Write_4bit_CMD(0x01); // Clear Screen
Delay(10000);
//LCD_Write_4bit_CMD(0x06);
//Delay(10);
//LCD_Write_4bit_CMD(0x80);
//Delay(10000);

}

