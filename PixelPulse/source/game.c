#include "button.h"
#include "MKL25Z4.h"
#include "LCD.h"
#include "delay.h"
#include "fsl_debug_console.h"

#define SPRITE_RUN1 0x00
#define SPRITE_RUN2 0x01
#define SPRITE_JUMP 0x02
#define SPRITE_JUMP_UPPER '.'         // Use the '.' character for the head
#define SPRITE_JUMP_LOWER 0x03
#define SPRITE_TERRAIN_EMPTY ' '      // User the ' ' character
#define SPRITE_TERRAIN_SOLID 0x04
#define SPRITE_TERRAIN_SOLID_RIGHT 0x05
#define SPRITE_TERRAIN_SOLID_LEFT 0x06

#define BOY_HORIZONTAL_POSITION 0x01    // Horizontal position of hero on screen

#define TERRAIN_WIDTH 16
#define TERRAIN_EMPTY 0
#define TERRAIN_LOWER_BLOCK 0x42
#define TERRAIN_UPPER_BLOCK 0x16

#define BOY_POSITION_OFF 0          // boy is invisible
#define BOY_POSITION_RUN_LOWER_1 1  // boy is running on lower row (pose 1)
#define BOY_POSITION_RUN_LOWER_2 2  //                              (pose 2)

#define BOY_POSITION_JUMP_1 3       // Starting a jump
#define BOY_POSITION_JUMP_2 4       // Half-way up
#define BOY_POSITION_JUMP_3 5       // Jump is on upper row
#define BOY_POSITION_JUMP_4 6       // Jump is on upper row
#define BOY_POSITION_JUMP_5 7       // Jump is on upper row
#define BOY_POSITION_JUMP_6 8       // Jump is on upper row
#define BOY_POSITION_JUMP_7 9       // Half-way down
#define BOY_POSITION_JUMP_8 10      // About to land

#define BOY_POSITION_RUN_UPPER_1 11 // boy is running on upper row (pose 1)
#define BOY_POSITION_RUN_UPPER_2 12 //                              (pose 2)

static char terrainUpper[TERRAIN_WIDTH + 1];
static char terrainLower[TERRAIN_WIDTH + 1];

uint8_t wasButtonPressed = 1;
uint8_t i = 0;
uint8_t isCrashed = 1;
uint8_t flag = 1;
//uint8_t i = 0;
int cursorPos = 0; // Initial position of the cursor
int pos1 = 0x27;
int pos2 = 0x28;
int pos3 = 0x29;
int pos4 = 0x30;
int pos5 = 0x31;
int pos6 = 0x32;
int pos7 = 0x33;
int pos8 = 0x34;
int pos9 = 0x35;
int pos10 = 0x36;

void init_game_fun(void) {

	for (uint8_t i = 0; i < 4; ++i) {
		terrainUpper[i] = SPRITE_TERRAIN_SOLID;
		terrainLower[i] = SPRITE_TERRAIN_SOLID;
	}
	for (uint8_t i = 4; i < 8; ++i) {
		terrainUpper[i] = SPRITE_TERRAIN_EMPTY;
		terrainLower[i] = SPRITE_TERRAIN_EMPTY;
	}
	for (uint8_t i = 8; i < 12; ++i) {
		terrainUpper[i] = SPRITE_TERRAIN_SOLID_LEFT;
		terrainLower[i] = SPRITE_TERRAIN_SOLID_LEFT;
	}
	for (uint8_t i = 12; i < 16; ++i) {
		terrainUpper[i] = SPRITE_TERRAIN_EMPTY;
		terrainLower[i] = SPRITE_TERRAIN_EMPTY;
	}
	terrainUpper[16] = '\0';
	terrainLower[16] = '\0';
	terrainLower[0] = SPRITE_TERRAIN_SOLID;
}

