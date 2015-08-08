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
    
void initTransmitter();
void sendPacket(uint8_t address, uint8_t data);
#ifdef	__cplusplus
}
#endif

#endif	/* TRANSMITTER_H */

