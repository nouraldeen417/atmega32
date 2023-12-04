/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_TIMER_PRIVATE_H
#define	XC_TIMER_PRIVATE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"../../lip/Macros.h"
#include"../../lip/STD_TYPES.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*Timer 0 Registers*/
#define  TIMER0_TCCR_REG  *((volatile u8 *)0x53)
#define  TIMER0_TCNT_REG  *((volatile u8 *)0x52)
#define  TIMER0_OCR_REG  *((volatile u8 *)0x5C)
#define  SFIOR_REG        *((volatile u8 *)0x50)
#define  TIMSK_REG        *((volatile u8 *)0x59)
#define  TIFR_REG         *((volatile u8 *)0x58)
/*******************************************/
/*TCCR0_BETS   WGM00 COM01 COM00 WGM01 FOC0*/
#define TCCR0_FOC0_BIT        7
#define TCCR0_WGM00_BIT       6
#define TCCR0_COM01_BIT       5
#define TCCR0_COM00_BIT       4
#define TCCR0_WGM01_BIT       3
#define TCCR_PRE_MASK        0xF8
/*******************************************/
/* Timer0 Output Compare Match Interrupt Enable BIT*/
#define TIMSK_OCIE0_BIT       1
/* Timer0 Output  Overflow Interrupt Enable*/
#define TIMSK_TOIE0_BIT       0
/*******************************************/
/* Timer0 Output Compare Match Interrupt Enable BIT  */
#define TIFR_OCF0_BIT         1
/* Timer0 Output  Overflow Interrupt Enable */
#define TIFR_TOV0_BIT        0


/*Timer 2 Registers*/
#define  TIMER2_TCCR_REG  *((volatile u8 *)0x45)
#define  TIMER2_TCNT_REG  *((volatile u8 *)0x44)
#define  TIMER2_OCR_REG   *((volatile u8 *)0x43)
/*******************************************/
/*TCCR2_BETS   WGM00 COM01 COM00 WGM01 FOC0*/
#define TCCR2_FOC0_BIT        7
#define TCCR2_WGM00_BIT       6
#define TCCR2_COM01_BIT       5
#define TCCR2_COM00_BIT       4
#define TCCR2_WGM01_BIT       3
#define TCCR2_PRE_MASK        0xF8
/* Timer2 Output Compare Match Interrupt Enable BIT*/
#define TIMSK_OCIE2_BIT       7
/* Timer2 Output  Overflow Interrupt Enable*/
#define TIMSK_TOIE2_BIT       6
/*******************************************/
/* Timer2 Output Compare Match Interrupt Enable BIT  */
#define TIFR_OCF2_BIT         7
/* Timer2 Output  Overflow Interrupt Enable */
#define TIFR_TOV2_BIT        6



/*Timer 1 Registers*/
#define  TIMER1_TCCRA_REG  *((volatile u8  *)0x4F)
#define  TIMER1_TCCRB_REG  *((volatile u8  *)0x4E)

#define  TIMER1_TCNTH_REG  *((volatile u8  *)0x4D)
#define  TIMER1_TCNTL_REG  *((volatile u8  *)0x4C)
#define  TIMER1_TCNT1_REG  *((volatile u16 *)0X4C) 

#define  TIMER1_OCRAH_REG  *((volatile u8  *)0x4B)
#define  TIMER1_OCRAL_REG  *((volatile u8  *)0x4A)
#define  TIMER1_OCRA1_REG  *((volatile u16 *)0x4A)

#define  TIMER1_OCRBH_REG  *((volatile u8  *)0x49)
#define  TIMER1_OCRBL_REG  *((volatile u8  *)0x48)
#define  TIMER1_OCRB1_REG  *((volatile u16 *)0x48)

#define  TIMER1_ICRH_REG  *((volatile u8   *)0x47)
#define  TIMER1_ICRL_REG  *((volatile u8   *)0x46)
#define  TIMER1_ICR1_REG  *((volatile u16  *)0x46)


/*******************************************/
/*TCCRA_BETS   */
#define TCCR1A_COM1A1_BIT        7
#define TCCR1A_COM1A0_BIT        6
#define TCCR1A_COM1B1_BIT        5
#define TCCR1A_COM1B0_BIT        4
#define TCCR1A_FOC1A_BIT         3
#define TCCR1A_FOC1B_BIT         2
#define TCCR1A_WGM11_BIT         1
#define TCCR1A_WGM10_BIT         0
/*TCCRB_BETS   */
#define TCCR1B_ICNC1_BIT         7
#define TCCR1B_ICES1_BIT         6
#define TCCR1B_WGM13_BIT         4
#define TCCR1B_WGM12_BIT         3

/* Timer1 Output Compare Match Interrupt Enable BIT TICIE1 OCIE1A OCIE1B TOIE1*/
#define TIMSK_TICIE1_BIT       5
#define TIMSK_OCIE1A_BIT       4
#define TIMSK_OCIE1B_BIT       3
#define TIMSK_TOIE1_BIT        2
/*******************************************/
/* Timer2 Output Compare Match Interrupt Enable BIT  */
#define TIFR_ICF1_BIT           5
#define TIFR_OCF1A_BIT          4
#define TIFR_OCF1B_BIT          3
#define TIFR_TOV1_BIT           2

/*WDT  */
#define  WDTCR_REG  *((volatile u8   *)0x41)

#define WDTCR_WDTOE_BIT           4
#define WDTCR_WDE_BIT             3
#define WDTCR_PRE_MASK            0xF8
#define WDTCR_DISABLE_MASK        0x18          //             0 0 0 1 1 0 0 0

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

