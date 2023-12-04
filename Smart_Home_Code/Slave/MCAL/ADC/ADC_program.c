/*
 * File:   ADC_program.c
 * Author: nour
 *
 * Created on September 8, 2023, 4:44 PM
 */


#include"ADC_interface.h"
#include"ADC_config.h"

/*Global pointer to carry the conversion result in the Asynchronous execution*/
static u16 * ADC_pu16AsynchConversionResult = NULL;
static u8 * ADC_pu8ChainChannel = NULL;

/*Global pointer to function to carry the notification function called by ISR*/
static void (* ADC_pvNotificationFunc)(void) = NULL;

static u8 ADC_u8State = IDLE;
static u8 ADC_u8Index=0;
static u8 ADC_CHANNEL_STATE;
static u8 ADC_u8ChainSize;

void ADC_voidInit() {

    /*Set Voltage Reference*/
    ADMUX_REG &= ADC_REF_MASK;
    ADMUX_REG |= (ADC_REFERENCE << ADMUX_REF_SHIFT_BITS);

    /*Set Adjustment*/
#if ADC_ADJUST==ADC_LEFT_ADJUST
    SET_BIT(ADMUX_REG, ADMUX_ADLAR_BIT);
#elif ADC_ADJUST==ADC_RIGHT_ADJUST
    CLEAR_BIT(ADMUX_REG, ADMUX_ADLAR_BIT);
#else
#error "Wrong ADC_ADJUST config"
#endif

    /*ADC Enable*/
#if ADC_STATUS==ADC_ENABLE
    SET_BIT(ADCSRA_REG, ADCSRA_ADEN_BIT);
#elif ADC_STATUS==ADC_DISABLE
    CLEAR_BIT(ADCSRA_REG, ADCSRA_ADEN_BIT);
#else
#error "Wrong ADC_ADJUST config"
#endif
    /*ADC Enable Interrupt*/
#if ADC_INTERRUPT==ADC_INTERRUPT_ENABLE
    SET_BIT(ADCSRA_REG, ADCSRA_ADEIE_BIT);
#elif ADC_INTERRUPT==ADC_INTERRUPT_DISABLE
    CLEAR_BIT(ADCSRA_REG, ADCSRA_ADEIE_BIT);
#else
#error "Wrong ADC_Interrupt config"
#endif



    /*Set Mode*/
#if ADC_MODE==ADC_FREE_RUNNING
    SET_BIT(ADCSRA_REG, ADCSRA_ADATE_BIT);
#elif ADC_MODE==ADC_SINGLE_CONVERSION
    CLEAR_BIT(ADCSRA_REG, ADCSRA_ADATE_BIT);
#else
#error  "Wrong ADC_MODE config"
#endif

    /*ADC Prescaler*/
    ADCSRA_REG &= ADC_PRE_MASK;
    ADCSRA_REG |= ADC_PRESCALER;



}

ADC_ErrorStatus ADC_enumGetResultSync(u8 Copy_u8Channel, u16 * Copy_u16Result) {

    ADC_ErrorStatus LOC_enumErrorState = ADC_OK;
    u32 Local_u32TimeoutCounter = 0;
    if (Copy_u16Result != NULL) {
        if (ADC_u8State == IDLE) {
            ADC_u8State == BUSY;

            /*Set  Channel*/
            ADMUX_REG &= ADC_CH_MASK;
            ADMUX_REG |= Copy_u8Channel;

            /*ADC Start Conversion*/
            SET_BIT(ADCSRA_REG, ADCSRA_ADSC_BIT);
            while (GET_BIT(ADCSRA_REG, ADCSRA_ADEIF_BIT) == 0 && Local_u32TimeoutCounter < ADC_TIMEOUT) {
                Local_u32TimeoutCounter++;
            }
            if (Local_u32TimeoutCounter == ADC_TIMEOUT) {
                LOC_enumErrorState = TIMEOUT_STATE;
            } else {

                SET_BIT(ADCSRA_REG, ADCSRA_ADEIF_BIT);
#if   ADC_ADJUST==ADC_LEFT_ADJUST
                *Copy_u16Result = ADCH_REG;
#elif ADC_ADJUST==ADC_RIGHT_ADJUST
                *Copy_u16Result = (ADCL_REG | (ADCH_REG << 8));
#else
#error "Wrong ADC_ADJUST config"
#endif                

            }
            ADC_u8State = IDLE;


        } else {
            LOC_enumErrorState = BUSY_STATE;
        }
    } else {
        LOC_enumErrorState = ADC_NOK;

    }
    return LOC_enumErrorState;

}

