/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <MACROS>
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef _TWI_PRIVATE_H
#define _TWI_PRIVATE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "..\..\lip\Macros.h"
#include "..\..\lip\STD_TYPES.h"  

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define TWI_TWDR   *((volatile u8 *)0x23)
#define TWI_TWAR   *((volatile u8 *)0x22)
#define TWI_TWSR   *((volatile u8 *)0x21)
#define TWI_TWBR   *((volatile u8 *)0x20)
#define TWI_TWCR   *((volatile u8 *)0x56)

/*TWINT TWEA TWSTA TWSTO TWWC TWEN ? TWIE TWCR*/

#define TWCR_TWINT_BIT         7        // TWI Interrupt Flag                  
#define TWCR_TWEA_BIT          6        // TWI Enable Acknowledge Bit          
#define TWCR_TWSTA_BIT         5        // TWI START Condition Bit          
#define TWCR_TWSTO_BIT         4        // TWI STOP Condition Bit          
#define TWCR_TWWC_BIT          3        // TWI Write Collision Flag          
#define TWCR_TWEN_BIT          2        // TWI Enable Bit          
#define TWCR_TWIE_BIT          0        // TWI Interrupt Enable          
/*TWSR BITS*/ 
#define TWSR_TWS_MASK          0xF8     // TWI Status
#define TWSR_TWPS1_BIT         1        // TWI Prescaler Bits
#define TWSR_TWPS0_BIT         1        // TWI Prescaler Bits

/*ACKS*/
#define START_ACK                            0x08
#define REBEATED_START_ACK                   0x10

#define SLAVE_ADDRESS_WRITE_ACK              0x18
#define SLAVE_ADDRESS_READ_ACK               0x40

#define MASTER_WRITE_BYTE_ACK                0x28
#define MASTER_READ_BYTE_ACK                 0x50

#define SLAVE_ADD_RECEIVED_WRITE_REQ         0x60
#define SLAVE_ADD_RECEIVED_READ_REQ          0xA8

#define SLAVE_WRITE_BYTE_ACK                 0xB8
#define SLAVE_READ_BYTE_ACK                  0x80

#define ARBITRATION_LOST                     0x38


/*Write / Read Data BIT*/
#define TWDR_RW_BIT                       0
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
#endif  /* FILE_NAME_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/







