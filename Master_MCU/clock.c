/*
 * clock.c
 *
 *  Created on: Mar 17, 2023
 *      Author: afkar.mi
 */

#include "clock.h"


void BaseInit(void)
{
          WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer


          P5SEL |= BIT2+BIT3;                       // Port select XT2
          UCSCTL6 &= ~XT2OFF;                       // Enable XT2
          UCSCTL3 |= SELREF_2;                      // FLLref = REFO

          UCSCTL4 |= SELA_2;                        // ACLK=REFO,SMCLK=DCO,MCLK=DCO

          // Loop until XT1,XT2 & DCO stabilizes - in this case loop until XT2 settles
          do
          {
            UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                                    // Clear XT2,XT1,DCO fault flags
            SFRIFG1 &= ~OFIFG;                      // Clear fault flags
          }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

          UCSCTL6 &= ~XT2DRIVE0;                    // Decrease XT2 Drive according to
                                                    // expected frequency
          UCSCTL4 |= SELS_5 + SELM_5;               // SMCLK=MCLK=XT2





}

