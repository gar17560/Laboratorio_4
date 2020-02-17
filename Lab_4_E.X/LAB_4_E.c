/*
 * File:   LAB_4_E.c
 * Author: Miguel García
 * Carné: 17560
 * Electrónica digital 2
 * Sección: 21
 *
 * Created on 12 de febrero de 2020
 */

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


#include <xc.h>
#include <stdint.h>
#include "funciones.h"

#define _XTAL_FREQ 4000000

uint8_t dato1;
uint8_t dato2;
uint8_t recibir1;
uint8_t recibir2;

void config(void);

void main(void) {
    config();
    spiInit(SPI_SLAVE_SS_DIS, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    
    while(1){
        //PORTBbits.RB0 = 0;
        //PORTBbits.RB1 = 0;
        
        init_ADC(0x00);
        PIR1bits.ADIF = 0;
        dato1 = ADRESH;
        
        __delay_ms(5);

        init_ADC(0x01);
        PIR1bits.ADIF = 0;
        dato2 = ADRESH;        
        
        __delay_ms(5);
        
    }
    
    
    return;
}

void __interrupt() isr(void){
    if (PIR1bits.SSPIF == 1){ 
        recibir1 = spiRead();
        PORTB = recibir1;
        if (recibir1 == 0xFF){
            spiWrite(dato1);
            //PORTBbits.RB0 = 1;
        }
        else {
            spiWrite(dato2);
            //PORTBbits.RB1 = 1;
        }
        PIR1bits.SSPIF = 0;
        }
    return;
}


void config(void){
    PORTA = 0x00;
    TRISA = 0x03;       // Puerto A0 como entrada    
    ANSEL = 0x03;  // ANS0 y ANS1 como entrada analogica
  
    PORTB = 0;
    TRISB = 0;
    ANSELH = 0;
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.SSPIE = 1;
    PIR1bits.SSPIF = 0;
}