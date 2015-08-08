
#include "transmitter.h"
void initTransmitter(){
    initComms();
}

void sendPacket(uint8_t address, uint8_t data){
    putch(SYNC);
    putch(address);
    putch(data);
    putch(address+data);
}
