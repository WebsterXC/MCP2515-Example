#include "include/mcp2515.h"
#include "include/spi.h"

#define MAX_WRITE_BYTES     16U

// CAN Timing Registers - 250kbps
#define REG_CNF1            0x00U
#define REG_CNF2            0xBFU
#define REG_CNF3            0x02U

// MCP2515 Device Initialization
void mcp2515_init(void){
    
    // Configure RXBxCTRL
    // - All Masks/Filters Off
    mcp2515_write(MCP2515_REG_RXB0CTRL, 0x60);
    mcp2515_write(MCP2515_REG_RXB1CTRL, 0x60);
    
    // Configure Bit Timing Registers
    mcp2515_write(MCP2515_REG_CNF1, REG_CNF1);
    mcp2515_write(MCP2515_REG_CNF2, REG_CNF2);
    mcp2515_write(MCP2515_REG_CNF3, REG_CNF3);
    
    // Go On Bus (Normal Mode)
    mcp2515_write(MCP2515_REG_CANCTRL, 0x00);
    
    return;
}

// Get the CANSTAT register.
uint8_t mcp2515_get_status(void){
    uint8_t status = 0;
    
    mcp2515_read(MCP2515_REG_CANSTAT, &status, 1);
    
    return status;
}

// Send a a CAN Tx request for a specific buffer (0, 1, 2).
void mcp2515_transmit_req(uint8_t bufferID){
    uint8_t dataOut[4];
    uint8_t buffer;
    
    // Calculate buffer register address.
    buffer = ((bufferID + 3) << 4) & 0xF0;
    
    dataOut[0] = MCP2515_INSTR_BIT_MODIFY;
    dataOut[1] = buffer;
    dataOut[2] = 0x08;      // Mask
    dataOut[3] = 0x08;      // Data
    
    spi_tx((const uint8_t *)dataOut, 4);
    
    return;
}

// Write a single register.
void mcp2515_write(uint8_t addr, uint8_t txData){
    uint8_t dataOut[3];
    
    dataOut[0] = MCP2515_INSTR_WRITE;
    dataOut[1] = addr;
    dataOut[2] = txData;
    
    spi_tx((const uint8_t *)dataOut, 3);
    
    return;
}

// Write sequential registers starting from a base address 'addr'.
void mcp2515_write_baseaddr(uint8_t addr, uint8_t *txData, uint8_t txBytes){
    uint8_t dataOut[MAX_WRITE_BYTES + 2];
    uint8_t bytes;
    uint8_t i;
    
    dataOut[0] = MCP2515_INSTR_WRITE;
    dataOut[1] = addr;
    
    if(txBytes > MAX_WRITE_BYTES){
        bytes = MAX_WRITE_BYTES;
    }else{
        bytes = txBytes;
    }
    
    for(i = 0; i < bytes; i++){
        dataOut[i+2] = txData[i];
    }
    
    spi_tx((const uint8_t *)dataOut, (bytes + 2));
    
    return;
}

// Read a single register.
void mcp2515_read(uint8_t addr, uint8_t *rxData, uint8_t rxBytes){
    uint8_t dataOut[2];
    
    dataOut[0] = MCP2515_INSTR_READ;
    dataOut[1] = addr;
    
    spi_txrx((const uint8_t *)dataOut, 2, rxData, rxBytes);
    
    return;
}
