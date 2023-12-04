
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  ULTRA+program.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "..\..\lip\Macros.h"
#include<util/delay.h>
#include "..\..\lip\STD_TYPES.h"  
#include "ULTRA_interface.h"
#include "ULTRA_config.h"
/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
static u16 ULTRA_u16OverFlowCounter=0;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
 * \Description     : Describe this service                                    
 *                                                                             
 * \Sync\Async      : Synchronous                                               
 * \Reentrancy      : Non Reentrant                                             
 * \Parameters (in) : Copy_u8IntNumber   Parameter Describtion                     
 * \Parameters (out): None                                                      
 * \Return value:   : None
 *                                  
 *******************************************************************************/
void ULTRA_ICUHandler() {
    ULTRA_u16OverFlowCounter ++;
}

void ULTRA_SetTrigger(UltraS_Type *Copy_UltraConf) {
    DIO_voidSetPinDirection(Copy_UltraConf->PortNumber, Copy_UltraConf->PinNumber, DIO_PIN_OUTPUT);
    DIO_voidSetPinValue(Copy_UltraConf->PortNumber, Copy_UltraConf->PinNumber, DIO_PIN_HIGH);
    _delay_us(20);
    DIO_voidSetPinValue(Copy_UltraConf->PortNumber, Copy_UltraConf->PinNumber, DIO_PIN_LOW);

}

void ULTRA_voidInit() {
    TIMER_voidICUInit();
    TIMER_SetCallBack(TIMER1_OVF_VECTOR, ULTRA_ICUHandler);
}

// d=v*t  2t=ticks/f  d=ticks*((v/f)/2)=ticks/(2f/v)
ErrorStatus ULTRA_GetDistance(u8 *Copy_u8distanceVal) {
    ErrorStatus LOC_Err = OK;
    u16 LOC_u8Ticks;
    if (Copy_u8distanceVal != NULL) {
        TIMER_enumDetectCaptureSync(TIMER_ICU_STATE_RAISING, & LOC_u8Ticks);
        TIMER1_voidSetPreload(0);
        TIMER_enumDetectCaptureSync(TIMER_ICU_STATE_FALLING, & LOC_u8Ticks);
        LOC_u8Ticks += ULTRA_u16OverFlowCounter * ULTRA_OVF_TICKS; 
        *Copy_u8distanceVal = LOC_u8Ticks /((2*ICU_FREQUENCY)/ULTRA_VELOCITY_CM_S);
        if((*Copy_u8distanceVal) > ULTRA_MAX_DISTANCE){
            LOC_Err=NOK;
        }
    } else {
        LOC_Err = NULL_PointerState;
    }
    return LOC_Err;
}
/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
 * \Description     : Describe this service                                    
 *                                                                             
 * \Sync\Async      : Synchronous                                               
 * \Reentrancy      : Non Reentrant                                             
 * \Parameters (in) : Copy_u8IntNumber   Parameter Describtion                     
 * \Parameters (out): None                                                      
 * \Return value:   : Std_ReturnType  OK
 *                                    NOK                                  
 *******************************************************************************/

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/








