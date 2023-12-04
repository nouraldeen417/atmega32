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
#ifndef XC_TIMER_CONFIG_H
#define	XC_TIMER_CONFIG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"TIMER_interface.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define TIMER0_MODE          TIMER_OVF_MODE
#define TIMER0_CLOCK         TIMER_PRESCALER_64

#if TIMER0_MODE == TIMER_OVERFLOW_MODE

    #define TIMER0_INTERRUPT     TIMER_INTERRUPT_EN
    #define TIMER0_PRELOAD_VAL   0

#elif TIMER0_MODE == TIMER_CTC_MODE

    #define TIMER0_CTC_VAL                    125
    #define TIMER0_INTERRUPT                  TIMER_INTERRUPT_EN
    #define TIMER0_CTC_MODE                   TIMER_OC_DISCONNECTED

#elif TIMER0_MODE == TIMER_PWM_MODE
    #define TIMER0_INTERRUPT     TIMER_INTERRUPT_EN
    #define TIMER0_CTC_VAL              128
    #define TIMER0_CTC_PWM_MODE        TIMER_OC_DISCONNECTED

#elif TIMER0_MODE == TIMER_FASTPWM_MODE
    #define TIMER0_INTERRUPT            TIMER_INTERRUPT_EN
    #define TIMER0_CTC_VAL            125
    #define TIMER0_CTC_PWM_MODE       TIMER_OC_DISCONNECTED
#else
#error "Wrong TIMER0_INTERRUPT Config"
#endif
/*****************************************************************************************/

#define TIMER1_MODE                       TIMER1_OVERFLOW_MODE
#define TIMER1_CLOCK                      TIMER_PRESCALER_64
#define TIMER1_PRELOAD_VAL                 (0)
#define TIMER1_CTCA_VAL                    (270)
#define TIMER1_CTCB_VAL                    (270)

#define TIMER1_ICU_VAL                     (270)

#define TIMER1_CTCA_MODE                   TIMER_CLR_ON_CTC_SET_ON_TOP
#define TIMER1_CTCB_MODE                   TIMER_OC_TOGGEL

#define ICU_NOISE_CANCELER                  ICU_NOISE_CANCELER_DIS
#define TIMER_ICU_STATE                     TIMER_ICU_STATE_RAISING

#define TIMER1_CTCA_INTERRUPT               TIMER_INTERRUPT_DIS
#define TIMER1_CTCB_INTERRUPT               TIMER_INTERRUPT_DIS
#define TIMER1_OVF_INTERRUPT                TIMER_INTERRUPT_EN
#define TIMER1_ICU_INTERRUPT                TIMER_INTERRUPT_DIS
    
    

/*************************************************************************************************/
#define TIMER2_MODE          TIMER_PWM_MODE
#define TIMER2_CLOCK         TIMER2_PRESCALER_64

#if TIMER2_MODE == TIMER_OVERFLOW_MODE

    #define TIMER2_INTERRUPT     TIMER_INTERRUPT_EN
    #define TIMER2_PRELOAD_VAL   0

#elif TIMER2_MODE == TIMER_CTC_MODE

    #define TIMER2_CTC_VAL                    125
    #define TIMER2_INTERRUPT                  TIMER_INTERRUPT_EN
    #define TIMER2_CTC_MODE                   TIMER_OC_TOGGEL

#elif TIMER2_MODE == TIMER_PWM_MODE

    #define TIMER2_INTERRUPT                  TIMER_INTERRUPT_EN
    #define TIMER2_CTC_VAL                    127
    #define TIMER2_CTC_PWM_MODE               TIMER_CLR_ON_CTC_SET_ON_TOP

#elif TIMER2_MODE == TIMER_FAST_PWM_MODE
    #define TIMER2_INTERRUPT                  TIMER_INTERRUPT_EN
    #define TIMER2_CTC_VAL                    125
    #define TIMER2_CTC_PWM_MODE               TIMER_CLR_ON_CTC_SET_ON_TOP
#else
#error "Wrong TIMER2_INTERRUPT Config"
#endif


#define WDT_PRESCALER            WDT_PS_16_3_MS
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