ADC_ErrorStatus ADC_enumStartConversionAsync(u8 Copy_u8Channel, void (* Copy_pvNotificationFunc)(void), u16 * Copy_pu16Result) {
    ADC_ErrorStatus LOC_enumErrorState = ADC_OK;
    if (Copy_pu16Result != NULL && Copy_pvNotificationFunc != NULL) {
        if (ADC_u8State == IDLE) {
            ADC_u8State == BUSY;
            ADC_CHANNEL_STATE = ADC_SINGLE_CHANNEL;
            /*Set  Channel*/
            ADMUX_REG &= ADC_CH_MASK;
            ADMUX_REG |= Copy_u8Channel;

            ADC_pvNotificationFunc = Copy_pvNotificationFunc;
            ADC_pu16AsynchConversionResult = Copy_pu16Result;
            /*ADC Start Conversion*/
            SET_BIT(ADCSRA_REG, ADCSRA_ADSC_BIT);
            /*Enable Interrupt*/
            SET_BIT(ADCSRA_REG, ADCSRA_ADEIE_BIT);

        } else {
            LOC_enumErrorState = BUSY_STATE;

        }

    } else {
        LOC_enumErrorState = ADC_NOK;

    }

    return LOC_enumErrorState;

}

ADC_ErrorStatus ADC_enumStartChainAsync(Chain_Type * Copy_Chain) {
    ADC_ErrorStatus LOC_enumErrorState = ADC_OK;
    if (Copy_Chain->Chanel != NULL
            && Copy_Chain->NotificationFunc != NULL
            && Copy_Chain->Result != NULL
            && Copy_Chain->size != NULL) {
        if (ADC_u8State == IDLE) {
            ADC_CHANNEL_STATE = ADC_CHAIN_CHANNEL;
            ADC_u8State = BUSY;
            ADC_u8Index = 0;

            /*Set Global data*/
            ADC_u8ChainSize = Copy_Chain->size;
            ADC_pu16AsynchConversionResult = Copy_Chain->Result;
            ADC_pvNotificationFunc = Copy_Chain->NotificationFunc;
            ADC_pu8ChainChannel = Copy_Chain->Chanel;
            /*Set  Channel*/
            ADMUX_REG &= ADC_CH_MASK;
            ADMUX_REG |= ADC_pu8ChainChannel[ ADC_u8Index];
            /*ADC Start Conversion*/
            SET_BIT(ADCSRA_REG, ADCSRA_ADSC_BIT);
            /*Enable Interrupt*/
            SET_BIT(ADCSRA_REG, ADCSRA_ADEIE_BIT);

        } else {
            LOC_enumErrorState = BUSY_STATE;

        }

    } else {
        LOC_enumErrorState = ADC_NOK;

    }


    return LOC_enumErrorState;



}

void __vector_16(void) __attribute__((signal));

void __vector_16(void) {
    if (ADC_CHANNEL_STATE == ADC_SINGLE_CHANNEL) {
#if   ADC_ADJUST==ADC_LEFT_ADJUST
        *ADC_pu16AsynchConversionResult = ADCH_REG;
#elif ADC_ADJUST==ADC_RIGHT_ADJUST
        *ADC_pu16AsynchConversionResult = (ADCL_REG | (ADCH_REG << 8));
#else
#error "Wrong ADC_ADJUST config"
#endif                
        ADC_u8State = IDLE;
        ADC_pvNotificationFunc();
        CLEAR_BIT(ADCSRA_REG, ADCSRA_ADEIE_BIT);

    } else {
#if   ADC_ADJUST==ADC_LEFT_ADJUST
        *ADC_pu16AsynchConversionResult = ADCH_REG;
#elif ADC_ADJUST==ADC_RIGHT_ADJUST
        *ADC_pu16AsynchConversionResult = (ADCL_REG | (ADCH_REG << 8));
#else
#error "Wrong ADC_ADJUST config"
#endif                

        ADC_u8Index++;
        if (ADC_u8Index == ADC_u8ChainSize+1) {
            ADC_u8State = IDLE;
            ADC_pvNotificationFunc();
            CLEAR_BIT(ADCSRA_REG, ADCSRA_ADEIE_BIT);

        } else {
            /*Set  Channel*/
            ADMUX_REG &= ADC_CH_MASK;
            ADMUX_REG |= ADC_pu8ChainChannel[ ADC_u8Index];//1 2
            /*ADC Start Conversion*/
            SET_BIT(ADCSRA_REG, ADCSRA_ADSC_BIT);

        }
    }

}