/*
 * File:   funciones.c
 * Author: ICHELECE
 *
 * Created on 12 de febrero de 2020, 10:44
 */


#include <xc.h>
#include <stdint.h>
#include "funciones.h"
#define _XTAL_FREQ 4000000

void init_serial(void){
    // Configuración del serial
    
    TXSTAbits.SYNC = 0;   //asincrono
    TXSTAbits.BRGH = 1;  
    BAUDCTLbits.BRG16 = 1;  //8 BITS BAURD RATE GENERATOR
    SPBRG = 103;
    SPBRGH = 0;
    
    RCSTAbits.SPEN = 1;     //habilitamos recibir datos
    RCSTAbits.RX9 = 0;      //8 bits
    RCSTAbits.CREN = 1;     //habilitamos la recepción de datos
    
    TXSTAbits.TXEN = 1;     //habilitamos la transmisión de datos 
}

void spiInit(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge)
{
    TRISC5 = 0;
    if(sType & 0b00000100) //If Slave Mode
    {
        SSPSTAT = sTransmitEdge;
        TRISC3 = 1;
    }
    else              //If Master Mode
    {
        SSPSTAT = sDataSample | sTransmitEdge;
        TRISC3 = 0;
    }
    
    SSPCON = sType | sClockIdle;
}

static void spiReceiveWait()
{
    while ( !SSPSTATbits.BF ); // Wait for Data Receive complete
}

void spiWrite(char dat)  //Write data to SPI bus
{
    SSPBUF = dat;
}

unsigned spiDataReady() //Check whether the data is ready to read
{
    if(SSPSTATbits.BF)
        return 1;
    else
        return 0;
}

char spiRead() //REad the received data
{
    spiReceiveWait();        // wait until the all bits receive
    return(SSPBUF); // read the received data from the buffer
}