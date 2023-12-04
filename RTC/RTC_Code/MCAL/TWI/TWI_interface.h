/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <MACROS>
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef _TWI_INTERFACE_H
#define _TWI_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "..\..\lip\Macros.h"
#include "..\..\lip\STD_TYPES.h"  
#include"TWI_private.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define TWI_MASTER                       0
#define TWI_SLAVE                        1

#define TWI_DISABLE                       0
#define TWI_ENABLE                        1

#define TWI_INTERRUPT_DISABLE             0
#define TWI_INTERRUPT_ENABLE              1

#define TWI_ACKNOWLEDGE_DISABLE           0
#define TWI_ACKNOWLEDGE_ENABLE            1

#define TWI_PRESCALER_1                   1
#define TWI_PRESCALER_4                   4
#define TWI_PRESCALER_16                  16
#define TWI_PRESCALER_64                  64


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum{
    TWI_NoErr=0,
    TWI_StartConditionErr=1,
    TWI_RebeatedStartConditionErr=2,
    TWI_SlaveAddressWithWriteErr=3,
    TWI_SlaveAddressWithReadErr=4,
    TWI_MasterWriteByteErr=5,
    TWI_MasterReadByteErr=6,
    TWI_SlaveWriteByteErr=7,
    TWI_SlaveReadByteErr=8,

}TWI_ErrorState;
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void TWI_voidMasterInit(u8 Copy_u8SlaveAdd);
void TWI_voidSlaveInit(u8 Copy_u8SlaveAdd);

void TWI_voidSendStopCondition(void);
TWI_ErrorState TWI_enumSendStartCondition(void);
TWI_ErrorState TWI_enumSendRepeatedStartCondition(void);

TWI_ErrorState TWI_enumSendSlaveAddressWithWrite(u8 Copy_u8SlaveAdd);
TWI_ErrorState TWI_enumSendSlaveAddressWithRead(u8 Copy_u8SlaveAdd);

TWI_ErrorState TWI_enumMasterWriteDataByte(u8 Copy_u8DataByte);
TWI_ErrorState TWI_enumMasterReadDataByte(u8 *Copy_pu8DataByte);

TWI_ErrorState TWI_enumSlaveWriteDataByte(u8 Copy_u8DataByte);
TWI_ErrorState TWI_enumSlaveReadDataByte(u8 *Copy_pu8DataByte);


#endif  /* FILE_NAME_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/







