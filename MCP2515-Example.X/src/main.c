#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "include/spi.h"
#include "include/mcp2515.h"

#define IO_OUTPUT       0U
#define IO_INPUT        1U
#define IO_DIGITAL      0U
#define IO_ANALOG       1U

#define FREQ_SYSCLK     40000000U
#define FREQ_PBCLK      40000000U

static void uart_init(void);
static void delay(void);

static uint8_t canMessage[13];
static uint8_t deviceStatus;

int main(int argc, char** argv) {
    
    __builtin_disable_interrupts();
    
    // Initialize I/O & PPS
    TRISAbits.TRISA0 = IO_INPUT;    // U2RX Input
    ANSELAbits.ANSA0 = IO_DIGITAL;  // U2RX Digital
    U2RXR = 0x0;
    
    TRISAbits.TRISA3 = IO_OUTPUT;   // U2TX Output
    RPA3R = 0x2;
    
    TRISBbits.TRISB14 = IO_OUTPUT;  // SPI1 SCK
    ANSELBbits.ANSB14 = IO_DIGITAL;
    
    TRISBbits.TRISB7 = IO_OUTPUT;   // SPI1 SS
    RPB7R = 0x3;
    
    TRISBbits.TRISB11 = IO_OUTPUT;  // SPI1 SDO
    RPB11R = 0x3;
    
    TRISBbits.TRISB5 = IO_INPUT;    // SPI1 SDI
    SDI1R = 0x1;
    CNPUBbits.CNPUB5 = 1;

    // Initialize Peripherials
    uart_init();
    spi_init();
    
    delay();
    
    mcp2515_init();
    
    printf("\r\n\r\n**INIT**\r\n\r\n");
    while(1){
        // Monitor device status. 0x00 is good (normal mode, no interrupts).
        deviceStatus = mcp2515_get_status();
        printf("Device Status: %x\r\n", deviceStatus);
        
        // Send 0x18FABC33 with increasing data.
        canMessage[0] = 0xC7;  // SIDH
        canMessage[1] = 0xCA;  // SIDL
        canMessage[2] = 0xBC;  // EID8
        canMessage[3] = 0x33;  // EID0
        canMessage[4] = 8;  // DLC
        
        canMessage[5] = 0;  // D0-D8
        canMessage[6] = 1;
        canMessage[7] = 2;
        canMessage[8] = 3;
        canMessage[9] = 4;
        canMessage[10] = 5;
        canMessage[11] = 6;
        canMessage[12] = 7;
        
        mcp2515_write_baseaddr(MCP2515_REG_TXBUF0_BASE, canMessage, 13);
        mcp2515_transmit_req(0);
        
        delay();
        deviceStatus = 0xFF;
    }
    
    return (EXIT_SUCCESS);
}

static void uart_init(void){
    
    // Initalize the UART with:
    //   - Baud: 115200
    //   - Stop Bits: 1
    //   - Parity: None
    //   - Data: 8-bit
    U2MODEbits.RTSMD = 1;
    U2MODEbits.UEN = 0; 
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    
    U2STAbits.UTXISEL = 1;
    U2STAbits.URXISEL = 0;
    U2STAbits.URXEN = 1;
    U2STAbits.UTXEN = 1;
    
    // This value is dependent on PBCLK2 = 40MHz.
    // Target Baud: 115200 | Actual Baud: 108695
    U2BRG = 22;
    
    // Turn the UART on; future calls to printf() will go to UART2.
    U2MODEbits.ON = 1;
    
    return;
}

static void delay(void){
    uint32_t i;
    for(i = 0; i < 1500000; i++);
}
