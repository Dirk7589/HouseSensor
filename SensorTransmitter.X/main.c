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
float readTemperatureSensor();

int main() {
    init16f88();
    initTransmitter();
    adcInit(TEMPERATURE_PROBE);
    while(1){
        TEMPERATURE_POWER = 1;
        float temperature = 0;
        float temperatureToTransmit = 0;
        for(int i = 0; i < SAMPLE_SIZE; i++){
            temperature = readTemperatureSensor() +temperature;
        }
        TEMPERATURE_POWER = 0;
        //getting average and then multiply by 10 to preserve miliunits, which is then back converted on receiver
        temperatureToTransmit = (temperature/SAMPLE_SIZE)*10;
        
        TRANSMITTER_SWITCH = 1;
        for(int i = 0; i < 10; i ++){
            sendPacket(1, (uint16_t)temperatureToTransmit);   
        }
        TRANSMITTER_SWITCH = 0;
        
        SWDTEN = 1; //Enable watchdog timer to sleep for about 45sec
        SLEEP(); //Sleep
        SLEEP();
        SLEEP();
        SLEEP();
        SLEEP();
        SLEEP();
        SWDTEN = 0;  //Disable watchdog timer
    }
    return (EXIT_SUCCESS);
}

void init16f88(){
    OSCCON = 0b01101110; //1 MHz
    TRISA = 0;
    TRISB = 0;
    ANSEL = 0;
    PORTA = 0;
    PORTB = 0;
    
    //Setup watchdog pre-scaler
    WDTPS3 = 0;
    WDTPS2 = 1;
    WDTPS1 = 1;
    WDTPS0 = 0;
    TRISBbits.TRISB3 = 0;
}

float readTemperatureSensor(){
    uint16_t value = adcRead();
    float voltage = value * 0.0048828125; //outputs mV
    float temperature = 0;
    temperature = (107*voltage - 57); //outputs degrees celcius
    return temperature;
}
