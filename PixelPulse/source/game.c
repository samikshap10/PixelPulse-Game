#include "button.h"
#include "MKL25Z4.h"
#include "LCD.h"
#include "delay.h"
#include "fsl_debug_console.h"

#define SPRITE_RUN1 0x01
#define SPRITE_RUN2 0x02
#define SPRITE_JUMP 0x03
#define SPRITE_JUMP_UPPER '.'         // Use the '.' character for the head
#define SPRITE_JUMP_LOWER 0x04
#define SPRITE_TERRAIN_EMPTY ' '      // User the ' ' character
#define SPRITE_TERRAIN_SOLID 0x05
#define SPRITE_TERRAIN_SOLID_RIGHT 0x06
#define SPRITE_TERRAIN_SOLID_LEFT 0x07

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
int cursorPos = 0; // Initial position of the cursor
int pos = 27;

void init_game_fun(void){

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
	  terrainUpper[12] = '\0';
	  terrainLower[12] = '\0';

}

// Slide the terrain to the left in half-character increments
//
void advanceTerrain(char* terrain, uint8_t newTerrain){
  for (int i = 0; i < TERRAIN_WIDTH; ++i) {
    char current = terrain[i];
    char next = (i == TERRAIN_WIDTH-1) ? newTerrain : terrain[i+1];
    switch (current){
      case SPRITE_TERRAIN_EMPTY:
        terrain[i] = (next == SPRITE_TERRAIN_SOLID) ? SPRITE_TERRAIN_SOLID_RIGHT : SPRITE_TERRAIN_EMPTY;
        break;
      case SPRITE_TERRAIN_SOLID:
        terrain[i] = (next == SPRITE_TERRAIN_EMPTY) ? SPRITE_TERRAIN_SOLID_LEFT : SPRITE_TERRAIN_SOLID;
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



void game_play(void){

	//	static uint8_t boyPos;
	//	static byte newTerrainType = TERRAIN_EMPTY;
	//	static byte newTerrainDuration = 1;
	//	static bool playing = false;
	//	static bool blink = false;
	//	static unsigned int distance = 0;
//	LCD_Write_4bit_CMD(0x01);
	if (isButtonPressed) {

		i++;
		PRINTF("I VALUE IS %d\n\r", i);
		if(i % 2 == 0){
			PRINTF("inside if\n\r");
			LCD_Write_4bit_CMD(0x80| 0x43);
			i2c_write_byte(0x07);
			LCD_Write_4bit_CMD(0x80| 0x16);
			i2c_write_byte(0x00);
			isButtonPressed = 0;
			i = 0;
		}else {
			PRINTF("inside else\n\r");
			LCD_Write_4bit_CMD(0x80| 0x16);
			i2c_write_byte(0x07);
			LCD_Write_4bit_CMD(0x80| 0x43);
			i2c_write_byte(0x02);
			isButtonPressed = 0;
		}
	}

if(pos >= 0x14 ){
	for (uint8_t i = 0; i < 12; ++i) {
		LCD_Write_4bit_CMD(0x80| pos);
		pos--;
		i2c_write_byte(terrainLower[i]);
	}
} else { pos = 0x27; }



}
