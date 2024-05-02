
/*
 * File: delay.c
 * Author: Samiksha Patil
 * Description: This file contains a function for generating a delay using software loops
 *              on the MKL25Z4 microcontroller.
 */
#include <MKL25Z4.H>

/*!
 * @brief Delay function
 * @param cnt Number of loops for delay
 */
void Delay(uint16_t cnt)
{
  int i,j;

    // 1 instruction takes 1/48000000 = 20nsec to execute
  // at 48Mhz system clock
    for (j=0; j<5; j++)
    {
        for(i=0;i<cnt;i++);
    }
}
