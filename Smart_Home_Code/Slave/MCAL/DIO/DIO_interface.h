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
#ifndef XC_DIO_interface_H
#define	XC_DIO_interface_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include <xc.h> // include processor files - each processor file is guarded.  
#include "../../lip/STD_TYPES.h"
#include "DIO_private.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define DIO_PIN_OUTPUT 1
#define DIO_PIN_INPUT  0
/*Ports*/
#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3
/*PINS*/
#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7
/*States*/
#define DIO_PIN_HIGH  1
#define DIO_PIN_LOW   0
/*PORTs Direction*/
#define DIO_PORT_OUTPUT 0xff
#define DIO_PORT_INPUT 0
#define DIO_PORT_HIGH  0xff
#define DIO_PORT_LOW   0
/*port Nipple*/
#define DIO_NIBBLE_HIGH  1
#define DIO_NIBBLE_LOW   0
/*PUD Bit*/
#define DIO_PULLUP_BIT   2

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum {
    DIO_NOK=0,
    DIO_OK=1
}DIO_ErrorStatus;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
DIO_ErrorStatus DIO_voidSetPinDirection  (u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);
DIO_ErrorStatus DIO_voidSetPinValue      (u8 Copy_u8Port, u8 Copy_u8Pin, u8 Value);
DIO_ErrorStatus DIO_u8ReadPinState       (u8 Copy_u8Port, u8 Copy_u8Pin, u8 * Copy_PtrData);
DIO_ErrorStatus DIO_u8GetPinValue        (u8 Copy_u8Port, u8 Copy_u8Pin ,u8 * Copy_PtrData);
DIO_ErrorStatus DIO_voidSetPORTDirection (u8 Copy_u8Port, u8 Copy_u8Direction);
DIO_ErrorStatus DIO_voidSetPORTValue     (u8 Copy_u8Port, u8 Value);
DIO_ErrorStatus DIO_u8GetPORTValue       (u8 Copy_u8Port, u8 * Copy_PtrData);
DIO_ErrorStatus DIO_voidTogglePinValue   (u8 Copy_u8Port, u8 Copy_u8Pin);
DIO_ErrorStatus DIO_voidSetPortHIGHNibble(u8 Copy_u8Port, u8 Copy_u8Value);
DIO_ErrorStatus DIO_voidSetPortLOWNibble (u8 Copy_u8Port, u8 Copy_u8Value);
DIO_ErrorStatus DIO_voidEnablePullup     (u8 Copy_u8Port, u8 Copy_u8Pin);
DIO_ErrorStatus DIO_voidDisablePullup    ();
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

