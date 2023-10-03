/*
 * spi.h
 *
 *  Created on: Aug 27, 2023
 *      Author: gns2.lee
 */

#ifndef COMMON_INC_HW_SPI_H_
#define COMMON_INC_HW_SPI_H_



#ifdef __cplusplus
extern "C" {
#endif

#include "hw_def.h"

#ifdef _USE_HW_SPI

#define SPI_MAX_CH          HW_SPI_MAX_CH


#define SPI_CLOCK_DIV_1     0
#define SPI_CLOCK_DIV_2     1
#define SPI_CLOCK_DIV_4     2
#define SPI_CLOCK_DIV_8     3
#define SPI_CLOCK_DIV_16    4
#define SPI_CLOCK_DIV_32    5
#define SPI_CLOCK_DIV_64    6
#define SPI_CLOCK_DIV_128   7
#define SPI_CLOCK_DIV_256   8

#define SPI_MODE0           0
#define SPI_MODE1           1
#define SPI_MODE2           2
#define SPI_MODE3           3


bool spiInit(void);
bool spiReset(uint8_t ch);
bool spiBegin(uint8_t ch);
bool spiIsBegin(uint8_t ch);
void spiSetBitOrder(uint8_t ch, uint8_t bitOrder);
void spiSetClockDivider(uint8_t ch, uint32_t clockDiv);
void spiSetDataMode(uint8_t ch, uint8_t dataMode);
void spiSetBitWidth(uint8_t ch, uint8_t bit_width);

bool     spiTransfer(uint8_t ch, uint8_t *tx_buf, uint8_t *rx_buf, uint32_t length, uint32_t timeout);
uint8_t  spiTransfer8(uint8_t ch, uint8_t data);
uint16_t spiTransfer16(uint8_t ch, uint16_t data);

void spiDmaTxStart(uint8_t ch, uint8_t *p_buf, uint32_t length);
bool spiDmaTxTransfer(uint8_t ch, void *buf, uint32_t length, uint32_t timeout);
bool spiDmaTxIsDone(uint8_t ch);
void spiAttachTxInterrupt(uint8_t ch, void (*func)());


#endif

#ifdef __cplusplus
}
#endif


#endif /* COMMON_INC_HW_SPI_H_ */
