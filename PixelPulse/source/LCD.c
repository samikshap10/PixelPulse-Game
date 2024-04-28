#include <MKL25Z4.H>
#include "I2C.h"
#include "LCD.h"
#include "fsl_debug_console.h"


void init_I2C_LCD(void)
{
//PRINTF(" IN INIT\n\r");

LCD_Write_4bit_CMD(0x02); // set 4 bit
Delay(10000);
LCD_Write_4bit_CMD(0x28); // Function Set  - 4 bit Interface, 1 = 2 lines, 0 = 5x8 font
Delay(10000);
LCD_Write_4bit_CMD(0x0F); // Clear Screen
Delay(10000);
LCD_Write_4bit_CMD(0x01); // Clear Screen
Delay(10000);

}

