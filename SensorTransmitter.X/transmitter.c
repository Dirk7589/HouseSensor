
#include "transmitter.h"
void initTransmitter(){
    initComms();
}

void sendPacket(uint8_t address, uint16_t data){
    uint8_t dataLow = data & 0xFF;
    uint8_t dataHigh = data>>8;
    uint16_t checkSum = address + data;
    uint8_t checkSumLow = checkSum & 0xFF;
    uint8_t checkSumHigh = checkSum >> 8;
    
    putch(SYNC);
    putch(address);
    
    putch(dataLow);
    putch(dataHigh);
    
    putch(checkSumLow);
    putch(checkSumHigh);
}
