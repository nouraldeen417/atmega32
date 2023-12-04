/*
 * File:   USART_program.c
 * Author: nour
 *
 * Created on September 22, 2023, 2:53 PM
 */
#include"USART_interface.h"
#include"USART_private.h"
#include"USART_config.h"


/*Global pointer to function to carry the notification function called by ISR*/
static void (* USART_pvNotificationFunc)(void) = NULL;

/*Global pointer to carry the String called by ISR*/
static const u8 * USART_pu8SendData = NULL;

/*Global pointer to carry the String called by ISR*/
static  u8 * USART_pu8RecieveData = NULL;

/*Global Counter for the USART Sending String*/
static u8 USART_u8Index = 0;

/*Global Counter for the USART Sending String*/
static u8 USART_u32BufferSize = 0;

/*Global flag for the USART Busy State*/
static u8 USART_u8STATE = IDLE;

void USART_voidInit() {

    u8 LOC_UCSRC = 0;
    //    u16 LOC_BaudRate = (u16) ((SYSTEM_FREQUENCY / (16 * USART_BAUD_RATE)) - 1);
    u16 LOC_BaudRate = (u16) (SYSTEM_FREQUENCY / (USART_BAUD_RATE) / 16) - 1;



#if   USART_MODE == USART_MODE_ASYNCHRONOUS
    /*Double the USART Transmission Speed*/
#if   USART_DOUPLE_TRANSMISSION_SPEED == ENABLE
    SET_BIT(USART_UCSRA_REG, UCSRA_U2X_BIT);
    LOC_BaudRate /= 2;
#elif USART_DOUPLE_TRANSMISSION_SPEED == DISABLE
    CLEAR_BIT(USART_UCSRA_REG, UCSRA_U2X_BIT);
#else
#error"Wrong USART_STOP_BIT Config"
#endif     


#elif USART_MODE == USART_MODE_SYNCHRONOUS 
    LOC_BaudRate /= 8;

#endif    

    USART_UBRRH_REG = (u8) (LOC_BaudRate >> 8);
    USART_UBRRL_REG = (u8) LOC_BaudRate;


    /* Multi-processor Communication Mode*/
#if   USART_Multi_PROCESSOR_COMMUNICATION_MODE == ENABLE
    SET_BIT(USART_UCSRA_REG, UCSRA_MPCM_BIT);
#elif USART_Multi_PROCESSOR_COMMUNICATION_MODE == DISABLE
    CLEAR_BIT(USART_UCSRA_REG, UCSRA_MPCM_BIT);
#else
#error"Wrong USART_STOP_BIT Config"
#endif     

    /*Set USART Mode*/
#if   USART_MODE == USART_MODE_ASYNCHRONOUS
    CLEAR_BIT(LOC_UCSRC, UCSRC_UMSEL_BIT);
#elif USART_MODE == USART_MODE_SYNCHRONOUS
    SET_BIT(LOC_UCSRC, UCSRC_UMSEL_BIT);
    /* SET Clock Polarity*/
#if   USART_CLOCK_POLARITY == USART_CLOCK_POLARITY_TX_FALLING_RX_RISING
    CLEAR_BIT(LOC_UCSRC, UCSRC_UCPOL_BIT);
#elif USART_CLOCK_POLARITY == USART_CLOCK_POLARITY_TX_RISING_RX_FALLING
    SET_BIT(LOC_UCSRC, UCSRC_UCPOL_BIT);

#else
#error"Wrong USART_CLOCK_POLARITY Config"
#endif     

#else
#error"Wrong USART_MODE Config"
#endif     
    /*SET Parity Mode*/
#if   USART_PARITY_MODE == USART_PARITY_DISABLE
    CLEAR_BIT(LOC_UCSRC, UCSRC_UPM0_BIT);
    CLEAR_BIT(LOC_UCSRC, UCSRC_UPM1_BIT);
#elif USART_PARITY_MODE == USART_EVEN_PARITY
    CLEAR_BIT(LOC_UCSRC, UCSRC_UPM0_BIT);
    SET_BIT(LOC_UCSRC, UCSRC_UPM1_BIT);

#elif USART_PARITY_MODE == USART_ODD_PARITY
    SET_BIT(LOC_UCSRC, UCSRC_UPM0_BIT);
    SET_BIT(LOC_UCSRC, UCSRC_UPM1_BIT);
#else
#error"Wrong USART_PARITY Config"
#endif     
    /* Stop Bit Select*/
#if   USART_STOP_BIT_SELECT == USART_1_BIT_SELECT
    CLEAR_BIT(LOC_UCSRC, UCSRC_USBS_BIT);
#elif USART_STOP_BIT_SELECT == USART_2_BIT_SELECT
    SET_BIT(LOC_UCSRC, UCSRC_USBS_BIT);

#else
#error"Wrong USART_STOP_BIT Config"
#endif     
    /* CHARACTER SIZE Select*/
#if   USART_CHARACTER_SIZE == USART_CHARACTER_SIZE_5_BIT
    CLEAR_BIT(LOC_UCSRC, UCSRC_UCSZ0_BIT);
    CLEAR_BIT(LOC_UCSRC, UCSRC_UCSZ1_BIT);
    CLEAR_BIT(USART_UCSRB_REG, UCSRB_UCSZ2_BIT);
#elif USART_CHARACTER_SIZE == USART_CHARACTER_SIZE_6_BIT
    SET_BIT(LOC_UCSRC, UCSRC_UCSZ0_BIT);
    CLEAR_BIT(LOC_UCSRC, UCSRC_UCSZ1_BIT);
    CLEAR_BIT(USART_UCSRB_REG, UCSRB_UCSZ2_BIT);
#elif USART_CHARACTER_SIZE == USART_CHARACTER_SIZE_7_BIT
    CLEAR_BIT(LOC_UCSRC, UCSRC_UCSZ0_BIT);
    SET_BIT(LOC_UCSRC, UCSRC_UCSZ1_BIT);
    CLEAR_BIT(USART_UCSRB_REG, UCSRB_UCSZ2_BIT);
#elif USART_CHARACTER_SIZE == USART_CHARACTER_SIZE_8_BIT
    SET_BIT(LOC_UCSRC, UCSRC_UCSZ0_BIT);
    SET_BIT(LOC_UCSRC, UCSRC_UCSZ1_BIT);
    CLEAR_BIT(USART_UCSRB_REG, UCSRB_UCSZ2_BIT);
#elif USART_CHARACTER_SIZE == USART_CHARACTER_SIZE_9_BIT
    SET_BIT(LOC_UCSRC, UCSRC_UCSZ0_BIT);
    SET_BIT(LOC_UCSRC, UCSRC_UCSZ1_BIT);
    SET_BIT(USART_UCSRB_REG, UCSRB_UCSZ2_BIT);
#else
#error"Wrong USART_CHARACTER_SIZE Config"
#endif     

    /*Select Register UCSRC */
    SET_BIT(LOC_UCSRC, UCSRC_URSEL_BIT);
    USART_UCSRC_REG = LOC_UCSRC;

    /*Set interrupts*/
#if   USART_RX_COMPLETE_INTERRUPT == ENABLE
    SET_BIT(USART_UCSRB_REG, UCSRB_RXCIE_BIT);
#elif USART_RX_COMPLETE_INTERRUPT == DISABLE
    CLEAR_BIT(USART_UCSRB_REG, UCSRB_RXCIE_BIT);

#else
#error"Wrong USART_RX_COMPLETE_INTERRUPT Config"
#endif     

#if   USART_TX_COMPLETE_INTERRUPT == ENABLE
    SET_BIT(USART_UCSRB_REG, UCSRB_TXCIE_BIT);
#elif USART_TX_COMPLETE_INTERRUPT == DISABLE
    CLEAR_BIT(USART_UCSRB_REG, UCSRB_TXCIE_BIT);

#else
#error"Wrong USART_TX_COMPLETE_INTERRUPT Config"
#endif     

#if   USART_DATA_REGISTER_EMPTY_INTERRUPT == ENABLE
    SET_BIT(USART_UCSRB_REG, UCSRB_UDRIE_BIT);
#elif USART_DATA_REGISTER_EMPTY_INTERRUPT == DISABLE
    CLEAR_BIT(USART_UCSRB_REG, UCSRB_UDRIE_BIT);

#else
#error"Wrong USART_RX_COMPLETE_INTERRUPT Config"
#endif     

    /*Set interrupts*/
#if   USART_RX_ENABLE == ENABLE
    SET_BIT(USART_UCSRB_REG, UCSRB_RXEN_BIT);
#elif USART_RX_ENABLE == DISABLE
    CLEAR_BIT(USART_UCSRB_REG, UCSRB_RXEN_BIT);

#else
#error"Wrong USART_RX_ENABLE Config"
#endif     

#if   USART_TX_ENABLE == ENABLE
    SET_BIT(USART_UCSRB_REG, UCSRB_TXEN_BIT);
#elif USART_TX_ENABLE == DISABLE
    CLEAR_BIT(USART_UCSRB_REG, UCSRB_TXEN_BIT);

#else
#error"Wrong USART_RX_ENABLE Config"
#endif     

}

