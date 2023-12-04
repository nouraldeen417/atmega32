/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  EEPROM_program.c
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
#include "Internal_EEPROM_interface.h"
#include<util/delay.h>

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
//#define F_CPU                  8000000UL
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static u8 EEPROM_State = IDLE;
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

ErrorStatus EEPROM_enumSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8DataByte) {
    ErrorStatus LOC_ErrorState = OK;
    if (EEPROM_State == IDLE) {
        EEPROM_State = BUSY;
        /* Wait for completion of previous write*/
        while (GET_BIT(EECR, EECR_EEWE_BIT) == 1);
        /* Set Address 10 Bits Max 0:1023  */
        EEAR = Copy_u16LocationAddress & 0x3F;
        /* Set Data  */
        EEDR = Copy_u8DataByte;
        /* Start eeprom write by setting EEMWE */
        SET_BIT(EECR, EECR_EEMWE_BIT);
        /* Start eeprom write by setting EEWE */
        SET_BIT(EECR, EECR_EEWE_BIT);
        EEPROM_State = IDLE;
    } else {
        LOC_ErrorState = Busy_State;
    }
    return LOC_ErrorState;
}

ErrorStatus EEPROM_enumReadDataByte(u16 Copy_u16LocationAddress, u8 * Copy_pu8Data) {
    ErrorStatus LOC_ErrorState = OK;
    if (EEPROM_State == IDLE) {
        EEPROM_State == BUSY;
        /* Wait for completion of previous write*/
        while (GET_BIT(EECR, EECR_EEWE_BIT) == 1);
        /* Set Address 10 Bits Max 0:1023  */
        EEAR = Copy_u16LocationAddress & 0x3F;
        /* Start EEPROM Read by setting EERE */
        SET_BIT(EECR, EECR_EERE_BIT);
        *Copy_pu8Data = EEDR;
        EEPROM_State = IDLE;
    } else {
        LOC_ErrorState = Busy_State;
    }
    return LOC_ErrorState;
}

ErrorStatus EEPROM_enumSendBufferSync(u16 Copy_u16StartAddress, const u8 *Copy_u8Data, u32 Copy_u32BufferSize) {
    ErrorStatus LOC_ErrorState = OK;
    u32 LOC_Iterator;
        if (Copy_u8Data != NULL) {

            for (LOC_Iterator = 0; LOC_Iterator < Copy_u32BufferSize; LOC_Iterator++) {
                EEPROM_enumSendDataByte((Copy_u16StartAddress+LOC_Iterator),Copy_u8Data[LOC_Iterator]);
            }

        } else {
            LOC_ErrorState = NULL_PointerState;
        }
    
    return LOC_ErrorState;
}
ErrorStatus EEPROM_enumRecieveBufferSync(u16 Copy_u16StartAddress, u8 * Copy_pu8Data, u32 Copy_u32BufferSize){
    ErrorStatus LOC_ErrorState = OK;
    u32 LOC_Iterator;
    
        if (Copy_pu8Data != NULL) {
            
            for (LOC_Iterator = 0; LOC_Iterator < Copy_u32BufferSize; LOC_Iterator++) {
                EEPROM_enumReadDataByte((Copy_u16StartAddress+LOC_Iterator),& Copy_pu8Data[LOC_Iterator]);
            }
        } else {
            LOC_ErrorState = NULL_PointerState;
        }
    
    return LOC_ErrorState;

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
 *  END OF FILE: EEPROM_program.c
 *********************************************************************************************************************/
