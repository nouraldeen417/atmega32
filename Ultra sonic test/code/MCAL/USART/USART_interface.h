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
#ifndef XC_USART_INTERFACE_H
#define	XC_USART_INTERFACE_H


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"../../lip/Macros.h"
#include"../../lip/STD_TYPES.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define ENABLE                                                      1
#define DISABLE                                                     0

#define USART_MODE_ASYNCHRONOUS                                     0
#define USART_MODE_SYNCHRONOUS                                      1

#define  USART_1_BIT_SELECT                                         0
#define  USART_2_BIT_SELECT                                         1

#define USART_PARITY_DISABLE                                        0
#define USART_EVEN_PARITY                                           2
#define USART_ODD_PARITY                                            3 


#define USART_CHARACTER_SIZE_5_BIT                                  0 
#define USART_CHARACTER_SIZE_6_BIT                                  1 
#define USART_CHARACTER_SIZE_7_BIT                                  2 
#define USART_CHARACTER_SIZE_8_BIT                                  3 
#define USART_CHARACTER_SIZE_9_BIT                                  4 

#define USART_CLOCK_POLARITY_TX_RISING_RX_FALLING                   0 
#define USART_CLOCK_POLARITY_TX_FALLING_RX_RISING                   1 


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
 void USART_voidInit();
 
ErrorStatus   USART_enumSendData (u8 Copy_u8Data);
 
ErrorStatus   USART_enumSendStringSync (const u8 *Copy_u8Data);
ErrorStatus   USART_enumSendStringASync (const u8 *Copy_u8Data,void (* USART_pvNotificationFunc)(void));
 
ErrorStatus USART_enumRecieveBufferSync( u8 * Copy_pu8Data, u32 Copy_u32BufferSize);
ErrorStatus USART_enumRecieveBufferASync( u8 *Copy_u8Data, void (* CopypvNotificationFunc)(void), u32 Copy_u32BufferSize);
 
ErrorStatus   USART_enumRecevieData (u8 * Copy_u8ReceviedData) ;

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

