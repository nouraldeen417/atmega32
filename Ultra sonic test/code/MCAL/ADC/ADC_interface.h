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
#ifndef XC_ADC_INTERFACE_H
#define	XC_ADC_INTERFACE_H

#include <xc.h> 
#include"../../lip/STD_TYPES.h"
#include"ADC_private.h"
#include"../../lip/Macros.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Reference Selection Bits*/
#define ADC_AREF                       0          //AREF, Internal Vref
#define ADC_AVCC                       1          //AVCC with external capacitor at AREF pin
#define ADC_INTERNAL_2_56              3          //Internal 2.56V Voltage Reference with external capacitor at AREF pin
/* ADC Left Adjust Result */
#define ADC_RIGHT_ADJUST               0
#define ADC_LEFT_ADJUST                1
/* Analog Channel and Gain Selection Bits*/
#define ADC_CHANEL0                    0
#define ADC_CHANEL1                    1
#define ADC_CHANEL2                    2
#define ADC_CHANEL3                    3
#define ADC_CHANEL4                    4
#define ADC_CHANEL5                    5
#define ADC_CHANEL6                    6
#define ADC_CHANEL7                    7
/* ADC Enable*/
#define ADC_DISABLE                   0
#define ADC_ENABLE                    1
/*ADC Start Conversion Mode*/
#define ADC_SINGLE_CONVERSION          0
#define ADC_FREE_RUNNING               1
/*Interrupt*/
#define ADC_INTERRUPT_DISABLE          0
#define ADC_INTERRUPT_ENABLE           1
/*ADC Prescaler Select Bits*/
#define ADC_PRE_2                      0
#define ADC_PRE_4                      2
#define ADC_PRE_8                      3
#define ADC_PRE_16                     4
#define ADC_PRE_32                     5
#define ADC_PRE_64                     6
#define ADC_PRE_128                    7
/* ADC Auto Trigger Source*/
#define ADC_ANALOG_COMPARATOR          0
#define ADC_EXTI0                      1
#define ADC_TIM0_CMC                   2
#define ADC_TIM0_OVF                   3
#define ADC_TIM1_CMC_CHANNELB          4
#define ADC_TIM1_OVF                   5
#define ADC_TIM1_ICU                   6

/*Channel State*/
#define ADC_SINGLE_CHANNEL             0
#define ADC_CHAIN_CHANNEL              1

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum {
    ADC_NOK = 0,
    ADC_OK = 1,
    TIMEOUT_STATE = 2,
    BUSY_STATE = 3
} ADC_ErrorStatus;

typedef struct {
    u8 *Chanel;
    u16 * Result;
    u8 size;
    void (* NotificationFunc)(void);
} Chain_Type;
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void ADC_voidInit();
ADC_ErrorStatus ADC_enumGetResultSync(u8 Copy_u8Channel, u16 * Copy_u16Result);
ADC_ErrorStatus ADC_enumStartConversionAsync(u8 Copy_u8Channel, void (* Copy_pvNotificationFunc)(void), u16 * Copy_pu16Result);
ADC_ErrorStatus ADC_enumStartChainAsync(Chain_Type * Copy_Chain);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

