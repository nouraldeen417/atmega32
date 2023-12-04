/*
 * File:   EXTI_program.c
 * Author: nour
 *
 * Created on September 4, 2023, 10:50 PM
 */


#include <xc.h>
#include"EXTI_interface.h"




void (* EXTI_CallBack[3]) (void) = {NULL};

void EXTI_voidInit(void) {
#ifdef EXTI_LINE
#if EXTI_LINE==EXTI_INT0
#if EXTI_SENSE_MODE  ==  EXTI_LOW_LEVEL
    CLEAR_BIT(MCUCR, 0);
    CLEAR_BIT(MCUCR, 1);
#elif EXTI_SENSE_MODE == EXTI_ON_CHANGE
    SET_BIT(MCUCR, 0);
    CLEAR_BIT(MCUCR, 1);
#elif EXTI_SENSE_MODE == EXTI_FALLING_EDGE
    CLEAR_BIT(MCUCR, 0);
    SET_BIT(MCUCR, 1);
#elif EXTI_SENSE_MODE == EXTI_RISING_EDGE
    SET_BIT(MCUCR, 0);
    SET_BIT(MCUCR, 1);
#endif
#elif EXTI_LINE==EXTI_INT1
#if EXTI_SENSE_MODE  ==  EXTI_LOW_LEVEL
    CLEAR_BIT(MCUCR, 2);
    CLEAR_BIT(MCUCR, 3);
#elif EXTI_SENSE_MODE == EXTI_ON_CHANGE
    SET_BIT(MCUCR, 2);
    CLEAR_BIT(MCUCR, 3);
#elif EXTI_SENSE_MODE == EXTI_FALLING_EDGE
    CLEAR_BIT(MCUCR, 2);
    SET_BIT(MCUCR, 3);
#elif EXTI_SENSE_MODE == EXTI_RISING_EDGE
    SET_BIT(MCUCR, 2);
    SET_BIT(MCUCR, 3);
#endif      
#elif EXTI_LINE==EXTI_INT2
#if   EXTI_SENSE_MODE == EXTI_FALLING_EDGE
    CLEAR_BIT(MCUCSR, 6);
#elif EXTI_SENSE_MODE == EXTI_RISING_EDGE
    SET_BIT(MCUCSR, 6);
#endif      
#endif
#endif
}

void EXTI_voidSetSignalConf(u8 EXTI_CopySenseMode, u8 EXTI_u8CopyINT) {
    if (EXTI_u8CopyINT >= EXTI_INT0 && EXTI_u8CopyINT <= EXTI_INT1) {
        EXTI_u8CopyINT = (6 - EXTI_u8CopyINT)*-2;
        switch (EXTI_CopySenseMode) {
            case EXTI_LOW_LEVEL:
                CLEAR_BIT(MCUCR, EXTI_u8CopyINT);
                CLEAR_BIT(MCUCR, EXTI_u8CopyINT + 1);
                break;
            case EXTI_ON_CHANGE:
                SET_BIT(MCUCR, EXTI_u8CopyINT);
                CLEAR_BIT(MCUCR, EXTI_u8CopyINT + 1);
                break;
            case EXTI_FALLING_EDGE:
                CLEAR_BIT(MCUCR, EXTI_u8CopyINT);
                SET_BIT(MCUCR, EXTI_u8CopyINT + 1);
                break;
            case EXTI_RISING_EDGE:
                SET_BIT(MCUCR, EXTI_u8CopyINT);
                SET_BIT(MCUCR, EXTI_u8CopyINT + 1);
                break;
        }
    } else {
        switch (EXTI_CopySenseMode) {
            case EXTI_FALLING_EDGE:
                CLEAR_BIT(MCUCSR, 6);
                break;
            case EXTI_RISING_EDGE:
                SET_BIT(MCUCSR, 6);
                break;
        }

    }
}

EXTI_ErrorStatus EXTI_enumEnableInterrupt(u8 EXTI_u8CopyINT) {
    EXTI_ErrorStatus LOC_enumState = EXTI_OK;
    if (EXTI_u8CopyINT <= EXTI_INT1 && EXTI_u8CopyINT >= EXTI_INT2) {
        SET_BIT(GICR, EXTI_u8CopyINT);
    } else {
        LOC_enumState = EXTI_NOK;
    }

    return LOC_enumState;
}

EXTI_ErrorStatus EXTI_enumDisableInterrupt(u8 EXTI_u8CopyINT) {
    EXTI_ErrorStatus LOC_enumState = EXTI_OK;
    if (EXTI_u8CopyINT <= EXTI_INT1 && EXTI_u8CopyINT >= EXTI_INT2) {
        CLEAR_BIT(GICR, EXTI_u8CopyINT);
    } else {
        LOC_enumState = EXTI_NOK;
    }

    return LOC_enumState;
}

void EXTI_voidSetCallBack(void (* EXTI_ptrvoidCopyCallBack) (void), u8 EXTI_u8CopyINT) { //5 INT_2  6 INT_0  7 INT_1
    if (EXTI_ptrvoidCopyCallBack != NULL) {
        switch (EXTI_u8CopyINT) {
            case EXTI_INT0:
                EXTI_CallBack[0] = EXTI_ptrvoidCopyCallBack;
                break;
            case EXTI_INT1:
                EXTI_CallBack[1] = EXTI_ptrvoidCopyCallBack;
                break;
            case EXTI_INT2:
                EXTI_CallBack[2] = EXTI_ptrvoidCopyCallBack;
                break;
        }


    }
}

EXTI_ErrorStatus EXTI_enumClearFlag(u8 EXTI_u8CopyINT) {
    EXTI_ErrorStatus LOC_enumState = EXTI_OK;
    if (EXTI_u8CopyINT <= EXTI_INT1 && EXTI_u8CopyINT >= EXTI_INT2) {
        SET_BIT(GIFR, EXTI_u8CopyINT);
    } else {
        LOC_enumState = EXTI_NOK;
    }

    return LOC_enumState;
}

u8 EXTI_u8GetFlag(u8 EXTI_u8CopyINT) {
    return GET_BIT(GIFR, EXTI_u8CopyINT);
}

void __vector_1(void)__attribute__((signal));

void __vector_1(void) {
    if (EXTI_CallBack[0] != NULL) {

        EXTI_CallBack[0]();
        EXTI_enumClearFlag(EXTI_INT0);
    }

}

void __vector_2(void) __attribute__((signal));

void __vector_2(void) {
    if (EXTI_CallBack[1] != NULL) {

        EXTI_CallBack[1]();
        EXTI_enumClearFlag(EXTI_INT1);
    }
}

void __vector_3(void) __attribute__((signal));

void __vector_3(void) {
    if (EXTI_CallBack[2] != NULL) {

        EXTI_CallBack[2]();
        EXTI_enumClearFlag(EXTI_INT2);
    }
}