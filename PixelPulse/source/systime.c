/*
 * File: systime.c
 * Author: Samiksha Patil
 * Description: This file contains functions for initializing and handling the system time
 *              using the SysTick timer on the MKL25Z4 microcontroller.
 */

#include "systime.h"

uint32_t msTicks = 0;
/*!
 * @brief Initializes systick
 */
void SysTick_Init(void)
{
    SysTick->LOAD = SystemCoreClock / 1000 - 1; // Set reload register for 1 ms interrupts
    NVIC_SetPriority (SysTick_IRQn, 3);
    SysTick->VAL = 0; // Clear current value to 0
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk; // Enable SysTick IRQ and SysTick Timer
}

/*!
 * @brief Systick handler function
 */
void SysTick_Handler(void)
{
    msTicks++; // Increment the millisecond counter
}

