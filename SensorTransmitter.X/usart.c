#include "usart.h"

void initComms(){
    RX_PIN = 1;
	TX_PIN = 1;
	SPBRG = DIVIDER;     	
	RCSTA = (NINE_BITS|0x90);	
	TXSTA = (SPEED|NINE_BITS|0x20);
}

void putch(unsigned char byte) 
{
	/* output one byte */
	while(!TRMT)	/* set when register is empty */
		continue;
	TXREG = byte;

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
