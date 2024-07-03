/*
 * spi_recv.h
 *
 *  Created on: Apr 17, 2023
 *      Author: afkar.mi
 */

#ifndef SPI_RECV_H_
#define SPI_RECV_H_

#include <msp430.h>
#include "driverlib.h"
#include <stdio.h>
#include <stdlib.h>

#define SPI_RECV_FLAG              (UCB0IFG & UCRXIFG)
#define SPI_RECV_BUF               UCB0RXBUF
//#define SPI_SEND_FLAG              (UCB0IFG & UCTXIFG)
//#define SPI_SEND_BUF               UCB0TXBUF

#define UART_RECV_TIMOUT_VALUE      0xFBBB

#define SPI_LENGTH                 0x0b   // SPI Whole Data
#define SPI_HEADER                 0x40
#define SPI_DATA_LENGTH            0x09   // (9 Bytes)


extern uint8_t spi_recv_buf[11];  // buffer to store data receive

extern uint8_t flag_spi_recv;

void spi_init(void);

void set_pins(void);


#endif /* SPI_RECV_H_ */