ErrorStatus USART_enumSendData(u8 Copy_u8Data) {
    u8 LOC_u8ErrorState = OK;
    u32 LOC_u32TimeOutCounter = 0;
    if (USART_u8STATE == IDLE) {
        USART_u8STATE = BUSY;
        /*Wait until  (UDR) is ready to receive new data*/
        while ((GET_BIT(USART_UCSRA_REG, UCSRA_UDRE_BIT) == 0) && LOC_u32TimeOutCounter < USART_TIME_OUT) {
            LOC_u32TimeOutCounter++;
        }
        if (LOC_u32TimeOutCounter == USART_TIME_OUT) {
            LOC_u8ErrorState = Time_OUT_State;
        } else {
            USART_UDR_REG = Copy_u8Data;
        }
        USART_u8STATE = IDLE;

    } else {
        LOC_u8ErrorState = Busy_State;
    }
    return LOC_u8ErrorState;
}

ErrorStatus USART_enumRecevieData(u8 * Copy_u8ReceviedData) {
    u8 LOC_ErrorState = OK;
    u32 LOC_u32TimeOutCounter = 0;
    if (Copy_u8ReceviedData != NULL) {
        if (USART_u8STATE == IDLE) {
            USART_u8STATE == BUSY;
            /*Wait until a receive complete*/
            while ((GET_BIT(USART_UCSRA_REG, UCSRA_RXC_BIT) == 0) && LOC_u32TimeOutCounter < USART_TIME_OUT) {
                LOC_u32TimeOutCounter++;
            }
            if (LOC_u32TimeOutCounter == USART_TIME_OUT) {
                LOC_ErrorState = Time_OUT_State;
            } else {
                *Copy_u8ReceviedData = USART_UDR_REG;
            }
            USART_u8STATE = IDLE;
        } else {
            LOC_ErrorState = Busy_State;
        }



    } else {
        LOC_ErrorState = NOK;
    }

    return LOC_ErrorState;
}

