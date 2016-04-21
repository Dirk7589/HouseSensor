/* 
 * File:   usart.h
 * Author: Dirk
 *
 * Created on August 8, 2015, 2:08 PM
 */

#ifndef USART_H
#define	USART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "hardwareDefinitions.h"
    /*Defines*/
#define BAUD 300    
#define NINE 0     /* Use 9bit communication? FALSE=8bit */
#define HIGH_SPEED 0

/*Derived values*/
#if HIGH_SPEED == 1
#define DIVIDER_SCALE 16
#else
#define DIVIDER_SCALE 64    
#endif
    
#define DIVIDER (int)(_XTAL_FREQ/(DIVIDER_SCALE * BAUD) -1)

#if NINE == 1
#define NINE_BITS 0x40
#else
#define NINE_BITS 0
#endif

#if HIGH_SPEED == 1
#define SPEED 0x4
#else
#define SPEED 0
#endif

#if defined(_16F87) || defined(_16F88)
	#define RX_PIN TRISBbits.TRISB2
	#define TX_PIN TRISBbits.TRISB5
#else
	#define RX_PIN TRISB5
	#define TX_PIN TRISB7
#endif

/**
 * Initalizes the communications
 */
void initComms();
void transmitOff();
void transmitOn();
void putch(unsigned char);
unsigned char getch(void);
unsigned char getche(void);


#ifdef	__cplusplus
}
#endif

#endif	/* USART_H */

