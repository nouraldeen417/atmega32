
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  DIO_program.c
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
#include "TWI_interface.h"
#include "TWI_config.h"

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

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

void TWI_voidMasterInit(u8 Copy_u8SlaveAdd) {
    //set TWBR Val
    TWI_TWBR = (u8) (((F_CPU / TWI_SCL_CLOCK) - 16) / (2 * TWI_PRESCALER));
    //set prescaler 
    if (TWI_PRESCALER == TWI_PRESCALER_1) {
        CLEAR_BIT(TWI_TWSR, TWSR_TWPS0_BIT);
        CLEAR_BIT(TWI_TWSR, TWSR_TWPS1_BIT);
    } else if (TWI_PRESCALER == TWI_PRESCALER_4) {
        SET_BIT(TWI_TWSR, TWSR_TWPS0_BIT);
        CLEAR_BIT(TWI_TWSR, TWSR_TWPS1_BIT);
    } else if (TWI_PRESCALER == TWI_PRESCALER_16) {
        CLEAR_BIT(TWI_TWSR, TWSR_TWPS0_BIT);
        SET_BIT(TWI_TWSR, TWSR_TWPS1_BIT);
    } else if (TWI_PRESCALER == TWI_PRESCALER_64) {
        SET_BIT(TWI_TWSR, TWSR_TWPS0_BIT);
        SET_BIT(TWI_TWSR, TWSR_TWPS1_BIT);
    }

    // Set Address 
    if (Copy_u8SlaveAdd != 0) {
        TWI_TWAR = (Copy_u8SlaveAdd << 1);
    } else {

        // Do nothing
    }
    // Enable ACK
    SET_BIT(TWI_TWCR, TWCR_TWEA_BIT);

    // Enable TWI
    SET_BIT(TWI_TWCR, TWCR_TWEN_BIT);

}

void TWI_voidSlaveInit(u8 Copy_u8SlaveAdd) {

    // Set Address 
    if (Copy_u8SlaveAdd != 0) {
        TWI_TWAR = (Copy_u8SlaveAdd << 1);
    } else {

        // Do nothing
    }
    // Enable ACK
    SET_BIT(TWI_TWCR, TWCR_TWEA_BIT);

    // Enable TWI
    SET_BIT(TWI_TWCR, TWCR_TWEN_BIT);
}

TWI_ErrorState TWI_enumSendStartCondition(void) {
    TWI_ErrorState LOC_ErrorState = TWI_NoErr;
    //Clear Interrupt Flag
    SET_BIT(TWI_TWCR, TWCR_TWINT_BIT);
    //Send START condition
    SET_BIT(TWI_TWCR, TWCR_TWSTA_BIT);
    //Wait for TWINT Flag set.
    while (GET_BIT(TWI_TWCR, TWCR_TWINT_BIT) == 0);
    //Check value of TWI Status Register
    if ((TWI_TWSR & TWSR_TWS_MASK) != START_ACK) {
        LOC_ErrorState = TWI_StartConditionErr;
    } else {
        // Do Nothing
    }
    return LOC_ErrorState;
}

TWI_ErrorState TWI_enumSendRepeatedStartCondition(void) {
    TWI_ErrorState LOC_ErrorState = TWI_NoErr;
    //Clear Interrupt Flag
    SET_BIT(TWI_TWCR, TWCR_TWINT_BIT);
    //Send START condition
    SET_BIT(TWI_TWCR, TWCR_TWSTA_BIT);
    //Wait for TWINT Flag set.
    while (GET_BIT(TWI_TWCR, TWCR_TWINT_BIT) == 0);
    //Check value of TWI Status Register
    if ((TWI_TWSR & TWSR_TWS_MASK) != REBEATED_START_ACK) {
        LOC_ErrorState = TWI_RebeatedStartConditionErr;
    } else {
        // Do Nothing
    }
    return LOC_ErrorState;
}

void TWI_voidSendStopCondition(void) {
    //Clear Interrupt Flag
    SET_BIT(TWI_TWCR, TWCR_TWINT_BIT);
    //Send STOP condition
    SET_BIT(TWI_TWCR, TWCR_TWSTO_BIT);
    //Clear Start Condition
    CLEAR_BIT(TWI_TWCR,TWCR_TWSTA_BIT);
//while(TWCR&(1<<TWSTO));
}

TWI_ErrorState TWI_enumSendSlaveAddressWithWrite(u8 Copy_u8SlaveAdd) {
    ErrorStatus LOC_ErrorState = TWI_NoErr;
    //Load SLA_W into TWDR Register
    TWI_TWDR = (Copy_u8SlaveAdd << 1);
    CLEAR_BIT(TWI_TWDR, TWDR_RW_BIT);
    //Clear Interrupt Flag
    SET_BIT(TWI_TWCR, TWCR_TWINT_BIT);
    //Wait for TWINT Flag set.
    while (GET_BIT(TWI_TWCR, TWCR_TWINT_BIT) == 0);
    //Check value of TWI Status Register
    if ((TWI_TWSR & TWSR_TWS_MASK) != SLAVE_ADDRESS_WRITE_ACK) {
        LOC_ErrorState = TWI_SlaveAddressWithWriteErr;
    } else {
        // Do Nothing
    }

    return LOC_ErrorState;

}

