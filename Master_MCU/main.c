#include <msp430.h>
#include "driverlib.h"

#include "uart.h"
#include "clock.h"
#include "spi.h"

#define SPI_LENGTH                 0x0b   // SPI Whole Data
#define SPI_HEADER                 0x40
#define SPI_DATA_LENGTH            0x09   // (9 Bytes)

uint8_t Header_buff[2] = {SPI_HEADER , SPI_DATA_LENGTH} ;

uint8_t uart_recv_buf[67] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                             0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                             0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                             0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                             0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                             0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                             0xff,0xff,0xff,0xff,0xff,0xff,0xff};  // Buffer to store data received

// FY - MCU_n PINs
uint8_t MCU_00[9] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uint8_t MCU_01[9] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uint8_t MCU_02[9] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uint8_t MCU_03[9] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uint8_t MCU_04[9] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uint8_t MCU_05[9] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uint8_t MCU_06[9] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uint8_t MCU_07[9] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uint8_t MCU_08[9] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uint8_t MCU_09[9] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uint8_t MCU_10[9] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

uint8_t MCU_send_11Bytes[11] = {SPI_HEADER,SPI_DATA_LENGTH,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

uint8_t flag_uart_recv = 0;

void pins_config(void);


int main(void)
{
         BaseInit();
         uart_init();
         spi_init();

         //---pin set
         pins_config();


         __bis_SR_register(GIE);      // open interrupt

         while(1)
         {

             if( flag_uart_recv == 1 )
             {
                 // FY - if the flag is set do data conversion; and SPI send; after this clear flag. and set pins
                 pinsmap_trans();

                 uint16_t i;

                 for ( i = 1; i < 11; i++)
                 {
                     //CS the mcu, select
                     switch (i)
                     {
                          case 1: P2OUT &= ~BIT1 /*set MCU_01 CS to 0*/;
                                  MCU_send_11Bytes[2] = MCU_01[0];
                                  MCU_send_11Bytes[3] = MCU_01[1];
                                  MCU_send_11Bytes[4] = MCU_01[2];
                                  MCU_send_11Bytes[5] = MCU_01[3];
                                  MCU_send_11Bytes[6] = MCU_01[4];
                                  MCU_send_11Bytes[7] = MCU_01[5];
                                  MCU_send_11Bytes[8] = MCU_01[6];
                                  MCU_send_11Bytes[9] = MCU_01[7];
                                  MCU_send_11Bytes[10] = MCU_01[8];
                                  break;
                          case 2: P2OUT &= ~BIT0 /*set MCU_02 CS to 0*/;
                                  MCU_send_11Bytes[2] = MCU_02[0];
                                  MCU_send_11Bytes[3] = MCU_02[1];
                                  MCU_send_11Bytes[4] = MCU_02[2];
                                  MCU_send_11Bytes[5] = MCU_02[3];
                                  MCU_send_11Bytes[6] = MCU_02[4];
                                  MCU_send_11Bytes[7] = MCU_02[5];
                                  MCU_send_11Bytes[8] = MCU_02[6];
                                  MCU_send_11Bytes[9] = MCU_02[7];
                                  MCU_send_11Bytes[10] = MCU_02[8];
                                  break;
                          case 3: P1OUT &= ~BIT7 /*set MCU_03 CS to 0*/;
                                  MCU_send_11Bytes[2] = MCU_03[0];
                                  MCU_send_11Bytes[3] = MCU_03[1];
                                  MCU_send_11Bytes[4] = MCU_03[2];
                                  MCU_send_11Bytes[5] = MCU_03[3];
                                  MCU_send_11Bytes[6] = MCU_03[4];
                                  MCU_send_11Bytes[7] = MCU_03[5];
                                  MCU_send_11Bytes[8] = MCU_03[6];
                                  MCU_send_11Bytes[9] = MCU_03[7];
                                  MCU_send_11Bytes[10] = MCU_03[8];
                                  break;
                          case 4: P1OUT &= ~BIT6 /*set MCU_04 CS to 0*/;
                                  MCU_send_11Bytes[2] = MCU_04[0];
                                  MCU_send_11Bytes[3] = MCU_04[1];
                                  MCU_send_11Bytes[4] = MCU_04[2];
                                  MCU_send_11Bytes[5] = MCU_04[3];
                                  MCU_send_11Bytes[6] = MCU_04[4];
                                  MCU_send_11Bytes[7] = MCU_04[5];
                                  MCU_send_11Bytes[8] = MCU_04[6];
                                  MCU_send_11Bytes[9] = MCU_04[7];
                                  MCU_send_11Bytes[10] = MCU_04[8];
                                  break;
                          case 5: P1OUT &= ~BIT5 /*set MCU_05 CS to 0*/;
                                  MCU_send_11Bytes[2] = MCU_05[0];
                                  MCU_send_11Bytes[3] = MCU_05[1];
                                  MCU_send_11Bytes[4] = MCU_05[2];
                                  MCU_send_11Bytes[5] = MCU_05[3];
                                  MCU_send_11Bytes[6] = MCU_05[4];
                                  MCU_send_11Bytes[7] = MCU_05[5];
                                  MCU_send_11Bytes[8] = MCU_05[6];
                                  MCU_send_11Bytes[9] = MCU_05[7];
                                  MCU_send_11Bytes[10] = MCU_05[8];
                                  break;
                          case 6: P1OUT &= ~BIT4 /*set MCU_06 CS to 0*/;
                                  MCU_send_11Bytes[2] = MCU_06[0];
                                  MCU_send_11Bytes[3] = MCU_06[1];
                                  MCU_send_11Bytes[4] = MCU_06[2];
                                  MCU_send_11Bytes[5] = MCU_06[3];
                                  MCU_send_11Bytes[6] = MCU_06[4];
                                  MCU_send_11Bytes[7] = MCU_06[5];
                                  MCU_send_11Bytes[8] = MCU_06[6];
                                  MCU_send_11Bytes[9] = MCU_06[7];
                                  MCU_send_11Bytes[10] = MCU_06[8];
                                  break;
                          case 7: P1OUT &= ~BIT3 /*set MCU_07 CS to 0*/;
                                  MCU_send_11Bytes[2] = MCU_07[0];
                                  MCU_send_11Bytes[3] = MCU_07[1];
                                  MCU_send_11Bytes[4] = MCU_07[2];
                                  MCU_send_11Bytes[5] = MCU_07[3];
                                  MCU_send_11Bytes[6] = MCU_07[4];
                                  MCU_send_11Bytes[7] = MCU_07[5];
                                  MCU_send_11Bytes[8] = MCU_07[6];
                                  MCU_send_11Bytes[9] = MCU_07[7];
                                  MCU_send_11Bytes[10] = MCU_07[8];
                                  break;
                          case 8: P1OUT &= ~BIT2 /*set MCU_08 CS to 0*/;
                                  MCU_send_11Bytes[2] = MCU_08[0];
                                  MCU_send_11Bytes[3] = MCU_08[1];
                                  MCU_send_11Bytes[4] = MCU_08[2];
                                  MCU_send_11Bytes[5] = MCU_08[3];
                                  MCU_send_11Bytes[6] = MCU_08[4];
                                  MCU_send_11Bytes[7] = MCU_08[5];
                                  MCU_send_11Bytes[8] = MCU_08[6];
                                  MCU_send_11Bytes[9] = MCU_08[7];
                                  MCU_send_11Bytes[10] = MCU_08[8];
                                  break;
                          case 9: P1OUT &= ~BIT1 /*set MCU_09 CS to 0*/;
                                  MCU_send_11Bytes[2] = MCU_09[0];
                                  MCU_send_11Bytes[3] = MCU_09[1];
                                  MCU_send_11Bytes[4] = MCU_09[2];
                                  MCU_send_11Bytes[5] = MCU_09[3];
                                  MCU_send_11Bytes[6] = MCU_09[4];
                                  MCU_send_11Bytes[7] = MCU_09[5];
                                  MCU_send_11Bytes[8] = MCU_09[6];
                                  MCU_send_11Bytes[9] = MCU_09[7];
                                  MCU_send_11Bytes[10] = MCU_09[8];
                                  break;
                          case 10: P1OUT &= ~BIT0 /*set MCU_10 CS to 0*/;
                                  MCU_send_11Bytes[2] = MCU_10[0];
                                  MCU_send_11Bytes[3] = MCU_10[1];
                                  MCU_send_11Bytes[4] = MCU_10[2];
                                  MCU_send_11Bytes[5] = MCU_10[3];
                                  MCU_send_11Bytes[6] = MCU_10[4];
                                  MCU_send_11Bytes[7] = MCU_10[5];
                                  MCU_send_11Bytes[8] = MCU_10[6];
                                  MCU_send_11Bytes[9] = MCU_10[7];
                                  MCU_send_11Bytes[10] = MCU_10[8];
                                  break;
                          //Please add
                     }

                     __delay_cycles(500);

                     spi_send_11_byte();

                     __delay_cycles(500);


                     switch (i)
                     {
                          case 1:P2OUT |= BIT1 /* set MCU_01 CS to 1*/;break;
                          case 2:P2OUT |= BIT0 /*set MCU_02 CS to 1*/;break;
                          case 3:P1OUT |= BIT7 /* set MCU_03 CS to 1*/;break;
                          case 4:P1OUT |= BIT6 /* set MCU_04 CS to 1*/;break;
                          case 5:P1OUT |= BIT5 /* set MCU_05 CS to 1*/;break;
                          case 6:P1OUT |= BIT4 /* set MCU_06 CS to 1*/;break;
                          case 7:P1OUT |= BIT3 /* set MCU_07 CS to 1*/;break;
                          case 8:P1OUT |= BIT2 /* set MCU_08 CS to 1*/;break;
                          case 9:P1OUT |= BIT1 /* set MCU_09 CS to 1*/;break;
                          case 10:P1OUT |= BIT0 /* set MCU_10 CS to 1*/;break;

                     }

                     __delay_cycles(5000);
                 }


                 flag_uart_recv = 0;

                 P8OUT = MCU_00[7];
                 P7OUT = MCU_00[6];
                 P6OUT = MCU_00[5];
                 P5OUT = MCU_00[4];
             }

         }

}


void pins_config(void){

    P5DIR |= BIT7 ;                                                     //PORT 5
    P6DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7 ;    //PORT 6
    P7DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7 ;    //PORT 7
    P8DIR |= BIT0 + BIT1 + BIT2;                                        //PORT 8

    // Set all values to one for the initial value
    // BCS MOSFET will trigger for negative values

    P5OUT |= BIT7 ;
    P6OUT |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7 ;
    P7OUT |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7 ;
    P8OUT |= BIT0 + BIT1 + BIT2;

}




