/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <MACROS>
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef _SPI_INTERFACE_H
#define _SPI_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "..\..\lip\Macros.h"
#include "..\..\lip\STD_TYPES.h"  
#include "SPI_private.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/**/
#define SPI_ENABLE                              1
#define SPI_DISABLE                             0
/**/
#define SPI_INTERRUPT_ENABLE                    1
#define SPI_INTERRUPT_DISABLE                   0
/**/
#define SPI_DATA_LSB_FIRST                      1
#define SPI_DATA_MSB_FIRST                      0
/**/
#define SPI_MASTER                              1
#define SPI_SLAVE                               0
/**/
#define SPI_RISING_LEADING_FALLING_TRAILING 	0
#define SPI_FALLING_LEADING_RISING_TRAILING		1
/**/
#define SPI_SAMPLE_LEADING_SETUP_TRAILING 		0
#define SPI_SETUP_LEADING_SAMPLE_TRAILING		1
/**/
#define SPI_FREQ_DIVIDED_BY_2					0
#define SPI_FREQ_DIVIDED_BY_4					1
#define SPI_FREQ_DIVIDED_BY_8					2
#define SPI_FREQ_DIVIDED_BY_16					3
#define SPI_FREQ_DIVIDED_BY_32					4
#define SPI_FREQ_DIVIDED_BY_64					5
#define SPI_FREQ_DIVIDED_BY_128					6

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct {
    u8 SPI_u8Enable;
    u8 SPI_u8InterruptEnable;
    u8 SPI_u8DataOrder;
    u8 SPI_u8MasterSlaveSelect;
    u8 SPI_u8ClockPolarity;
    u8 SPI_u8ClockPhase;
    u8 SPI_u8ClockRate;
}SPI_confType;

typedef struct {
const u8 *SPI_u8TData;
    u8 *SPI_u8RData;
    u8 SPI_u8BufferSize;
    void (* SPI_pvNotifaction)(void)  ;
}SPI_BufferType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

void SPI_VoidInit(void) ;
ErrorStatus SPI_enumInitConfig (SPI_confType * Copy_SpiConfig) ;
ErrorStatus SPI_enumTranceive  (u8 Copy_u8TData , u8 * Copy_u8RData) ;
ErrorStatus SPI_enumBufferTranceiverSynch (const u8 * Copy_u8TData , u8 * Copy_u8RData , u8 Copy_u8BufferSize) ;
ErrorStatus SPI_enumBufferTranceiverAsynch (SPI_BufferType * spi_buffer) ;

#endif  /* FILE_NAME_H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/







