/*
 * File:   LAB_4_M.c
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

uint8_t pot1;
uint8_t pot2;
uint8_t recibir1;

void config(void);

void main(void) {
    config();
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);  //MASTER  
    init_serial();
    while (1){
        
        spiWrite(0xFF);
        pot1 = spiRead();
        __delay_ms(10);
        
        spiWrite(0x0F);
        pot2 = spiRead();
        __delay_ms(10);
        
        TXREG = pot1;
        while(PIR1bits.TXIF == 0){
        }
        
        TXREG = pot2;
        while(PIR1bits.TXIF == 0){
        }
        

        if (PIR1bits.RCIF == 1){
            recibir1 = RCREG;
        }

        __delay_ms(100);
        PORTD = pot2;
        PORTB = recibir1;
    }
    
    return;
}

void config(void){
    PORTB = 0x00;
    TRISB = 0x00;       // Puerto B como salida   
    ANSELH = 0x00;  
    
    PORTD = 0x00;
    TRISD = 0x00;   
    
    PORTA = 0;
    TRISA = 0;
    ANSEL = 0;
}