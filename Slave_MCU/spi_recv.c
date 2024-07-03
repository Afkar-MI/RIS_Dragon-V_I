/*
 * spi_recv.c
 *
 *  Created on: Apr 17, 2023
 *      Author: afkar.mi
 */

#include "spi_recv.h"

uint8_t spi_recv_buf[11] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

uint8_t flag_spi_recv = 0;

void spi_init(void)
{

    P3SEL |= BIT0;      // SOMI
    P3SEL |= BIT1;      // SIM0
    P3SEL |= BIT2;      // CLK

    //P3DIR &= ~(BIT7) ; // Slave Select

    UCB0CTL1 |= UCSWRST;                      // **Put state machine in reset**
    UCB0CTL0 |= UCSYNC+UCCKPL+UCMSB;    // 3-pin, 8-bit SPI master
                                                 // Clock polarity high, MSB
    UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    UCB0IE |= UCRXIE;                         // Enable USCI_B0 RX interrupt

}


uint8_t spi_recv_one_byte(uint16_t *fp)   // Receive one byte data
{
    uint32_t t;
    uint8_t dat;
    for (t = 0; t < UART_RECV_TIMOUT_VALUE; t++) {
        if (SPI_RECV_FLAG) {
            dat = SPI_RECV_BUF;
            *fp = 1;
            break;
        }
    }
    if (t >= UART_RECV_TIMOUT_VALUE) {
        dat = 0xFF;
        *fp = 0;
    }
    return dat;
}



uint8_t spi_recv_n_byte(uint8_t* buff, uint16_t len )  // Receive all data and
{                                                      // and store them in a buffer
    uint16_t i = 0;
    uint16_t flag = 1;
    for (i= 0 ; (i < len) & (flag == 1); i++){
        buff[i] = spi_recv_one_byte(&flag);
    }
    if ((i == len) & (flag == 1)) {
        return 1;   // success
    } else {
        return 0;   // fail
    }
}


void set_pins(void){

    P1OUT &= ~(spi_recv_buf[2]) ;
    P2OUT &= ~(spi_recv_buf[3]) ;         // MOSFET will trigger for negative values
    P3OUT &= ~(spi_recv_buf[4]) ;
    P4OUT &= ~(spi_recv_buf[5]) ;
    P5OUT &= ~(spi_recv_buf[6]) ;
    P6OUT &= ~(spi_recv_buf[7]) ;
    P7OUT &= ~(spi_recv_buf[8]) ;
    P8OUT &= ~(spi_recv_buf[9]) ;
    //PUOUT0 &= ~(spi_recv_buf[10]) ;

}


#pragma vector=USCI_B1_VECTOR
__interrupt void USCI_B1_ISR(void)
{
    // FY - need to close all interrupt
    _DINT();

   spi_recv_n_byte(spi_recv_buf, SPI_LENGTH); //Receive All data from

   if ((spi_recv_buf[0] == SPI_HEADER) && (spi_recv_buf[1] == SPI_DATA_LENGTH)) // check for validity
   {
       flag_spi_recv = 1;
    }

   _EINT();
}
