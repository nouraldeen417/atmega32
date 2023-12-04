/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <MACROS>
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef _SEVEN_SEGMENT_INTERFACE_H
#define _SEVEN_SEGMENT_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "..\..\lip\Macros.h"
#include "..\..\lip\STD_TYPES.h"
#include"7Seg_private.h"
#include"../../MCAL/DIO/DIO_interface.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define SSD_COMMON_ANODE                    0
#define SSD_COMMON_CATHODE                  1


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct {
  u8 SSD_Type;  
  u8 SSD_DataPort;  
  u8 SSD_EnablePort;  
  u8 SSD_EnablePin;  
}SSD_Type;
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
ErrorStatus SSD_voidInitDataPort(SSD_Type *Copy_Conf);
ErrorStatus SSD_voidEnable      (SSD_Type *Copy_Conf);
ErrorStatus SSD_voidDisable     (SSD_Type *Copy_Conf );
ErrorStatus SSD_voidSendNumber  (SSD_Type *Copy_Conf, u8 Copy_u8Number);
#endif /* FILE_NAME_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
