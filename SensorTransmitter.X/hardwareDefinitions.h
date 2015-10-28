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

#define POWER_LED PORTAbits.RA0
#define TRANSMIT_LED PORTAbits.RA1
#define TEMPERATURE_PROBE 0 //Selects Analog channel 0
    
#ifdef	__cplusplus
}
#endif

#endif	/* HARDWAREDEFINITIONS_H */

