/* 
 * File:   transmitter.h
 * Author: Dirk
 *
 * Created on August 8, 2015, 3:04 PM
 */

#ifndef TRANSMITTER_H
#define	TRANSMITTER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>
#include "usart.h"
    
#define SYNC 0x28
    
/*Address mapping
 * 0 to 50 reserved for temperature
 * 50 to 100 reserved for rangers
 */
    
void initTransmitter();
void sendPacket(uint8_t address, uint16_t data);
#ifdef	__cplusplus
}
#endif

#endif	/* TRANSMITTER_H */

