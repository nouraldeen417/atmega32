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
#ifndef XC_USART_PRIVATE_H
#define	XC_USART_PRIVATE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include"../../lip/Macros.h"
#include"../../lip/STD_TYPES.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define USART_UDR_REG                                     *((volatile u8 *)0x2C)

/*UCSRA_REG_BITS  RXC TXC UDRE FE DOR PE U2X MPCM */
#define USART_UCSRA_REG                                   *((volatile u8 *)0x2B)
#define UCSRA_RXC_BIT                                      7 /* USART Receive Complete Flag*/
#define UCSRA_TXC_BIT                                      6 /* USART Transmit Complete Flag*/
#define UCSRA_UDRE_BIT                                     5 /* USART Data Register Empty Flag*/
#define UCSRA_FE_BIT                                       4 /* USART Frame Error Flag*/
#define UCSRA_DOR_BIT                                      3 /* USART  Data OverRun Flag*/
#define UCSRA_PE_BIT                                       2 /* USART Parity Error */
#define UCSRA_U2X_BIT                                      1 /* Double the USART Transmission Speed*/
#define UCSRA_MPCM_BIT                                     0 /* Multi-processor Communication Mode*/

/*UCSRB_REG_BITS RXCIE TXCIE UDRIE RXEN TXEN UCSZ2 RXB8 TXB8 */
#define USART_UCSRB_REG                                   *((volatile u8 *)0x2A)
#define UCSRB_RXCIE_BIT                                   7 /* RX Complete Interrupt Enable*/
#define UCSRB_TXCIE_BIT                                   6 /* TX Complete Interrupt Enable*/
#define UCSRB_UDRIE_BIT                                   5 /* USART Data Register Empty Interrupt Enable*/
#define UCSRB_RXEN_BIT                                    4 /* Receiver Enable*/
#define UCSRB_TXEN_BIT                                    3 /* Transmitter Enable*/
#define UCSRB_UCSZ2_BIT                                   2 /* Character Size*/
#define UCSRB_RXB8_BIT                                    1 /* Receive Data Bit 8*/
#define UCSRB_TXB8_BIT                                    0 /* Transmit Data Bit 8*/

/*UCSRC_REG_BIT URSEL UMSEL UPM1 UPM0 USBS UCSZ1 UCSZ0 UCPOL */
#define USART_UCSRC_REG                                   *((volatile u8 *)0x40)
#define UCSRC_URSEL_BIT                                   7 /* Register Select*/
#define UCSRC_UMSEL_BIT                                   6 /* USART Mode Select*/
#define UCSRC_UPM1_BIT                                    5 /* Parity Mode EN/DIS*/
#define UCSRC_UPM0_BIT                                    4 /* Parity Mode EN/DIS*/
#define UCSRC_USBS_BIT                                    3 /* Stop Bit Select*/
#define UCSRC_UCSZ1_BIT                                   2 /* Character Size*/
#define UCSRC_UCSZ0_BIT                                   1 /* Character Size*/
#define UCSRC_UCPOL_BIT                                   0 /* Clock Polarity*/

#define USART_UBRRL_REG                                   *((volatile u8 *)0x29)
#define USART_UBRRH_REG                                   *((volatile u8 *)0x40)

#define USART_TIME_OUT                                   10000000



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

