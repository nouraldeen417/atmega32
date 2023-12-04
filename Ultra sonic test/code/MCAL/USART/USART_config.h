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
#ifndef XC_USART_CONFIG_H
#define	XC_USART_CONFIG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"../../lip/Macros.h"
#include"../../lip/STD_TYPES.h"
#include"USART_interface.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define SYSTEM_FREQUENCY                                                8000000
#define USART_BAUD_RATE                                                 9600

/*Enable the USART Reciever:
  ENABLE
  DISABLE
 
 */
#define USART_RX_ENABLE                                                   ENABLE
/*Enable the USART Transmission:
  ENABLE
  DISABLE
 
 */

#define USART_TX_ENABLE                                                   ENABLE
/*Double the USART Transmission Speed:
  ENABLE
  DISABLE
 
 */
#define USART_DOUPLE_TRANSMISSION_SPEED                                  DISABLE

/* Multi-processor Communication Mode:
  ENABLE
  DISABLE
 
 */
#define USART_Multi_PROCESSOR_COMMUNICATION_MODE                         DISABLE

/* RX Complete Interrupt Enable:
  ENABLE
  DISABLE
 
 */
#define USART_RX_COMPLETE_INTERRUPT                                       ENABLE

/* TX Complete Interrupt Enable:
  ENABLE
  DISABLE
 
 */
#define USART_TX_COMPLETE_INTERRUPT                                       ENABLE

/* USART Data Register Empty Interrupt Enable:
  ENABLE
  DISABLE
 
 */
#define USART_DATA_REGISTER_EMPTY_INTERRUPT                              DISABLE


/*  USART Mode Select:
 USART_MODE_ASYNCHRONOUS 
 USART_MODESYNCHRONOUS 
 */
#define USART_MODE                                       USART_MODE_ASYNCHRONOUS 

/*   Parity Mode:
 USART_PARITY_DISABLE
 USART_EVEN_PARITY 
 USART_ODD_PARITY 
 */
#define USART_PARITY_MODE                                      USART_EVEN_PARITY 
 
/* Stop Bit Select:
 USART_1_BIT_SELECT
 USART_2_BIT_SELECT
 */
#define USART_STOP_BIT_SELECT                                 USART_1_BIT_SELECT
 
/*  Character Size:
 USART_CHARACTER_SIZE_5_BIT
 USART_CHARACTER_SIZE_6_BIT
 USART_CHARACTER_SIZE_7_BIT
 USART_CHARACTER_SIZE_8_BIT
 USART_CHARACTER_SIZE_9_BIT

 */
#define  USART_CHARACTER_SIZE                         USART_CHARACTER_SIZE_8_BIT

#if USART_MODE == USART_MODE_SYNCHRONOUS
/*  Character Size:
USART_CLOCK_POLARITY_TX_RISING_RX_FALLING
USART_CLOCK_POLARITY_TX_FALLING_RX_RISING
 */
#define  USART_CLOCK_POLARITY                                    USART_CLOCK_POLARITY_TX_RISING_RX_FALLING
 
#endif

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