// Slide the terrain to the left in half-character increments
//
void advanceTerrain(char *terrain, uint8_t newTerrain) {
	for (int i = 0; i < TERRAIN_WIDTH; ++i) {
		char current = terrain[i];
		char next = (i == TERRAIN_WIDTH - 1) ? newTerrain : terrain[i + 1];
		switch (current) {
		case SPRITE_TERRAIN_EMPTY:
			terrain[i] =
					(next == SPRITE_TERRAIN_SOLID) ?
							SPRITE_TERRAIN_SOLID_RIGHT : SPRITE_TERRAIN_EMPTY;
			break;
		case SPRITE_TERRAIN_SOLID:
			terrain[i] =
					(next == SPRITE_TERRAIN_EMPTY) ?
							SPRITE_TERRAIN_SOLID_LEFT : SPRITE_TERRAIN_SOLID;
			break;
		case SPRITE_TERRAIN_SOLID_RIGHT:
			terrain[i] = SPRITE_TERRAIN_SOLID;
			break;
		case SPRITE_TERRAIN_SOLID_LEFT:
			terrain[i] = SPRITE_TERRAIN_EMPTY;
			break;
		}
	}
}
//void i2c_write_string(const char* str) {
//    // Loop through each character in the string until the null terminator is reached
//    for (size_t i = 0; str[i] != '\0'; ++i) {
//        // Send each character over I2C
//    	i2c_write_byte(str[i]);
//    }
//}

void game_play(void) {

//	static uint8_t currentEndPos, currentStartPos = 0;
//	uint8_t currentBoyPos = 0;
//	PRINTF("crash value is %d\n\r", isCrashed);

	if(isCrashed == 1 && flag == 1){
	LCD_Write_4bit_CMD(0x01);
	LCD_Write_4bit_CMD(0x80 | 0x00);
	i2c_write_string("  PRESS BUTTON!!  ");
	flag = 0;
//	LCD_Write_4bit_CMD(0x80 | 0x14);
//	i2c_write_string("  TO PLAY AGAIN!!  ");

	}
	if (isButtonPressed){
		PRINTF("BUTTON PRESSED\n\r");
		isCrashed = 0;
		LCD_Write_4bit_CMD(0x01);
	}

	if(isCrashed == 0){

	for (uint8_t j = 0; j < 26; ++j) {
		LCD_Write_4bit_CMD(0x80 | pos1);
		i2c_write_byte(terrainLower[0]); // Print the jth element of terrainLower array
		pos1--;
//		currentStartPos = pos4;
		LCD_Write_4bit_CMD(0x80 | pos2);
		i2c_write_byte(terrainLower[0]); // Print the jth element of terrainLower array
		pos2--;
		LCD_Write_4bit_CMD(0x80 | pos3);
		i2c_write_byte(terrainLower[0]); // Print the jth element of terrainLower array
		pos3--;
		LCD_Write_4bit_CMD(0x80 | pos4);
		i2c_write_byte(terrainLower[6]); // Print the jth element of terrainLower array
		pos4--;
		LCD_Write_4bit_CMD(0x80 | pos5);
		i2c_write_byte(terrainLower[6]); // Print the jth element of terrainLower array
		pos5--;
		LCD_Write_4bit_CMD(0x80 | pos6);
		i2c_write_byte(terrainLower[6]); // Print the jth element of terrainLower array
		pos6--;
//		currentEndPos = pos6;
		Delay(60000);
		if (isButtonPressed) {
			i++;
			if (i % 2 == 0) {
				LCD_Write_4bit_CMD(0x80 | 0x04);
				i2c_write_byte(0x07);
				LCD_Write_4bit_CMD(0x80 | 0x16);
				i2c_write_byte(0x00);
//				currentBoyPos = ( 0x80 | 0x16 );
				isButtonPressed = 0;
				i = 0;
			} else {
				PRINTF("inside else\n\r");
				LCD_Write_4bit_CMD(0x80 | 0x16);
				i2c_write_byte(0x07);
				LCD_Write_4bit_CMD(0x80 | 0x04);
				i2c_write_byte(0x02);
//				currentBoyPos = ( 0x80 | 0x04 );
				isButtonPressed = 0;
			}
		}

//		if( currentBoyPos <= currentStartPos && currentBoyPos >= currentEndPos)
//		{
//			PRINTF("StartPos is %2x and EndPos is %2x \n\r",currentStartPos, currentEndPos );
//			PRINTF("CRASHHH");
//			isCrashed = 1;
//		}
		if (pos6 == 0x00) {
			pos1 = 0x27;
			pos2 = 0x28;
			pos3 = 0x29;
			pos4 = 0x30;
			pos5 = 0x31;
			pos6 = 0x32;
			pos7 = 0x33;
			pos8 = 0x34;
			pos9 = 0x35;
			pos10 = 0x36;
		}
	}
	}
}
