/*
 * uart.h
 *
 *  Created on: Mar 17, 2023
 *      Author: afkar.mi
 */

#ifndef UART_H_
#define UART_H_

#include <msp430.h>
#include "driverlib.h"
#include <stdio.h>
#include <stdlib.h>

#define UART_RECV_TIMOUT_VALUE      0xFBBB

#define UART_RECV_FLAG              (UCA1IFG & UCRXIFG)
#define UART_RECV_BUF               UCA1RXBUF   // Receive buffer
#define UART_SEND_FLAG              (UCA1IFG & UCTXIFG)
#define UART_SEND_BUF               UCA1TXBUF   // Transmission buffer

#define HEADER                      0x20  // Frame Header UART Data
#define DATA_LENGTH                 0x41  // Data Length from PC (65 Bytes)               //FY - Please check length should be fixed 65, 0x41

#define UART_RECV_LENGTH            0x43  // Data Length (whole)                          //FY - Please check shuould be 67, 0x43


extern uint8_t uart_recv_buf[67];  // Buffer to store data received

// FY - MCU_n PINs
extern uint8_t MCU_00[9];
extern uint8_t MCU_01[9];
extern uint8_t MCU_02[9];
extern uint8_t MCU_03[9];
extern uint8_t MCU_04[9];
extern uint8_t MCU_05[9];
extern uint8_t MCU_06[9];
extern uint8_t MCU_07[9];
extern uint8_t MCU_08[9];
extern uint8_t MCU_09[9];
extern uint8_t MCU_10[9];

extern uint8_t MCU_send_11Bytes[11];

extern uint8_t flag_uart_recv;


void uart_init(void); //Uart config

void uart_send_data(uint8_t *data, uint8_t length);

void pinsmap_trans(void);


#endif /* UART_H_ */