TWI_ErrorState TWI_enumSendSlaveAddressWithRead(u8 Copy_u8SlaveAdd) {
    ErrorStatus LOC_ErrorState = TWI_NoErr;
    //Load SLA_R into TWDR Register
    TWI_TWDR = (Copy_u8SlaveAdd << 1);
    SET_BIT(TWI_TWDR, TWDR_RW_BIT);
    //Clear Interrupt Flag
    SET_BIT(TWI_TWCR, TWCR_TWINT_BIT);
    //Wait for TWINT Flag set.
    while (GET_BIT(TWI_TWCR, TWCR_TWINT_BIT) == 0);
    //Check value of TWI Status Register
    if ((TWI_TWSR & TWSR_TWS_MASK) != SLAVE_ADDRESS_READ_ACK) {
        LOC_ErrorState = TWI_SlaveAddressWithReadErr;
    } else {
        // Do Nothing
    }

    return LOC_ErrorState;
}

TWI_ErrorState TWI_enumMasterWriteDataByte(u8 Copy_u8DataByte) {
    ErrorStatus LOC_ErrorState = TWI_NoErr;
    //Load SLA_R into TWDR Register
    TWI_TWDR = Copy_u8DataByte;
    //Clear Interrupt Flag
    SET_BIT(TWI_TWCR, TWCR_TWINT_BIT);
    //Wait for TWINT Flag set.
    while (GET_BIT(TWI_TWCR, TWCR_TWINT_BIT) == 0);
    //Check value of TWI Status Register
    if ((TWI_TWSR & TWSR_TWS_MASK) != MASTER_WRITE_BYTE_ACK) {
        LOC_ErrorState = TWI_MasterWriteByteErr;
    } else {
        // Do Nothing
    }

    return LOC_ErrorState;

}

TWI_ErrorState TWI_enumMasterReadDataByte(u8 *Copy_pu8DataByte) {
    ErrorStatus LOC_ErrorState = TWI_NoErr;
    //Clear Interrupt Flag
    SET_BIT(TWI_TWCR, TWCR_TWINT_BIT);
    //Wait for TWINT Flag set.
    while (GET_BIT(TWI_TWCR, TWCR_TWINT_BIT) == 0);
    //Check value of TWI Status Register
    if ((TWI_TWSR & TWSR_TWS_MASK) != MASTER_READ_BYTE_ACK) {
        LOC_ErrorState = TWI_MasterReadByteErr;
    } else {
        //Read Data From TWDR Register
        * Copy_pu8DataByte = TWI_TWDR;
    }

    return LOC_ErrorState;
}

TWI_ErrorState TWI_enumSlaveWriteDataByte(u8 Copy_u8DataByte) {
    ErrorStatus LOC_ErrorState = TWI_NoErr;
    //Clear Interrupt Flag
    SET_BIT(TWI_TWCR, TWCR_TWINT_BIT);
    //Wait for TWINT Flag set.
    while (GET_BIT(TWI_TWCR, TWCR_TWINT_BIT) == 0);
    //Check value of TWI Status Register
    if ((TWI_TWSR & TWSR_TWS_MASK) != SLAVE_ADD_RECEIVED_WRITE_REQ) {
        LOC_ErrorState = TWI_SlaveWriteByteErr;
    } else {
        //Load SLA_W into TWDR Register
        TWI_TWDR = Copy_u8DataByte;
    }
    //Clear Interrupt Flag
    SET_BIT(TWI_TWCR, TWCR_TWINT_BIT);
    //Wait for TWINT Flag set.
    while (GET_BIT(TWI_TWCR, TWCR_TWINT_BIT) == 0);
    //Check value of TWI Status Register
    if ((TWI_TWSR & TWSR_TWS_MASK) != SLAVE_WRITE_BYTE_ACK) {
        LOC_ErrorState = TWI_SlaveWriteByteErr;
    } else {
        // Do Nothing
    }

    return LOC_ErrorState;
}

TWI_ErrorState TWI_enumSlaveReadDataByte(u8 *Copy_pu8DataByte) {
    ErrorStatus LOC_ErrorState = TWI_NoErr;
    //Clear Interrupt Flag
    SET_BIT(TWI_TWCR, TWCR_TWINT_BIT);
    //Wait for TWINT Flag set.
    while (GET_BIT(TWI_TWCR, TWCR_TWINT_BIT) == 0);
    //Check value of TWI Status Register
    if ((TWI_TWSR & TWSR_TWS_MASK) != SLAVE_ADD_RECEIVED_READ_REQ) {
        LOC_ErrorState = TWI_SlaveReadByteErr;
    } else {
     // Do Nothing       
    }
    //Clear Interrupt Flag
    SET_BIT(TWI_TWCR, TWCR_TWINT_BIT);
    //Wait for TWINT Flag set.
    while (GET_BIT(TWI_TWCR, TWCR_TWINT_BIT) == 0);
    //Check value of TWI Status Register
    if ((TWI_TWSR & TWSR_TWS_MASK) != SLAVE_READ_BYTE_ACK) {
        LOC_ErrorState = TWI_SlaveReadByteErr;
    } else {
        //Load SLAVE R into TWDR Register
        * Copy_pu8DataByte = TWI_TWDR;
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
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/