ErrorStatus USART_enumSendStringSync(const u8 * Copy_pu8Data) {
    u8 LOC_ErrorState = OK;
    u32 LOC_Index = 0;
    if (Copy_pu8Data != NULL) {
        while (Copy_pu8Data[LOC_Index] != '\0') {
            LOC_ErrorState = USART_enumSendData(Copy_pu8Data[LOC_Index]);
            LOC_Index++;
            if (LOC_ErrorState != OK) {
                return LOC_ErrorState;
            }
        }

    } else {
        LOC_ErrorState = NOK;
    }

    return LOC_ErrorState;
}

ErrorStatus USART_enumSendStringASync(const u8 *Copy_u8Data, void (* CopypvNotificationFunc)(void)) {
    u8 LOC_ErrorState = OK;
    if (USART_u8STATE == IDLE) {
        if ((Copy_u8Data != NULL) && (CopypvNotificationFunc != NULL)) {
            USART_u8STATE = BUSY;

            USART_pu8SendData = Copy_u8Data;
            USART_pvNotificationFunc = CopypvNotificationFunc;

            USART_UDR_REG = USART_pu8SendData[USART_u8Index];

            SET_BIT(USART_UCSRB_REG, UCSRB_TXCIE_BIT);

        } else {
            LOC_ErrorState = NOK;
        }

    } else {
        LOC_ErrorState = Busy_State;
    }
    return LOC_ErrorState;

}

ErrorStatus USART_enumRecieveBufferSync( u8 * Copy_pu8Data, u32 Copy_u32BufferSize) {
    u8 LOC_ErrorState = OK;
    u32 LOC_Index = 0;
    if (Copy_pu8Data != NULL) {
        while (LOC_Index < Copy_u32BufferSize) {
            LOC_ErrorState = USART_enumRecevieData(&Copy_pu8Data[LOC_Index]);
            LOC_Index++;
            if (LOC_ErrorState != OK) {
                return LOC_ErrorState;
            }
        }

    } else {
        LOC_ErrorState = NOK;
    }

    return LOC_ErrorState;
}

ErrorStatus USART_enumRecieveBufferASync( u8 *Copy_u8Data, void (* CopypvNotificationFunc)(void), u32 Copy_u32BufferSize) {
    u8 LOC_ErrorState = OK;
    if (USART_u8STATE == IDLE) {
        if ((Copy_u8Data != NULL) && (CopypvNotificationFunc != NULL)) {
            USART_u8STATE = BUSY;

            USART_pu8RecieveData = Copy_u8Data;
            USART_u32BufferSize = Copy_u32BufferSize;
            USART_pvNotificationFunc = CopypvNotificationFunc;


            USART_u8Index = 0;
            SET_BIT(USART_UCSRB_REG, UCSRB_RXCIE_BIT);

        } else {
            LOC_ErrorState = NOK;
        }

    } else {
        LOC_ErrorState = Busy_State;
    }
    return LOC_ErrorState;

}


void __vector_13(void) __attribute__((signal));

void __vector_13(void) {

    USART_pu8RecieveData[USART_u8Index] = USART_UDR_REG;
    USART_u8Index++;

    if (USART_u8Index == USART_u32BufferSize) {
        USART_u8Index = 0;

        USART_u8STATE = IDLE;

        USART_pvNotificationFunc();

        CLEAR_BIT(USART_UCSRB_REG, UCSRB_RXCIE_BIT);
    } else {

    }

}

void __vector_15(void) __attribute__((signal));

void __vector_15(void) {
    USART_u8Index++;

    if (USART_pu8SendData[USART_u8Index] == '\0') {
        USART_u8Index = 0;

        USART_u8STATE = IDLE;

        USART_pvNotificationFunc();

        CLEAR_BIT(USART_UCSRB_REG, UCSRB_TXCIE_BIT);
    } else {
        USART_UDR_REG = USART_pu8SendData[USART_u8Index];
    }

}