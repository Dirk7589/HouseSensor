/* 
 * File:   reciever.h
 * Author: Dirk
 *
 * Created on August 8, 2015, 3:26 PM
 */

#ifndef RECIEVER_H
#define	RECIEVER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>
#include "usart.h"
    
#define SYNC 0x28

void initReceiver();
uint8_t receiverPacket(uint8_t address);

#ifdef	__cplusplus
}
#endif

#endif	/* RECIEVER_H */

