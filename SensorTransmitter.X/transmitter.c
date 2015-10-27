
#include "transmitter.h"
void initTransmitter(){
    initComms();
}

void sendPacket(uint8_t address, uint8_t data){
    uint8_t checkSum = address + data;
    putch(SYNC);
    putch(address);
    putch(data);
    putch(checkSum);
}
