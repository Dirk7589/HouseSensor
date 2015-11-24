/* 
 * File:   hardwareDefinitions.h
 * Author: Dirk
 *
 * Created on August 8, 2015, 2:01 PM
 */

#ifndef HARDWAREDEFINITIONS_H
#define	HARDWAREDEFINITIONS_H

#ifdef	__cplusplus
extern "C" {
#endif


#define _XTAL_FREQ 4000000

#define TEMPERATURE_PROBE 3 //Selects Analog channel for the temperature probe
#define TRANSMITTER_SWITCH PORTBbits.RB6
#define TEMPERATURE_POWER PORTAbits.RA2
#ifdef	__cplusplus
}
#endif

#endif	/* HARDWAREDEFINITIONS_H */

