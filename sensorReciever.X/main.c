/* 
 * File:   main.c
 * Author: Dirk
 *
 * Created on August 8, 2015, 2:01 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f88.h>
#include "hardwareDefinitions.h"
#include "receiver.h"

#pragma config BOREN = OFF, CPD = OFF, CCPMX = RB3, DEBUG = OFF, WRT = OFF, FOSC = INTOSCIO, MCLRE = OFF, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = OFF

void init16f88();

/*
 * 
 */
int main() {
    init16f88();
    initReceiver();
    while(1){
        receiverAndForwardPacket();
    }
    return (EXIT_SUCCESS);
}

void init16f88(){
    OSCCON = 0b01101110;
    TRISA = 0;
    TRISB = 0;
    ANSEL = 0;
    PORTA = 0;
    PORTB = 0;
}