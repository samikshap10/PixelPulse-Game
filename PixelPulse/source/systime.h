#ifndef SYSTIME_H
#define SYSTIME_H

#include "MKL25Z4.h"
#include "core_cm0plus.h"

extern uint32_t msTicks;
void SysTick_Init(void);

#endif
