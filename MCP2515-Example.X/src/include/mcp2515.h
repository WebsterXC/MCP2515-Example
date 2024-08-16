#ifndef MCP2515_H
#define	MCP2515_H

#include <stdint.h>

// MCP2515 Instructions
#define MCP2515_INSTR_RESET             0xC0U
#define MCP2515_INSTR_READ              0x03U
#define MCP2515_INSTR_READ_RXBUF        0x90U
#define MCP2515_INSTR_WRITE             0x02U
#define MCP2515_INSTR_LOAD_TXBUF        0x40U
#define MCP2515_INSTR_RTS               0x80U
#define MCP2515_INSTR_READ_STATUS       0xA0U
#define MCP2515_INSTR_RX_STATUS         0xB0U
#define MCP2515_INSTR_BIT_MODIFY        0x05U

// MCP2515 Registers
#define MCP2515_REG_CANSTAT             0x0EU
#define MCP2515_REG_CANCTRL             0x0FU
#define MCP2515_REG_CNF1                0x2AU
#define MCP2515_REG_CNF2                0x29U
#define MCP2515_REG_CNF3                0x28U
#define MCP2515_REG_TXB0CTRL            0x30U
#define MCP2515_REG_TXB1CTRL            0x40U
#define MCP2515_REG_TXB2CTRL            0x50U
#define MCP2515_REG_RXB0CTRL            0x60U
#define MCP2515_REG_RXB1CTRL            0x70U

// MCP2515 Register Base Addresses
#define MCP2515_REG_TXBUF0_BASE         0x31U
#define MCP2515_REG_TXBUF1_BASE         0x41U
#define MCP2515_REG_TXBUF2_BASE         0x51U

// Default Value for CANCTRL register at POR.
#define MCP2515_POR_CANCTRL             0x87U

void mcp2515_init(void);
uint8_t mcp2515_get_status(void);
void mcp2515_transmit_req(uint8_t bufferID);
void mcp2515_write(uint8_t addr, uint8_t txData);
void mcp2515_write_baseaddr(uint8_t addr, uint8_t *txData, uint8_t txBytes);
void mcp2515_read(uint8_t addr, uint8_t *rxData, uint8_t rxBytes);

#endif	/* MCP2515_H */

