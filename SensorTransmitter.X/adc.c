/**
@file adc.c
@brief A set of functions for you
*/

//Includes
#include "adc.h"

/**
*@brief An initalization function for the ADC on port RB7
*@retval
*/
void adcInit(uint8_t channel)
{
	TRISAbits.TRISA4 = 1;
    ANSELAbits.ANSA4 = 1;
    ADCON0 = 0b00101000;
    ADCON0bits.AD1ON = 1; //Turn on ADC
    ADCON1bits.ADCS = 0b111;
    ADCON1bits.ADPREF = 0b00;
    return;
}	

uint16_t adcRead(void)
{
    GO_nDONE1 = 1; //Activate ADC conversion
    while(GO_nDONE1); //Wait until the conversion finishes
    uint16_t result = AD1RES0H;
    result <<= 8;
    result += AD1RES0L;
    return result;
}