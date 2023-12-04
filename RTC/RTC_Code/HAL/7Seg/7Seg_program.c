
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  SevenSeg_program.c
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
#include "..\..\lip\STD_TYPES.h"  
#include"7Seg_interface.h"

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
static u8 LOC_u8SegArray[10] = {0b00111111,//0
                                0b00000110,//1
                                0b01011011,//2
                                0b01001111,//3
                                0b01100110,//4
                                0b01101101,//5
                                0b01111101,//6
                                0b01000111,//7
                                0b01111111,//8
                                0b01101111 //9
};
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
ErrorStatus SSD_voidInitDataPort(SSD_Type *Copy_Conf) {
    ErrorStatus LOC_Err = OK;
    DIO_voidSetPORTDirection(Copy_Conf->SSD_DataPort, DIO_PORT_OUTPUT);
    if (Copy_Conf->SSD_Type == SSD_COMMON_ANODE) {
        DIO_voidSetPORTValue(Copy_Conf->SSD_DataPort, DIO_PORT_HIGH);
    } else if (Copy_Conf->SSD_Type == SSD_COMMON_CATHODE) {
        DIO_voidSetPORTValue(Copy_Conf->SSD_DataPort, DIO_PORT_LOW);
    } else {
        LOC_Err = NOK;
    }
    return LOC_Err;
}

ErrorStatus SSD_voidEnable(SSD_Type *Copy_Conf) {
    ErrorStatus LOC_Err = OK;
    DIO_voidSetPinDirection(Copy_Conf->SSD_EnablePort, Copy_Conf->SSD_EnablePin, DIO_PIN_OUTPUT);
    if (Copy_Conf->SSD_Type == SSD_COMMON_ANODE) {
        DIO_voidSetPinValue(Copy_Conf->SSD_EnablePort, Copy_Conf->SSD_EnablePin, DIO_PIN_HIGH);
    } else if (Copy_Conf->SSD_Type == SSD_COMMON_CATHODE) {
        DIO_voidSetPinValue(Copy_Conf->SSD_EnablePort, Copy_Conf->SSD_EnablePin, DIO_PIN_LOW);
    } else {
        LOC_Err = NOK;
    }
    return LOC_Err;
}

ErrorStatus SSD_voidDisable(SSD_Type *Copy_Conf) {
    ErrorStatus LOC_Err = OK;
    DIO_voidSetPinDirection(Copy_Conf->SSD_EnablePort, Copy_Conf->SSD_EnablePin, DIO_PIN_OUTPUT);
    if (Copy_Conf->SSD_Type == SSD_COMMON_ANODE) {
        DIO_voidSetPinValue(Copy_Conf->SSD_EnablePort, Copy_Conf->SSD_EnablePin, DIO_PIN_LOW);
    } else if (Copy_Conf->SSD_Type == SSD_COMMON_CATHODE) {
        DIO_voidSetPinValue(Copy_Conf->SSD_EnablePort, Copy_Conf->SSD_EnablePin, DIO_PIN_HIGH);
    } else {
        LOC_Err = NOK;
    }
    return LOC_Err;

}

ErrorStatus SSD_voidSendNumber(SSD_Type *Copy_Conf, u8 Copy_u8Number) {
    ErrorStatus LOC_Err = OK;
    if (Copy_u8Number >= 0 && Copy_u8Number <= 9) {
        if (Copy_Conf->SSD_Type == SSD_COMMON_ANODE) {
            DIO_voidSetPORTValue(Copy_Conf->SSD_DataPort , ~(LOC_u8SegArray[Copy_u8Number]));
        } else if (Copy_Conf->SSD_Type == SSD_COMMON_CATHODE) {
            DIO_voidSetPORTValue(Copy_Conf->SSD_DataPort , LOC_u8SegArray[Copy_u8Number]);
        }
    } else {
        LOC_Err = NOK;
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
 * \Return value:   : None
 *                                  
 *******************************************************************************/

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

