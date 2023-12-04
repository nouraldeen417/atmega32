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
#ifndef XC_TIMER_INTERFACE_H
#define	XC_TIMER_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"../../lip/STD_TYPES.h"
#include"../../lip/Macros.h"
#include"TIMER_private.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Define indexes for the global pointer to func for ISR  */
#define TIMER0_OVF_VECTOR		0 //Vector 11
#define TIMER0_CTC_VECTOR		1 //Vector 10
#define TIMER1_OVF_VECTOR		2 //Vector 9
#define TIMER1_CTCB_VECTOR		3 //Vector 8
#define TIMER1_CTCA_VECTOR		4 //Vector 7
#define TIMER1_ICU_VECTOR		5 //Vector 6
#define TIMER2_OVF_VECTOR		6 //Vector 5
#define TIMER2_CTC_VECTOR		7 //Vector 4

/*********************************************TIMER0*****************************************************************/    

/*TIMER MODES*/
#define TIMER_OVERFLOW_MODE                               0
#define TIMER_PWM_MODE                                    1
#define TIMER_CTC_MODE                                    2
#define TIMER_FAST_PWM_MODE                               3


/* Compare Match Output Mode*/
#define TIMER_OC_DISCONNECTED					          0
#define TIMER_OC_TOGGEL							          1
#define TIMER_OC_LOW							          2
#define TIMER_OC_HIGH							          3

/* FASTPWM/PWM Mode*/
#define TIMER_OC_DISCONNECTED                             0
#define TIMER_CLR_ON_CTC_SET_ON_TOP                       2
#define TIMER_SET_ON_CTC_CLR_ON_TOP                       3
/*Clock Select Bit Description For Timer_0 /Timer_1*/
#define TIMER_NOCLOCK                                     0   
#define TIMER_NOPRESCALER                                 1
#define TIMER_PRESCALER_8                                 2
#define TIMER_PRESCALER_64                                3
#define TIMER_PRESCALER_256                               4
#define TIMER_PRESCALER_1024                              5
#define TIMER_EXTC_FALLING                                6
#define TIMER_EXTC_RISING                                 7
/*Timer2 Clock Source*/
#define TIMER2_PRESCALER_32                               3
#define TIMER2_PRESCALER_64                               4
#define TIMER2_PRESCALER_128                              5
#define TIMER2_PRESCALER_256                              6
#define TIMER2_PRESCALER_1024                             7
/*Timer_1 MODES*/
#define TIMER1_OVERFLOW_MODE                              0
#define TIMER1_PWM_8_BIT_MODE                             1
#define TIMER1_PWM_9_BIT_MODE                             2
#define TIMER1_PWM_10_BIT_MODE                            3
#define TIMER1_CTC_OCR1A_MODE                             4
#define TIMER1_FAST_PWM_8_BIT_MODE                        5
#define TIMER1_FAST_PWM_9_BIT_MODE                        6
#define TIMER1_FAST_PWM_10_BIT_MODE                       7
#define TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1_MODE           8
#define TIMER1_PWM_PHASE_FREQ_CORRECT_OCR1A_MODE          9
#define TIMER1_PWM_PHASE_CORRECT_ICR1_MODE                10
#define TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE               11
#define TIMER1_CTC_ICR1_MODE                              12
#define TIMER1_FAST_PWM_ICR1_MODE                         14
#define TIMER1_FAST_PWM_OCR1A_MODE                        15



/*TIMER INTERRUPT*/
#define TIMER_INTERRUPT_EN                                0
#define TIMER_INTERRUPT_DIS                               1

/*TIMER ICU STATE */
#define TIMER_ICU_STATE_RAISING                           0
#define TIMER_ICU_STATE_FALLING                           1
/*: Input Capture Noise Canceler*/
#define ICU_NOISE_CANCELER_DIS                            0
#define ICU_NOISE_CANCELER_EN                             1
/*WDT  */
#define WDT_PS_16_3_MS                                    0
#define WDT_PS_32_5_MS                                    1
#define WDT_PS_65_MS                                      2
#define WDT_PS_0_13_S                                     3
#define WDT_PS_0_26_S                                     4
#define WDT_PS_0_52_S                                     5
#define WDT_PS_1_0_S                                      6
#define WDT_PS_2_1_S                                      7
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
static void (*TIMER_pvoidCallBackFunc[16])(void)={NULL};
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

void TIMER0_voidInit                           (                 );
void TIMER0_voidDisable                        (                 );
void TIMER0_voidSetPreload                     (u8 Copy_u8Preload);
void TIMER0_voidSetCTC                         (u8 Copy_u8Preload);
ErrorStatus TIMER0_enumGetTimerCounterValue    (u8 *Copy_pu8Value);

void TIMER1_voidInit                           (                   );
void TIMER1_voidDisable                        (                   );
void TIMER1_voidEnable                         (                   );
void TIMER1_voidSetPreload                     (u16 Copy_u16Preload);
void TIMER1_voidSetCTCA                        (u16 Copy_u16Preload);
void TIMER1_voidSetCTCB                        (u16 Copy_u16Preload);
ErrorStatus TIMER1_enumGetTimerCounterValue    (u16 *Copy_pu16Value);


void TIMER2_voidInit                           (                 );
void TIMER2_voidDisable                        (                 );
void TIMER2_voidSetPreload                     (u8 Copy_u8Preload);
void TIMER2_voidSetCTC                         (u8 Copy_u8Preload);
ErrorStatus TIMER2_enumGetTimerCounterValue    (u8 *Copy_pu8Value);

void TIMER_voidICUInit                         (                 );
ErrorStatus TIMER_enumICUSetTrigger            (u8 Copy_u8Trigger);
void TIMER_voidICUEnableInterrupt              (                 );
void TIMER_voidICUDisableInterrupt             (                 );
ErrorStatus TIMER_enumICRValue                 (u16 *Copy_pu16Value);


/*WDT*/
void WDT_voidSleap                             (                   );
void WDT_voidEnable                            (                   );
void WDT_voidDisable                           (                   );

ErrorStatus TIMER_SetCallBack                  (u8 Copy_u8VectorID,void (*TIMER_CallPack)(void));




#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

