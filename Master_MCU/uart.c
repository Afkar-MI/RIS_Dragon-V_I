/*
 * uart.c
 *
 *  Created on: Mar 17, 2023
 *      Author: afkar.mi
 */

// --------10/04/2023-------------//




#include "uart.h"



void uart_init(void)
{
    //port mappingsS
      P4SEL |= BIT4+BIT5;                       // P4.4,5 = USCI_A1 TXD/RXD
      UCA1CTL1 |= UCSWRST;                      // **Put state machine in reset**
      UCA1CTL1 |= UCSSEL_2;                     // SMCLK
      UCA1BR0 = 0x04;                           // 8MHz/115200=4.41 (see User's Guide)
      UCA1BR1 = 0x00;
      UCA1MCTL |= UCOS16 + UCBRS_5 + UCBRF_3;
      UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
      UCA1IE |= UCRXIE;                         // Enable USCI_A1 RX interrupt

}


//-------------------------------UART RX /TX ------------------------------------------------------------//


uint8_t uart_recv_one_byte(uint16_t *fp)   // Receive one byte data
{
    uint32_t t;
    uint8_t dat;
    for (t = 0; t < UART_RECV_TIMOUT_VALUE; t++) {
        if (UART_RECV_FLAG) {
            dat = UCA1RXBUF;
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



uint8_t uart_recv_data(uint16_t len, uint8_t* buff)  // Receive all data and
{                                                      // and store them in a buffer
    uint16_t i = 0;
    uint16_t flag = 1;
    for (i= 0 ; (i < len) & (flag == 1); i++){
        buff[i] = uart_recv_one_byte(&flag);
    }
    if ((i == len) & (flag == 1)) {
        return 1;   // success
    } else {
        return 0;   // fail
    }
}



// Pins Map For All MCU

void pinsmap_trans(void)
{

    // FY Please do like this, This may not seem smart, but it's easy to check for errors
    //MCU_A Master MCU
    MCU_00[8] = 0x00;                                                                                                     //portU
    MCU_00[7] = uart_recv_buf[2] >> 5;                                                                                      //port8
    MCU_00[6] = ((uart_recv_buf[2] >> 1) & 0x0f) | ((uart_recv_buf[3] << 7) & 0x80) | ((uart_recv_buf[4] >> 1) & 0x70);     //port7
    MCU_00[5] = ((uart_recv_buf[2] << 7) & 0x80) | ((uart_recv_buf[3] >> 1) & 0x7f) ;                                       //port6
    MCU_00[4] = ((uart_recv_buf[4] << 3) & 0x80);                                                                           //port5
    MCU_00[3] = 0x00;                                                                                               //port4
    MCU_00[2] = 0x00;                                                                                                    //port3
    MCU_00[1] = 0x00;                                                                                                     //port2
    MCU_00[0] = 0x00;                                                                                                   //port1

    // SLAVE MCU 01
    MCU_01[8] = ((uart_recv_buf[6] >> 4) & 0x01);                                                                           //portU
    MCU_01[7] = ((uart_recv_buf[4] >> 1) & 0x07);                                                                           //port8
    MCU_01[6] = ((uart_recv_buf[4] << 3) & 0x08) | ((uart_recv_buf[5] >> 5) & 0x07) | ((uart_recv_buf[6] << 4) & 0xf0);     //port7
    MCU_01[5] = ((uart_recv_buf[5] << 3) & 0xf8) | ((uart_recv_buf[6] >> 5) & 0x07) ;                                       //port6
    MCU_01[4] = ((uart_recv_buf[7]) & 0xc0) ;                                                                               //port5
    MCU_01[3] = ((uart_recv_buf[7] << 2) & 0xfc) | ((uart_recv_buf[8] >> 6) & 0x03) ;                                       //port4
    MCU_01[2] = ((uart_recv_buf[8] << 2) & 0xf8) ;                                                                          //port3
    MCU_01[1] = ((uart_recv_buf[8] << 6) & 0x40) | ((uart_recv_buf[9] >> 2) & 0x3f) ;                                       //port2
    MCU_01[0] = ((uart_recv_buf[9] << 6) & 0xc0) | ((uart_recv_buf[10] >> 2) & 0x3f);                                       //port1

    // SLAVE MCU 02
    MCU_02[8] = ((uart_recv_buf[12] >> 2) & 0x01);                                                                          //portU
    MCU_02[7] = ((uart_recv_buf[10] << 1) & 0x06) | ((uart_recv_buf[11] >> 7) & 0x01);                                      //port8
    MCU_02[6] = ((uart_recv_buf[11] >> 3) & 0x0f) | ((uart_recv_buf[12] << 6) & 0xc0) | ((uart_recv_buf[13] >> 2) & 0x30);  //port7
    MCU_02[5] = ((uart_recv_buf[11] << 5) & 0xe0) | ((uart_recv_buf[12] >> 3) & 0x1f);                                      //port6
    MCU_02[4] = ((uart_recv_buf[13] << 2) & 0xc0) ;                                                                         //port5
    MCU_02[3] = ((uart_recv_buf[13] << 4) & 0xf0) | ((uart_recv_buf[14] >> 4) & 0x0f) ;                                     //port4
    MCU_02[2] = ((uart_recv_buf[14] << 4) & 0xf0) | ((uart_recv_buf[15] >> 4) & 0x08)  ;                                    //port3
    MCU_02[1] = ((uart_recv_buf[15]) & 0x7f) ;                                                                              //port2
    MCU_02[0] = (uart_recv_buf[16]);                                                                                        //port1


    // SLAVE MCU 03
    MCU_03[8] = ((uart_recv_buf[18]) & 0x01);                                                                               //portU
    MCU_03[7] = ((uart_recv_buf[17] >> 5));                                                                                 //port8
    MCU_03[6] = ((uart_recv_buf[17] >> 1) & 0x0f) | ((uart_recv_buf[19]) & 0xf0);                                           //port7
    MCU_03[5] = (uart_recv_buf[18] >> 1)  | (uart_recv_buf[17] << 7);                                                       //port6
    MCU_03[4] = ((uart_recv_buf[19] << 4) & 0xc0) ;                                                                         //port5
    MCU_03[3] = ((uart_recv_buf[19] << 6) & 0xc0) | (uart_recv_buf[20] >> 2)  ;                                             //port4
    MCU_03[2] = ((uart_recv_buf[20] << 6) & 0xc0) | ((uart_recv_buf[21] >> 2) & 0x38)  ;                                    //port3
    MCU_03[1] = ((uart_recv_buf[21] << 2) & 0x7c) | (uart_recv_buf[22] >> 6) ;                                              //port2
    MCU_03[0] = (uart_recv_buf[22] << 2) | (uart_recv_buf[23] >> 6);                                                        //port1

    // SLAVE MCU 04
    MCU_04[8] = ((uart_recv_buf[25] >> 6) & 0x01);                                                                          //portU
    MCU_04[7] = ((uart_recv_buf[23] >> 3) & 0x07);                                                                          //port8
    MCU_04[6] = ((uart_recv_buf[23] << 1) & 0x0e) | ((uart_recv_buf[24] >> 7) & 0x01) | ((uart_recv_buf[25] << 2) & 0xf0);  //port7
    //18/5/2023 correction
    MCU_04[5] = (uart_recv_buf[24] << 1)  | (uart_recv_buf[25] >> 7);                                                       //port6
    //
    MCU_04[4] = (uart_recv_buf[25] << 6) ;                                                                                  //port5
    MCU_04[3] = uart_recv_buf[26]  ;                                                                                        //port4
    MCU_04[2] = ((uart_recv_buf[27]) & 0xf8) ;                                                                              //port3
    MCU_04[1] = ((uart_recv_buf[27] << 4) & 0x70) | (uart_recv_buf[28] >> 4) ;                                              //port2
    MCU_04[0] = (uart_recv_buf[28] << 4) | (uart_recv_buf[29] >> 4);                                                        //port1

    // SLAVE MCU 05
    MCU_05[8] = ((uart_recv_buf[31] >> 4) & 0x01);                                                                           //portU
    MCU_05[7] = ((uart_recv_buf[29] >> 1) & 0x07);                                                                           //port8
    MCU_05[6] = ((uart_recv_buf[29] << 3) & 0x08) | ((uart_recv_buf[30] >> 5) & 0x07) | ((uart_recv_buf[31] << 4) & 0xf0);   //port7
    MCU_05[5] = (uart_recv_buf[30] << 3)  | (uart_recv_buf[31] >> 5)  ;                                                      //port6
    MCU_05[4] = ((uart_recv_buf[32]) & 0xc0) ;                                                                               //port5
    MCU_05[3] = ((uart_recv_buf[32] << 2) & 0xfc) | (uart_recv_buf[32] >> 6)  ;                                              //port4
    MCU_05[2] = ((uart_recv_buf[33] << 2) & 0xf8) ;                                                                          //port3
    MCU_05[1] = ((uart_recv_buf[33] << 6) & 0x40) | (uart_recv_buf[34] >> 2)  ;                                              //port2
    MCU_05[0] = (uart_recv_buf[34] << 6)  |  (uart_recv_buf[35] >> 2) ;                                                      //port1

    // SLAVE MCU 06
    MCU_06[8] = ((uart_recv_buf[37] >> 2) & 0x01);                                                                          //portU
    MCU_06[7] = ((uart_recv_buf[35] << 1) & 0x06) | ((uart_recv_buf[36] >> 7) & 0x01);                                      //port8
    MCU_06[6] = ((uart_recv_buf[36] >> 3) & 0x0f) | ((uart_recv_buf[37] << 6) & 0xc0) | ((uart_recv_buf[38] >> 2) & 0x30);  //port7
    MCU_06[5] = (uart_recv_buf[36] << 5) | (uart_recv_buf[37] >> 3);                                                        //port6
    MCU_06[4] = ((uart_recv_buf[38] << 2) & 0xc0) ;                                                                         //port5
    MCU_06[3] = (uart_recv_buf[38] << 4)  | (uart_recv_buf[39] >> 4) ;                                                      //port4
    MCU_06[2] = (uart_recv_buf[39] << 4) | ((uart_recv_buf[40] >> 4) & 0x08)  ;                                              //port3
    MCU_06[1] = ((uart_recv_buf[40]) & 0x7f) ;                                                                              //port2
    MCU_06[0] = (uart_recv_buf[41]);                                                                                        //port1


    // SLAVE MCU 07
   MCU_07[8] = ((uart_recv_buf[43]) & 0x01);                                                                               //portU
   MCU_07[7] = ((uart_recv_buf[42] >> 5));                                                                                 //port8
   MCU_07[6] = ((uart_recv_buf[42] >> 1) & 0x0f) | ((uart_recv_buf[44]) & 0xf0);                                           //port7
   MCU_07[5] = (uart_recv_buf[43] >> 1)  | (uart_recv_buf[42] << 7);                                                       //port6
   MCU_07[4] = ((uart_recv_buf[44] << 4) & 0xc0) ;                                                                         //port5
   MCU_07[3] = ((uart_recv_buf[44] << 6) & 0xc0) | ((uart_recv_buf[45] >> 2) & 0x3f) ;                                     //port4
   MCU_07[2] = ((uart_recv_buf[45] << 6) & 0xc0) | ((uart_recv_buf[46] >> 2) & 0x38)  ;                                    //port3
   MCU_07[1] = ((uart_recv_buf[46] << 2) & 0x7c) | (uart_recv_buf[47] >> 6) ;                                              //port2
   MCU_07[0] = (uart_recv_buf[47] << 2) | (uart_recv_buf[48] >> 6);                                                        //port1

   // SLAVE MCU 08
   MCU_08[8] = ((uart_recv_buf[50] >> 6) & 0x01);                                                                          //portU
   MCU_08[7] = ((uart_recv_buf[48] >> 3) & 0x07);                                                                          //port8
   MCU_08[6] = ((uart_recv_buf[48] << 1) & 0x0e) | ((uart_recv_buf[49] >> 7) & 0x01) | ((uart_recv_buf[50] << 2) & 0xf0);  //port7
   MCU_08[5] = (uart_recv_buf[49] << 1)  | (uart_recv_buf[50] >> 7);                                                       //port6
   MCU_08[4] = (uart_recv_buf[50] << 6) ;                                                                                  //port5
   MCU_08[3] = uart_recv_buf[51]  ;                                                                                        //port4
   MCU_08[2] = ((uart_recv_buf[52]) & 0xf8) ;                                                                              //port3
   MCU_08[1] = ((uart_recv_buf[52] << 4) & 0x70) | (uart_recv_buf[53] >> 4) ;                                              //port2
   MCU_08[0] = (uart_recv_buf[53] << 4) | (uart_recv_buf[54] >> 4);                                                        //port1

   // SLAVE MCU 09
   MCU_09[8] = ((uart_recv_buf[56] >> 4) & 0x01);                                                                           //portU
   MCU_09[7] = ((uart_recv_buf[54] >> 1) & 0x07);                                                                           //port8
   MCU_09[6] = ((uart_recv_buf[54] << 3) & 0x08) | ((uart_recv_buf[55] >> 5) & 0x07) | ((uart_recv_buf[56] << 4) & 0xf0);   //port7
   MCU_09[5] = (uart_recv_buf[55] << 3)  | (uart_recv_buf[56] >> 5)  ;                                                      //port6
   MCU_09[4] = ((uart_recv_buf[57]) & 0xc0) ;                                                                               //port5
   //5/18/2023 //correction
   MCU_09[3] = ((uart_recv_buf[57] << 2) & 0xfc) | (uart_recv_buf[58] >> 6)  ;                                              //port4
   //
   MCU_09[2] = ((uart_recv_buf[58] << 2) & 0xf8) ;                                                                          //port3
   MCU_09[1] = ((uart_recv_buf[58] << 6) & 0x40) | (uart_recv_buf[59] >> 2)  ;                                              //port2
   MCU_09[0] = (uart_recv_buf[59] << 6)  |  (uart_recv_buf[60] >> 2) ;                                                      //port1


   // SLAVE MCU 10
   MCU_10[8] = ((uart_recv_buf[62] >> 2) & 0x01);                                                                          //portU
   MCU_10[7] = ((uart_recv_buf[60] << 1) & 0x06) | ((uart_recv_buf[61] >> 7) & 0x01);                                      //port8
   MCU_10[6] = ((uart_recv_buf[61] >> 3) & 0x0f) | ((uart_recv_buf[62] << 6) & 0xc0) | ((uart_recv_buf[63] >> 2) & 0x30);  //port7
   MCU_10[5] = (uart_recv_buf[61] << 5) | (uart_recv_buf[62] >> 3);                                                        //port6
   MCU_10[4] = ((uart_recv_buf[63] << 2) & 0xc0) ;                                                                         //port5
   MCU_10[3] = (uart_recv_buf[63] << 4)  | (uart_recv_buf[64] >> 4) ;                                                      //port4
   MCU_10[2] = (uart_recv_buf[64] << 4) | ((uart_recv_buf[65] >> 4) & 0x08)  ;                                              //port3
   MCU_10[1] = ((uart_recv_buf[65]) & 0x7f) ;                                                                              //port2
   MCU_10[0] = (uart_recv_buf[66]);                                                                                        //port1

}


//-------------------------------Interrupt------------------------------------------------------//
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
    // FY - need to close all interrupt
    _DINT();

   uart_recv_data(UART_RECV_LENGTH, uart_recv_buf);

   if ((uart_recv_buf[0] == HEADER) && (uart_recv_buf[1] == DATA_LENGTH))
   {
    //uint16_t *fp= 0;
    //uint8_t dat = 0;
    //dat = uart_recv_one_byte(fp);

    flag_uart_recv = 1;

    }

   _EINT();
}

//-------------------------------Interrupt END------------------------------------------------------//
