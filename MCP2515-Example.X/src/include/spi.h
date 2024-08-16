#ifndef SPI_H
#define	SPI_H

#include <stdint.h>

#endif	/* SPI_H */

void spi_init(void);
void spi_tx(const uint8_t *txData, uint8_t txSize);
void spi_txrx(const uint8_t *txData, uint8_t txSize, uint8_t *rxData, uint8_t rxSize);
