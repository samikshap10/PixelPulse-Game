/*
 * File: game.c
 * Author: Samiksha Patil
 * Description: This file contains functions for controlling the gameplay of a simple game
 *              using an LCD display and a button on the MKL25Z4 microcontroller.
 */
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

/*!
 * @brief Game play function
 */

void game_play(void) {

	if(isCrashed == 1 && flag == 1){
	LCD_Write_4bit_CMD(0x01);
	LCD_Write_4bit_CMD(0x80 | 0x00);
	i2c_write_string("  PRESS BUTTON!!  ");
	flag = 0;

	}
	if (isButtonPressed){
		PRINTF("BUTTON PRESSED\n\r");
		isCrashed = 0;
		LCD_Write_4bit_CMD(0x01);
	}

	if(isCrashed == 0){

	for (uint8_t j = 0; j < 26; ++j) {
		LCD_Write_4bit_CMD(0x80 | pos1);
		i2c_write_byte(SPRITE_TERRAIN_SOLID); // Print the jth element of terrainLower array
		pos1--;
		LCD_Write_4bit_CMD(0x80 | pos2);
		i2c_write_byte(SPRITE_TERRAIN_SOLID); // Print the jth element of terrainLower array
		pos2--;
		LCD_Write_4bit_CMD(0x80 | pos3);
		i2c_write_byte(SPRITE_TERRAIN_SOLID); // Print the jth element of terrainLower array
		pos3--;
		LCD_Write_4bit_CMD(0x80 | pos4);
		i2c_write_byte(SPRITE_TERRAIN_EMPTY); // Print the jth element of terrainLower array
		pos4--;
		LCD_Write_4bit_CMD(0x80 | pos5);
		i2c_write_byte(SPRITE_TERRAIN_EMPTY); // Print the jth element of terrainLower array
		pos5--;
		LCD_Write_4bit_CMD(0x80 | pos6);
		i2c_write_byte(SPRITE_TERRAIN_EMPTY); // Print the jth element of terrainLower array
		pos6--;
		Delay(60000);
		if (isButtonPressed) {
			i++;
			if (i % 2 == 0) {
				LCD_Write_4bit_CMD(0x80 | 0x04);
				i2c_write_byte(0x07);
				LCD_Write_4bit_CMD(0x80 | 0x16);
				i2c_write_byte(SPRITE_RUN1);
				isButtonPressed = 0;
				i = 0;
			} else {
				PRINTF("inside else\n\r");
				LCD_Write_4bit_CMD(0x80 | 0x16);
				i2c_write_byte(0x07);
				LCD_Write_4bit_CMD(0x80 | 0x04);
				i2c_write_byte(SPRITE_JUMP);
				isButtonPressed = 0;
			}
		}

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
