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
	TRISAbits.TRISA2 = 1;
    ANSELAbits.ANSA2 = 1;
    ADCON0bits.CHS = 0b00010;
    ADCON0bits.AD1ON = 1; //Turn on ADC
    ADCON1bits.ADCS = 0b111;
    ADCON1bits.ADPREF = 0b00;
    ADCON1bits.ADFM = 1;
    return;
}	

uint16_t adcRead(void)
{
    GO_nDONE1 = 1; //Activate ADC conversion
    while(GO_nDONE1); //Wait until the conversion finishes
    uint16_t result = AD1RES0H;
    result = result << 8;
    result = result + AD1RES0L;
    return result;
}