/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    PixelPulse.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "LCD.h"
#include "I2C.h"
#include "delay.h"
#include "button.h"
#include "game.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

uint8_t LCDTestFlag = 1;

int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    SysTick_Init();
    i2c_init();
    init_I2C_LCD();
    initializeIRQ();
    create_custom_char();
    testLCD();	//TEST LCD - Happy Cases
    automatedTest(); //Automated test for corner cases

    isButtonPressed= 0; //Making the button pressed 0, as it was acting different before

    while(1) {

    	game_play(); //Game Play function
    }
    return 0 ;
}
