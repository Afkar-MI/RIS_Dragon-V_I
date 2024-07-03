/*
 * spi.h
 *
 *  Created on: Apr 3, 2023
 *      Author: afkar.mi
 */

#ifndef SPI_H_
#define SPI_H_

#include <msp430.h>
#include "driverlib.h"

extern uint8_t MCU_send_11Bytes[11];

void spi_init(void);
void spi_send_one_byte(uint8_t data);
void spi_send_n_byte(uint8_t *send_data, uint16_t length);

void spi_send_11_byte(void);

#endif /* SPI_H_ */
