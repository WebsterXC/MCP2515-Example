#include <xc.h>
#include <stdio.h>
#include "include/spi.h"

#define ENH_BUFFER_BYTES    16U
#define RX_TX_MAX_BYTES     8U

void spi_init(void){
    
    SPI1CONCLR = 0xFFFFFFFF;
    SPI1BUF = 0x00000000;
    
    // Initialize SPI1 with:
    // - Mode: Master, 8-Bit
    // - Frequency: 625.0 kHz
    // - Options: Sample Falling Edge
    SPI1BRG = 31;
    SPI1STATbits.SPIROV = 0;
    SPI1CONbits.MSSEN = 1;
    SPI1CONbits.MSTEN = 1;
    SPI1CONbits.ENHBUF = 0;
    SPI1CONbits.MODE16 = 0;
    SPI1CONbits.MODE32 = 0;
    SPI1CONbits.CKE = 1;
    SPI1CONbits.ON = 1;
    
    return;
}

// Send a number of bytes with no response.
void spi_tx(const uint8_t *txData, uint8_t txSize){
    uint8_t dummyByte;
    uint8_t txBytes;
    uint8_t i;
    
    // Check and wait for SPI idle.
    while(SPI1STATbits.SPIBUSY == 1);
    
    txBytes = txSize;
    
    // Load Tx buffer with data.
    for(i = 0; i < txBytes; i++){
        SPI1BUF = txData[i];
        while(SPI1STATbits.SPITBE == 0);
        dummyByte = SPI1BUF;
    }
    
    // Wait for transaction to complete, otherwise CS# will stay low.
    while(SPI1STATbits.SPIBUSY == 1);
    
    return;
}

// Send a txSize bytes of data and receive a rxSize bytes of data.
void spi_txrx(const uint8_t *txData, uint8_t txSize, uint8_t *rxData, uint8_t rxSize){
    uint8_t i;
    uint8_t txBytes;
    uint8_t rxBytes;
    uint8_t dummyByte;
    
    // Check and wait for SPI idle.
    while(SPI1STATbits.SPIBUSY == 1);
    
    dummyByte = SPI1BUF;    // Flush SPI1 buffer.
    txBytes = txSize;
    rxBytes = rxSize;
    
    // Load Tx buffer with data.
    for(i = 0; i < txBytes; i++){
        SPI1BUF = txData[i];
        while(SPI1STATbits.SPITBE == 0);
        dummyByte = SPI1BUF;
    }
    
    // Load Rx buffer by extending data.
    for(i = 0; i < rxBytes; i++){
        SPI1BUF = 0xFF;
        while(SPI1STATbits.SPITBE == 0);
        dummyByte = SPI1BUF;    // Not sure why this flush is needed but it is.
    }
    
    // Wait for Rx buffer to fill.
    while(SPI1STATbits.SPIRBF == 0);
    
    // Read from SPI1 Rx buffer.
    for(i = 0; i < rxBytes; i++){
        rxData[i] = SPI1BUF;
    }
    
    return;
}
