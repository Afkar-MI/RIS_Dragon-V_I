/*
 * spi.c
 *
 *  Created on: Apr 3, 2023
 *      Author: afkar.mi
 *
//                   MSP430F5529
//                 -----------------
//             /|\|                 |
//              | |                 |
//              --|RST          P1.0|-> LED
//                |                 |
//                |             P3.0|-> Data Out (UCB0SIMO)
//                |                 |
//                |             P3.1|<- Data In (UCB0SOMI)
//                |                 |
//  Slave reset <-|P1.1         P3.2|-> Serial Clock Out (UCB0CLK)
//
 *
 *
 *
 */
#include "spi.h"


#define SPI_RECV_FLAG              (UCB0IFG & UCRXIFG)
#define SPI_RECV_BUF               UCB0RXBUF
#define SPI_SEND_FLAG              (UCB0IFG & UCTXIFG)
#define SPI_SEND_BUF               UCB0TXBUF


void spi_init(void)
{
    P3SEL |= BIT0;      // MOSI
    P3SEL |= BIT1;      // MISO
    P3SEL |= BIT2;      // CLK

    P1DIR |= 0xff;      // set all to output direction  CS10, CS9, CS8, CS7, CS6, CS5, CS4, CS3
    P2DIR |= BIT1 + BIT0; //Set to Output Direction CS1, CS2;

    UCB0CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCB0CTL0 |= UCMST+UCSYNC+UCCKPL+UCMSB;    // 3-pin, 8-bit SPI master
                                                  // Clock polarity high, MSB
    UCB0CTL1 |= UCSSEL_2;                     // SMCLK 8MHz
    UCB0BR0 = 0x08;                           // /8 = 1Mhz
    UCB0BR1 = 0;                              //
    //UCB0MCTL = 0x00;                             // No modulation
    UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

}

// FY - need to consider which CS

void spi_send_one_byte(uint8_t data)
{
    while (!(UCB0IFG&UCTXIFG));
    UCB0TXBUF = data;
    __delay_cycles(100);
}



void spi_send_n_byte(uint8_t *send_data, uint16_t length)
{
    uint16_t i = 0;
    for (i = 0; i < length; i++)
    {
        spi_send_one_byte(*(send_data+i));
    }
}

void spi_send_11_byte(void)
{
    uint16_t i = 0;
    for (i = 0; i < 11; i++)
    {
        spi_send_one_byte(MCU_send_11Bytes[i]);
    }
}

