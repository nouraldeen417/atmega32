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
#include"SPI_interface.h"
/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
static u8 SPI_State = IDLE;
static u8 SPI_u8Size = 0;
static u8 SPI_u8Index = 0;
static const u8 *SPI_pu8TData = NULL;
static u8 *SPI_pu8RData = NULL;

void (*SPI_pvCallBackFunction)(void) = NULL;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 F *********************************************************************************************************************/
void SPI_voidInit(void);

ErrorStatus SPI_enumInitConfig(SPI_confType * Copy_SpiConfig) {
    ErrorStatus LOC_ErrorState = OK;

    if (Copy_SpiConfig != NULL) {
        if (Copy_SpiConfig->SPI_u8Enable == SPI_ENABLE) {
            SET_BIT(SPI_SPCR, SPCR_SPE_BIT);
        } else if (Copy_SpiConfig->SPI_u8Enable == SPI_DISABLE) {
            CLEAR_BIT(SPI_SPCR, SPCR_SPE_BIT);
        } else {
            LOC_ErrorState = NOK;

        }

        if (Copy_SpiConfig->SPI_u8InterruptEnable == SPI_INTERRUPT_ENABLE) {
            SET_BIT(SPI_SPCR, SPCR_SPIE_BIT);
        } else if (Copy_SpiConfig->SPI_u8Enable == SPI_INTERRUPT_DISABLE) {
            CLEAR_BIT(SPI_SPCR, SPCR_SPIE_BIT);
        } else {
            LOC_ErrorState = NOK;

        }

        if (Copy_SpiConfig->SPI_u8DataOrder == SPI_DATA_LSB_FIRST) {
            SET_BIT(SPI_SPCR, SPCR_DORD_BIT);
        } else if (Copy_SpiConfig->SPI_u8DataOrder == SPI_DATA_MSB_FIRST) {
            CLEAR_BIT(SPI_SPCR, SPCR_DORD_BIT);
        } else {
            LOC_ErrorState = NOK;

        }

        if (Copy_SpiConfig->SPI_u8MasterSlaveSelect == SPI_MASTER) {
            SET_BIT(SPI_SPCR, SPCR_MSTR_BIT);
        } else if (Copy_SpiConfig->SPI_u8MasterSlaveSelect == SPI_SLAVE) {
            CLEAR_BIT(SPI_SPCR, SPCR_MSTR_BIT);
        } else {
            LOC_ErrorState = NOK;

        }

        if (Copy_SpiConfig->SPI_u8ClockPolarity == SPI_FALLING_LEADING_RISING_TRAILING) {
            SET_BIT(SPI_SPCR, SPCR_CPOL_BIT);
        } else if (Copy_SpiConfig->SPI_u8ClockPolarity == SPI_RISING_LEADING_FALLING_TRAILING) {
            CLEAR_BIT(SPI_SPCR, SPCR_CPOL_BIT);
        } else {
            LOC_ErrorState = NOK;

        }

        if (Copy_SpiConfig->SPI_u8ClockPhase == SPI_SETUP_LEADING_SAMPLE_TRAILING) {
            SET_BIT(SPI_SPCR, SPCR_CPOL_BIT);
        } else if (Copy_SpiConfig->SPI_u8ClockPhase == SPI_SAMPLE_LEADING_SETUP_TRAILING) {
            CLEAR_BIT(SPI_SPCR, SPCR_CPOL_BIT);
        } else {
            LOC_ErrorState = NOK;

        }
        switch (Copy_SpiConfig->SPI_u8ClockRate) {
            case SPI_FREQ_DIVIDED_BY_4:
                CLEAR_BIT(SPI_SPCR, SPCR_SPR0_BIT);
                CLEAR_BIT(SPI_SPCR, SPCR_SPR1_BIT);
                CLEAR_BIT(SPI_SPSR, SPSR_SPI2X_BIT);
                break;
            case SPI_FREQ_DIVIDED_BY_16:
                SET_BIT(SPI_SPCR, SPCR_SPR0_BIT);
                CLEAR_BIT(SPI_SPCR, SPCR_SPR1_BIT);
                CLEAR_BIT(SPI_SPSR, SPSR_SPI2X_BIT);
                break;
            case SPI_FREQ_DIVIDED_BY_64:
                CLEAR_BIT(SPI_SPCR, SPCR_SPR0_BIT);
                SET_BIT(SPI_SPCR, SPCR_SPR1_BIT);
                CLEAR_BIT(SPI_SPSR, SPSR_SPI2X_BIT);
                break;
            case SPI_FREQ_DIVIDED_BY_128:
                SET_BIT(SPI_SPCR, SPCR_SPR0_BIT);
                SET_BIT(SPI_SPCR, SPCR_SPR1_BIT);
                CLEAR_BIT(SPI_SPSR, SPSR_SPI2X_BIT);
                break;
            case SPI_FREQ_DIVIDED_BY_2:
                CLEAR_BIT(SPI_SPCR, SPCR_SPR0_BIT);
                CLEAR_BIT(SPI_SPCR, SPCR_SPR1_BIT);
                SET_BIT(SPI_SPSR, SPSR_SPI2X_BIT);
                break;
            case SPI_FREQ_DIVIDED_BY_8:
                SET_BIT(SPI_SPCR, SPCR_SPR0_BIT);
                CLEAR_BIT(SPI_SPCR, SPCR_SPR1_BIT);
                SET_BIT(SPI_SPSR, SPSR_SPI2X_BIT);
                break;
            case SPI_FREQ_DIVIDED_BY_32:
                CLEAR_BIT(SPI_SPCR, SPCR_SPR0_BIT);
                SET_BIT(SPI_SPCR, SPCR_SPR1_BIT);
                SET_BIT(SPI_SPSR, SPSR_SPI2X_BIT);
                break;
            default:
                LOC_ErrorState = NOK;
                break;
        }

    } else {
        LOC_ErrorState = OK;
    }
    return LOC_ErrorState;
}

