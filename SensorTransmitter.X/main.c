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
#include "hardwareDefinitions.h"
#include "transmitter.h"
#include "adc.h"

#define SAMPLE_SIZE 5
#define RETRANSMIT 10
#define PACKET_ADDRESS 2

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = SWDTEN    // Watchdog Timer Enable (WDT controlled by the SWDTEN bit in the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled. SBOREN bit is ignored.)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), 1.9V trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

void init16lf599();
float readTemperatureSensor();
void sleepTime(uint8_t timeInMinutes);
uint16_t performMeasurement();

int main() {
    init16lf599();
    initTransmitter();
    adcInit(TEMPERATURE_PROBE);
    while(1){
        //Measurement portion
        uint16_t valueToTransmit = performMeasurement();
        //Communications portion
        transmitOn();
        TRANSMITTER_SWITCH = ON;
        for(int i = 0; i < RETRANSMIT; i ++){
            sendPacket(PACKET_ADDRESS, valueToTransmit);   
        }
        TRANSMITTER_SWITCH = OFF;
        transmitOff();
        
        sleepTime(1);
        
    }
    return (EXIT_SUCCESS);
}

void init16lf599(){
    OSCCON = 0b01011010;
    OSCCONbits.IRCF = 0b1101; //4Mhz
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    WDTCONbits.WDTPS = 0b01010; //1s delay
    
    TRISBbits.TRISB6 = 0;
    TRISAbits.TRISA2 = 0;
}

uint16_t performMeasurement(){
    ADCON0bits.AD1ON = ON; //adc on
    TEMPERATURE_POWER = ON; 
    float temperature = 0;
    float temperatureToTransmit = 0;
    __delay_ms(20);
    for(int i = 0; i < SAMPLE_SIZE; i++){
        temperature = readTemperatureSensor() +temperature;
    }
    TEMPERATURE_POWER = OFF;
    ADCON0bits.AD1ON = OFF; //adc off
    //getting average and then multiply by 10 to preserve miliunits, which is then back converted on receiver
    temperatureToTransmit = (temperature/SAMPLE_SIZE)*10;
    
    return (uint16_t)temperatureToTransmit;
}

float readTemperatureSensor(){
    uint16_t value = adcRead();//assumes adc 3V/10bit
    float voltage = value * 2.9296875; //outputs mV
    float temperature = 0;
    temperature = (.1*voltage - 50); //outputs degrees celcius
    return temperature;
}

void sleepTime(uint8_t timeInMinutes){
    
    uint16_t timeInSeconds = timeInMinutes * 60;
    uint16_t numberOfSleeps = timeInSeconds;
    
    SWDTEN = 1; //Enable watchdog timer to sleep for about 1sec
    for(uint16_t i = 0; i < numberOfSleeps + PACKET_ADDRESS; i++){
        SLEEP();
    }
    SWDTEN = 0;  //Disable watchdog timer
}