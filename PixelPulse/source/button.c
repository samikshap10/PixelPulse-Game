#include "button.h"
#include "fsl_debug_console.h"

#define DEBOUNCE_TIME_MS 50 // Adjust debounce time as needed

uint8_t isButtonPressed= 0;
volatile uint32_t lastTriggerTime = 0; // Variable to store the last trigger time

const uint32_t INPUT_CONFIG =   PORT_PCR_IRQC(0b1000) | // IRQ Falling Edge
                                PORT_PCR_MUX(001)   | // Pin set to GPIO
                                PORT_PCR_DSE(0)     | // Low drive strength
                                PORT_PCR_PFE(0)     | // Passive filter disabled, try enabling if noisy
                                PORT_PCR_SRE(0)     | // Fast slew rate, look up what slow would mean
                                PORT_PCR_PE(1)      | // Pull resistor is disabled
                                PORT_PCR_PS(1);       // Pull resistor is set to pulldown (but is still disabled)
/*!
 * @brief Initializing Hardware Interrupt
 */
void initializeIRQ(){
	 NVIC_EnableIRQ(PORTD_IRQn);
	 // Enable and setup 3 pins in PORTA
	 SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;    //Enable the clock to port D
	 PORTD->PCR[5] = INPUT_CONFIG;     //Setup PTD5
}

/*!
 * @brief PortD Interrupt Handler
 */
void PORTD_IRQHandler(void){

//	PRINTF("MS TICKS %d\r\n", msTicks);

	uint32_t currentTime = msTicks;

	// Check if enough time has elapsed since the last trigger
	if ((currentTime - lastTriggerTime) >= DEBOUNCE_TIME_MS){
	PRINTF("Interrupt from PORT D calling COP FUNCTION:\r\n");
	// Update the last trigger time
	lastTriggerTime = currentTime;
	}
    //CLEAR INTERRUPT FLAG
    PORTD->ISFR = 0xFFFFFFFF;
}
