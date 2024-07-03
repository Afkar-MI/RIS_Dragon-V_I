/*
 * pin_config.c
 *
 *  Created on: Apr 17, 2023
 *      Author: afkar.mi
 */

#include "pin_config.h"

void pins_config(void){

    P1DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7 ;    //PORT 1
    P2DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 ;           //PORT 2
    P3DIR |= BIT3 + BIT4 + BIT5 + BIT6 + BIT7 ;                         //PORT 3
    P4DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7 ;    //PORT 4
    P5DIR |= BIT6 + BIT7 ;                                              //PORT 5
    P6DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7 ;    //PORT 6
    P7DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7 ;    //PORT 7
    P8DIR |= BIT0 + BIT1 + BIT2;                                        //PORT 8
    //PUDIR |= BIT0 ;                                                     //PORT U

    // Set all values to one for the initial value
    // BCS MOSFET will trigger for negative values

    P1OUT |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7 ;
    P2OUT |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 ;           // BCS MOSFET will trigger for negative values
    P3OUT |= BIT3 + BIT4 + BIT5 + BIT6 + BIT7 ;
    P4OUT |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7 ;
    P5OUT |= BIT6 + BIT7 ;
    P6OUT |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7 ;
    P7OUT |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7 ;
    P8OUT |= BIT0 + BIT1 + BIT2;
    //PUOUT |= BIT0 ;

}
