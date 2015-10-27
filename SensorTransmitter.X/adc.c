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
	ADCON1 = 0x00;	//Sets ADCON1
	
	switch (channel)
	{
		case 0: 
			TRISAbits.TRISA0 = 1;
			ANS0 = 1; //Sets the analogue select port to ANS0
			ADCON0 = 0xC0;	//Sets ADCON0
			CHS0 = 0;
			CHS1 = 0;
			CHS2 = 0;
			break;
		case 1: 
			TRISAbits.TRISA1 = 1;
			ANS1 = 1; //Sets the analogue select port to ANS0
			ADCON0 = 0xC0;	//Sets ADCON0
			CHS0 = 1;
			CHS1 = 0;
			CHS2 = 0;
			break;
		case 2: 
			TRISAbits.TRISA2 = 1;
			ANS2 = 1; //Sets the analogue select port to ANS0
			ADCON0 = 0xC0;	//Sets ADCON0
			CHS0 = 0;
			CHS1 = 1;
			CHS2 = 0;
		break;
		case 3: 
			TRISAbits.TRISA3 = 1;
			ANS3 = 1; //Sets the analogue select port to ANS0
			ADCON0 = 0xC0;	//Sets ADCON0
			CHS0 = 1;
			CHS1 = 1;
			CHS2 = 0;
		break;
		case 4: 
			TRISAbits.TRISA4 = 1;
			ANS4 = 1; //Sets the analogue select port to ANS0
			ADCON0 = 0xC0;	//Sets ADCON0
			CHS0 = 0;
			CHS1 = 0;
			CHS2 = 1;
		break;
		case 5: 
			TRISBbits.TRISB6 = 1;
			ANS5 = 1; //Sets the analogue select port to ANS0
			ADCON0 = 0xC0;	//Sets ADCON0
			CHS0 = 1;
			CHS1 = 0;
			CHS2 = 1;
		break;
		case 6: 
			TRISBbits.TRISB7 = 1;
			ANS6 = 1; //Sets the analogue select port to ANS0
			ADCON0 = 0xC0;	//Sets ADCON0
			CHS0 = 0;
			CHS1 = 1;
			CHS2 = 1;
		break;
		default:
			TRISAbits.TRISA0 = 1;
			ANS0 = 1; //Sets the analogue select port to ANS0
			ADCON0 = 0xC0;	//Sets ADCON0
			CHS0 = 0;
			CHS1 = 0;
			CHS2 = 0;
		break;
	}
    TRISAbits.TRISA3 = 1;
    ANS3 = 1;
    VCFG1 = 1;
	VCFG0 = 0;
    ADFM = 1;
	ADON = 1; 			//Turn on the ADC
}	

uint16_t adcRead(void)
{
	GO_nDONE = 1; //Activate ADC conversion
    while(GO_nDONE); //Wait until the conversion finishes
    uint16_t result = ADRESH;
    result <<= 8;
    result += ADRESL;
    return result;
}