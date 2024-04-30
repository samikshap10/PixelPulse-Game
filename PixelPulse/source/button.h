#ifndef BUTTON_H
#define BUTTON_H

#include "pin_mux.h"
#include "MKL25Z4.h"
#include "systime.h"

extern uint8_t isButtonPressed;

void initializeIRQ();

#endif
