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
#ifndef XC_EXTI_INTERFACE_H
#define	XC_EXTI_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include <xc.h> // include processor files - each processor file is guarded.  
#include "../../lip/STD_TYPES.h"
#include"EXTI_private.h"
#include"EXTI_config.h"
#include"../../lip/Macros.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define EXTI_INT0   6
#define EXTI_INT1   7
#define EXTI_INT2   5
/*EXT_SENSE_MODE*/
#define EXTI_FALLING_EDGE   4
#define EXTI_RISING_EDGE    3
#define EXTI_ON_CHANGE      2
#define EXTI_LOW_LEVEL      1

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum {
    EXTI_NOK=0,
    EXTI_OK=1
}EXTI_ErrorStatus;
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
EXTI_ErrorStatus EXTI_enumEnableInterrupt (u8 EXTI_u8CopyINT);
EXTI_ErrorStatus EXTI_enumDisableInterrupt(u8 EXTI_u8CopyINT);
EXTI_ErrorStatus EXTI_enumClearFlag       (u8 EXTI_u8CopyINT);
u8               EXTI_u8GetFlag           (u8 EXTI_u8CopyINT);
void             EXTI_voidSetCallBack     (void (* EXTI_ptrvoidCopyCallBack) (void),u8 EXTI_u8CopyINT);
void             EXTI_voidInit            (void                                                      );
void             EXTI_voidSetSignalConf   (u8 EXTI_CopySenseMode,u8 EXTI_u8CopyINT                   );

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