ErrorStatus SPI_enumTranceive(u8 Copy_u8TData, u8 * Copy_u8RData) {
    ErrorStatus LOC_ErroreState = OK;
    u32 LOC_u32TimeOutCount = 0;
    if (SPI_State == IDLE) {
        SPI_State = BUSY;
        SPI_SPDR = Copy_u8TData;

        while((GET_BIT(SPI_SPSR, SPSR_SPIF_BIT) == 0) && LOC_u32TimeOutCount < SPI_TRANSFER_TIME_OUT) {
            LOC_u32TimeOutCount++;
        }
        if (LOC_u32TimeOutCount == SPI_TRANSFER_TIME_OUT) {
            LOC_ErroreState = Time_OUT_State;
        } else {
            *Copy_u8RData = SPI_SPDR;
        }
        SPI_State = IDLE;
    } else {
        LOC_ErroreState = Busy_State;
    }

    return LOC_ErroreState;
}

ErrorStatus SPI_enumBufferTranceiverSynch(const u8 * Copy_u8TData, u8 * Copy_u8RData, u8 Copy_u8BufferSize) {
    ErrorStatus LOC_ErroreState = OK;
    u8 LOC_Iterator = 0;

    if ((Copy_u8TData != NULL) && (Copy_u8RData != NULL)) {

        for (LOC_Iterator = 0; LOC_Iterator < Copy_u8BufferSize; LOC_Iterator++) {
            SPI_enumTranceive(Copy_u8TData[LOC_Iterator], &Copy_u8RData[LOC_Iterator]);
        }

    } else {
        LOC_ErroreState = NOK;
    }

    return LOC_ErroreState;

}

ErrorStatus SPI_enumBufferTranceiverAsynch(SPI_BufferType * Copy_bufferConf) {
    ErrorStatus LOC_ErroreState = OK;
    if (SPI_State == IDLE) {

        if (Copy_bufferConf != NULL && Copy_bufferConf->SPI_u8TData != NULL && Copy_bufferConf->SPI_u8RData != NULL && Copy_bufferConf->SPI_pvNotifaction != NULL) {
            SPI_State == BUSY;
            SPI_pu8TData = Copy_bufferConf->SPI_u8TData;
            SPI_pu8RData = Copy_bufferConf->SPI_u8RData;
            SPI_u8Size = Copy_bufferConf->SPI_u8BufferSize;
            SPI_pvCallBackFunction = Copy_bufferConf->SPI_pvNotifaction;
            SPI_u8Index = 0;
            /*start tranceive*/
            SPI_SPDR = SPI_pu8TData[SPI_u8Index];
            /*Interrupt Enable*/
            SET_BIT(SPI_SPCR, SPCR_SPIE_BIT);
        }
        else {
            LOC_ErroreState = NULL_PointerState;
        }

    } else {
        LOC_ErroreState = Busy_State;
    }

    return LOC_ErroreState;

}


void __vector_12 (void)		__attribute__ ((signal)) ;
void __vector_12 (void)
{
    /*receive data*/
    SPI_pu8RData[SPI_u8Index] = SPI_SPDR;
    SPI_u8Index++;
    if(SPI_u8Index == SPI_u8Size){
            /*Interrupt Enable*/
            CLEAR_BIT(SPI_SPCR, SPCR_SPIE_BIT);
            SPI_pvCallBackFunction();
    }else{

        SPI_SPDR = SPI_pu8TData[SPI_u8Index];
    }
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

