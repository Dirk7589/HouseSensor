/* 
 * File:   main.c
 * Author: Dirk
 *
 * Created on August 8, 2015, 2:01 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xc.h>
#include <pic16f88.h>
#include "hardwareDefinitions.h"
#include "transmitter.h"
#include "adc.h"

#pragma config BOREN = OFF, CPD = OFF, CCPMX = RB3, DEBUG = OFF, WRT = OFF, FOSC = INTOSCIO, MCLRE = OFF, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = OFF

#define SAMPLE_SIZE 10
#define PACKET_ADDRESS 1
void init16f88();
uint8_t readTemperatureSensor();

int main() {
    init16f88();
    initTransmitter();
    adcInit(2);
    while(1){
        TRANSMIT_LED = 1;
        
        float temperature = 0;
        for(int i = 0; i < SAMPLE_SIZE; i++){
            temperature = readTemperatureSensor() +temperature;
        }
        temperature = temperature/SAMPLE_SIZE;
   
        sendPacket(PACKET_ADDRESS, temperature);
        
        SWDTEN = 1; //Enable watchdog timer
        TRANSMIT_LED = 0; 
        SLEEP(); //Sleep
        SWDTEN = 0; //Disable watchdog timer
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
    
    //Setup watchdog prescaler
    WDTPS3 = 0;
    WDTPS2 = 1;
    WDTPS1 = 1;
    WDTPS0 = 0;
    
    POWER_LED = 1; //Turn on power led
}

uint8_t readTemperatureSensor(){
    uint16_t value = adcRead();
    float voltage = (value * 5000)/1024; //outputs mV/10
    float temperature = (voltage - 500)/10; //outputs degrees celcius
    return (uint8_t)temperature;
}
