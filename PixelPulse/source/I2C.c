#include <MKL25Z4.H>
#include "i2c.h"
#include "delay.h"
#include "fsl_debug_console.h"

//init i2c0
void i2c_init(void)
{
	//clock i2c peripheral and port E
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= (SIM_SCGC5_PORTC_MASK);
	//set pins to I2C function
	PORTC->PCR[8] |= PORT_PCR_MUX(2);
	PORTC->PCR[9] |= PORT_PCR_MUX(2);
	//set to 400k baud
	//baud = bus freq/(scl_div+mul)
 	//60 = 24M/(400k); icr=0x11 sets scl_div to 56
	// Disable I2C module
 	I2C0->F = (I2C_F_ICR(0x11) | I2C_F_MULT(0));

	//enable i2c and set to master mode
	I2C0->C1 |= (I2C_C1_IICEN_MASK);

	// Select high drive mode
	I2C0->C2 |= (I2C_C2_HDRS_MASK);

}


////send start sequence
void i2c_start()
{
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
}

void i2c_write_byte(uint8_t data)
{
// input must be in form of 0x0c or 0xc
// For instructions RS & RW =0
uint8_t EHi = 0x0D;
uint8_t ELo = 0x08;
Delay(1000);
I2C_TRAN;
I2C_M_START;
//I2C1->S |= I2C_S_IICIF_MASK;
I2C0->D = LCD_ADDR;
I2C_WAIT;
Delay(30000); //1ms delay
;
I2C0->D = ((data & 0xF0) | EHi); //higher
I2C_WAIT;
Delay(30000);

I2C0->D = ((data & 0xF0) | ELo);
I2C_WAIT;
Delay(30000);

I2C0->D = (((data << 4) & 0xF0) | EHi);
I2C_WAIT;
Delay(30000);
;
I2C0->D = (((data << 4) & 0xF0) | ELo);
I2C_WAIT;
Delay(30000);

I2C_M_STOP;

}

void i2c_custom_byte(uint8_t data)
{
// input must be in form of 0x0c or 0xc
// For instructions RS & RW =0
uint8_t EHi = 0x0D;
uint8_t ELo = 0x08;
Delay(1000);
I2C_TRAN;
I2C_M_START;
//I2C1->S |= I2C_S_IICIF_MASK;
I2C0->D = LCD_ADDR;
I2C_WAIT;
Delay(30000); //1ms delay
;
I2C0->D = ((data & 0xF0) | EHi | 0x40); //higher
I2C_WAIT;
Delay(30000);

I2C0->D = ((data & 0xF0) | ELo | 0x40);
I2C_WAIT;
Delay(30000);

I2C0->D = (((data << 4) & 0xF0) | EHi | 0x40);
I2C_WAIT;
Delay(30000);
;
I2C0->D = (((data << 4) & 0xF0) | ELo | 0x40);
I2C_WAIT;
Delay(30000);

I2C_M_STOP;

}

void LCD_Write_4bit_CMD(uint8_t data)
{
// input must be in form of 0x0c or 0xc
// For instructions RS & RW =0
//PRINTF("AT START\n\r");
uint8_t EHi = 0x0C;
uint8_t ELo = 0x08;
Delay(10000);
I2C_TRAN;
I2C_M_START;
//I2C1->S |= I2C_S_IICIF_MASK;
I2C0->D = LCD_ADDR;
I2C_WAIT;
Delay(30000); //1ms delay
;
I2C0->D = ((data & 0xF0) | EHi); //higher
I2C_WAIT;
Delay(30000);

I2C0->D = ((data & 0xF0) | ELo);
I2C_WAIT;
Delay(30000);

I2C0->D = (((data << 4) & 0xF0) | EHi);
I2C_WAIT;
Delay(30000);
;
I2C0->D = (((data << 4) & 0xF0) | ELo);
I2C_WAIT;
Delay(30000);

I2C_M_STOP;

}
