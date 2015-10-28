#include "usart.h"

void initComms(){
    RX_PIN = 1;
	TX_PIN = 1;
	SPBRG = DIVIDER;     	
	RCSTA = (NINE_BITS|0x90);	
	TXSTA = (SPEED|NINE_BITS|0x20);
}

void transmitOff(){
    TXEN = 0;
}

void transmitOn(){
    TXEN = 1;
}

void putch(unsigned char byte) 
{
	/* output one byte */
	while(!TRMT){
        continue;
    }	/* set when register is empty */
		
	TXREG = byte;
    while(!TRMT){
        continue;
    }	
    
}

unsigned char getch() {
	/* retrieve one byte */
	while(!RCIF)	/* set when register is not empty */
		continue;
	return RCREG;	
}

unsigned char getche(void)
{
	unsigned char c;
	putch(c = getch());
	return c;
}
