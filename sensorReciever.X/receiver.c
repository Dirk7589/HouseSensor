
#include "receiver.h"


void initReceiver(){
    initComms();
}

void receiverAndForwardPacket(){
   uint8_t frame[3];
   
   /*Blocking call that does not return until it has data*/
   while(1){
        for(int i = 0; i < 3; i++){
            frame[i] = getch();
        }
        //checksum
        if((frame[2] == (frame[0]+frame[1]))){
            putch(SYNC);
            putch(frame[0]);
            putch(frame[1]);
            return;
        }
   }
}