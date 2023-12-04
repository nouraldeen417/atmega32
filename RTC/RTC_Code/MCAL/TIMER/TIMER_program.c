/*
 * File:   TIMER_program.c
 * Author: nour
 *
 * Created on September 13, 2023, 3:42 PM
 */
#include <math.h>

#include "TIMER_interface.h"
#include"TIMER_config.h"


/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
//counter for handler
static u8 ICU_u8State = IDLE;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************TIMER_0*******************************************************************/
void TIMER0_voidInit() {
    /*SET TIMER0 MODE */

#if   TIMER0_MODE==TIMER_OVERFLOW_MODE
    CLEAR_BIT(TIMER0_TCCR_REG, TCCR0_WGM00_BIT);
    CLEAR_BIT(TIMER0_TCCR_REG, TCCR0_WGM01_BIT);
    /*SET TIMER0 INTERRUPT */

#if   TIMER0_INTERRUPT==TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_TOIE0_BIT);
#elif TIMER0_INTERRUPT==TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_TOIE0_BIT);
#else
#error
    "Wrong TIMER0_INTERRUPT Config"
#endif

    /*SET PRELOAD*/
    TIMER0_TCNT_REG = TIMER0_PRELOAD_VAL;


#elif TIMER0_MODE==TIMER_CTC_MODE
    CLEAR_BIT(TIMER0_TCCR_REG, TCCR0_WGM00_BIT);
    SET_BIT(TIMER0_TCCR_REG, TCCR0_WGM01_BIT);
#if   TIMER0_INTERRUPT==TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_OCIE0_BIT);
#elif TIMER0_INTERRUPT==TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_OCIE0_BIT);
#else
#error
    "Wrong TIMER0_INTERRUPT Config"
#endif
#if   TIMER0_CTC_MODE== TIMER_OC_DISCONNECTED
    CLEAR_BIT(TIMER0_TCCR_REG, TCCR0_COM00_BIT);
    CLEAR_BIT(TIMER0_TCCR_REG, TCCR0_COM01_BIT);
#elif TIMER0_CTC_MODE== TIMER_OC_TOGGEL
    SET_BIT(TIMER0_TCCR_REG, TCCR0_COM00_BIT);
    CLEAR_BIT(TIMER0_TCCR_REG, TCCR0_COM01_BIT);
#elif TIMER0_CTC_MODE== TIMER_OC_LOW
    CLEAR_BIT(TIMER0_TCCR_REG, TCCR0_COM00_BIT);
    SET_BIT(TIMER0_TCCR_REG, TCCR0_COM01_BIT);
#elif TIMER0_CTC_MODE== TIMER_OC_HIGH
    SET_BIT(TIMER0_TCCR_REG, TCCR0_COM00_BIT);
    SET_BIT(TIMER0_TCCR_REG, TCCR0_COM01_BIT);
#else
#error
    "Wrong TIMER0_MODE Config"
#endif

    /*SET PRELOAD*/
    TIMER0_OCR_REG = TIMER0_CTC_VAL;



#elif TIMER0_MODE==TIMER_PWM_MODE
    SET_BIT(TIMER0_TCCR_REG, TCCR0_WGM00_BIT);
    CLEAR_BIT(TIMER0_TCCR_REG, TCCR0_WGM01_BIT);
#if TIMER0_CTC_PWM_MODE== TIMER_OC_DISCONNECTED
    CLEAR_BIT(TIMER0_TCCR_REG, TCCR0_COM00_BIT);
    CLEAR_BIT(TIMER0_TCCR_REG, TCCR0_COM01_BIT);
#elif TIMER0_CTC_PWM_MODE== TIMER_CLR_ON_CTC_SET_ON_TOP
    CLEAR_BIT(TIMER0_TCCR_REG, TCCR0_COM00_BIT);
    SET_BIT(TIMER0_TCCR_REG, TCCR0_COM01_BIT);
#elif TIMER0_CTC_PWM_MODE== TIMER_SET_ON_CTC_CLR_ON_TOP
    SET_BIT(TIMER0_TCCR_REG, TCCR0_COM00_BIT);
    SET_BIT(TIMER0_TCCR_REG, TCCR0_COM01_BIT);
#else
#error
    "Wrong TIMER0_MODE Config"
#endif
    /*   SET PRELOAD   */
    TIMER0_OCR_REG = TIMER0_CTC_VAL;

#elif TIMER0_MODE==TIMER_FASTPWM_MODE
    SET_BIT(TIMER0_TCCR_REG, TCCR0_WGM00_BIT);
    SET_BIT(TIMER0_TCCR_REG, TCCR0_WGM01_BIT);
#if TIMER0_CTC_PWM_MODE== TIMER_OC_DISCONNECTED
    CLEAR_BIT(TIMER0_TCCR_REG, TCCR0_COM00_BIT);
    CLEAR_BIT(TIMER0_TCCR_REG, TCCR0_COM01_BIT);
#elif TIMER0_CTC_PWM_MODE== TIMER_CLR_ON_CTC_SET_ON_TOP
    CLEAR_BIT(TIMER0_TCCR_REG, TCCR0_COM00_BIT);
    SET_BIT(TIMER0_TCCR_REG, TCCR0_COM01_BIT);
#elif TIMER0_CTC_PWM_MODE== TIMER_SET_ON_CTC_CLR_ON_TOP
    SET_BIT(TIMER0_TCCR_REG, TCCR0_COM00_BIT);
    SET_BIT(TIMER0_TCCR_REG, TCCR0_COM01_BIT);
#else
#error
    "Wrong TIMER0_MODE Config"
#endif
    /*   SET PRELOAD   */
    TIMER0_OCR_REG = TIMER0_CTC_VAL;



#else
#error
    "Wrong TIMER0_MODE Config"
#endif

    /*SET TIMER0 CLOCK SOURCE*/
    TIMER0_TCCR_REG &= TCCR_PRE_MASK;
    TIMER0_TCCR_REG |= TIMER0_CLOCK;
}

void TIMER0_voidSetPreload(u8 Copy_u8Preload) {
    /*SET PRELOAD*/
    TIMER0_TCNT_REG = Copy_u8Preload;
}

void TIMER0_voidSetCTC(u8 Copy_u8Preload) {
    /*SET PRELOAD*/
    TIMER0_OCR_REG = Copy_u8Preload;

}

void TIMER0_voidDisable() {
    TIMER0_TCCR_REG &= TCCR_PRE_MASK;
    TIMER0_TCCR_REG |= 0;

}

ErrorStatus TIMER0_enumGetTimerCounterValue(u8 *Copy_pu8Value) {
    ErrorStatus LOC_ErrorStare = OK;
    if (Copy_pu8Value != NULL) {
        *Copy_pu8Value = TIMER0_TCNT_REG;
    } else {
        LOC_ErrorStare = NOK;
    }
    return LOC_ErrorStare;

}

/**********************************************TIMER_1*******************************************************************/
void TIMER1_voidInit() {
    /*SET TIMER0 MODE */

#if   TIMER1_MODE==TIMER_OVERFLOW_MODE
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);

    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM12_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);

    /*SET PRELOAD*/
    TIMER1_TCNT1_REG = TIMER1_PRELOAD_VAL;
    // TIMER1_TCNT1_REG = 0XF0F1;
    //  TIMER1_TCNTL_REG = 0XFF;
    /*SET TIMER1 INTERRUPT */
#if   TIMER1_OVF_INTERRUPT == TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_TOIE1_BIT);
#elif TIMER1_OVF_INTERRUPT==TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_TOIE1_BIT);
#else
#error
    "Wrong TIMER1_INTERRUPT Config"
#endif




#elif (TIMER1_MODE==TIMER1_CTC_OCR1A_MODE) || (TIMER1_MODE==TIMER1_CTC_ICR1_MODE)

    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);
#if   TIMER1_MODE==TIMER1_CTC_OCR1A_MODE
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM12_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);
#elif TIMER1_MODE==TIMER1_CTC_ICR1_MODE
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM12_BIT);
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);
#else 
#error
    "Wrong TIMER1_MODE Config"
#endif


#if   TIMER1_CTCA_MODE== TIMER_OC_DISCONNECTED
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A0_BIT);
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A1_BIT);

#elif TIMER1_CTCA_MODE== TIMER_OC_TOGGEL
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A0_BIT);
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A1_BIT);
#elif TIMER1_CTCA_MODE== TIMER_OC_LOW
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A0_BIT);
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A1_BIT);
#elif TIMER1_CTCA_MODE== TIMER_OC_HIGH
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A0_BIT);
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A1_BIT);
#else
#error
    "Wrong TIMER1_OC Config"
#endif

#if   TIMER1_CTCB_MODE== TIMER_OC_DISCONNECTED
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B0_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B1_BIT);

#elif TIMER1_CTCB_MODE== TIMER_OC_TOGGEL
    SET_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B0_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B1_BIT);
#elif TIMER1_CTCB_MODE== TIMER_OC_LOW
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B0_BIT);
    SET_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B1_BIT);
#elif TIMER1_CTCB_MODE== TIMER_OC_HIGH
    SET_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B0_BIT);
    SET_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B1_BIT);
#else
#error
    "Wrong TIMER1_OC Config"
#endif

    /*SET OCR VAL*/
    TIMER1_OCRA1_REG = TIMER1_CTCA_VAL;
    TIMER1_OCRB1_REG = TIMER1_CTCB_VAL;

    /*Set ICR1 if TIMER1_CTC_OCR1A_MODE = TIMER1_CTC_ICR1_MODE*/
#if  TIMER1_MODE == TIMER1_CTC_ICR1_MODE
    TIMER1_ICR1_REG = TIMER1_ICU_VAL;
    /*ICU_NOISE_CANCELER*/
#if ICU_NOISE_CANCELER == ICU_NOISE_CANCELER_EN
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_ICNC1_BIT);

#else
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_ICNC1_BIT);

#endif    
    /*Set STATE*/
#if TIMER_ICU_STATE == TIMER_ICU_STATE_RAISING
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_ICES1_BIT);
#elif     TIMER_ICU_STATE == TIMER_ICU_STATE_FALLING
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_ICES1_BIT);
#else
#error
    "Wrong TIMER_ICU_STATE Config"
#endif  
#endif            

#if   TIMER1_CTCA_INTERRUPT==TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_OCIE1A_BIT);
#elif TIMER1_CTCA_INTERRUPT==TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_OCIE1A_BIT);
#else
#error
    "Wrong TIMER1_INTERRUPT Config"
#endif

#if   TIMER1_CTCB_INTERRUPT==TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_OCIE1B_BIT);
#elif TIMER1_CTCB_INTERRUPT==TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_OCIE1B_BIT);
#else
#error
    "Wrong TIMER1_INTERRUPT Config"
#endif


#elif (TIMER1_MODE==TIMER1_PWM_8_BIT_MODE) || (TIMER1_MODE==TIMER1_PWM_9_BIT_MODE) || (TIMER1_MODE==TIMER1_PWM_10_BIT_MODE) || (TIMER1_MODE==TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1_MODE) || (TIMER1_MODE==TIMER1_PWM_PHASE_FREQ_CORRECT_OCR1A_MODE) || (TIMER1_MODE==TIMER1_PWM_PHASE_CORRECT_ICR1_MODE) || (TIMER1_MODE==TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE) 
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM12_BIT);
#if    TIMER1_MODE==TIMER1_PWM_8_BIT_MODE
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);
#elif  TIMER1_MODE==TIMER1_PWM_9_BIT_MODE
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);
#elif  TIMER1_MODE==TIMER1_PWM_10_BIT_MODE
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);
#elif  TIMER1_MODE==TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1_MODE
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);
#elif  TIMER1_MODE==TIMER1_PWM_PHASE_FREQ_CORRECT_OCR1A_MODE
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);
#elif  TIMER1_MODE==TIMER1_PWM_PHASE_CORRECT_ICR1_MODE
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);
#elif  TIMER1_MODE==TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);
#else
#error  "Wrong TIMER1_MODE Config"
#endif

#if   TIMER1_CTCA_MODE== TIMER_OC_DISCONNECTED
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A0_BIT);
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A1_BIT);

#elif TIMER1_CTCA_MODE== TIMER_OC_TOGGEL
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A0_BIT);
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A1_BIT);
#elif TIMER1_CTCA_MODE== TIMER_CLR_ON_CTC_SET_ON_TOP
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A0_BIT);
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A1_BIT);
#elif TIMER1_CTCA_MODE== TIMER_SET_ON_CTC_CLR_ON_TOP
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A0_BIT);
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A1_BIT);
#else
#error
    "Wrong TIMER1_OC Config"
#endif

#if   TIMER1_CTCB_MODE== TIMER_OC_DISCONNECTED
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B0_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B1_BIT);

#elif TIMER1_CTCB_MODE== TIMER_OC_TOGGEL
    SET_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B0_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B1_BIT);
#elif TIMER1_CTCB_MODE== TIMER_CLR_ON_CTC_SET_ON_TOP
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B0_BIT);
    SET_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B1_BIT);
#elif TIMER1_CTCB_MODE== TIMER_SET_ON_CTC_CLR_ON_TOP
    SET_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B0_BIT);
    SET_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B1_BIT);
#else
#error
    "Wrong TIMER1_OC Config"
#endif

    /*SET OCR VAL*/
    TIMER1_OCRA1_REG = TIMER1_CTCA_VAL;
    TIMER1_OCRB1_REG = TIMER1_CTCB_VAL;

    /*Set ICR1 if TIMER1_CTC_OCR1A_MODE = TIMER1_CTC_ICR1_MODE*/
#if   ((TIMER1_MODE==TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1_MODE) || (TIMER1_MODE==TIMER1_PWM_PHASE_CORRECT_ICR1_MODE))
    TIMER1_ICR1_REG = TIMER1_ICU_VAL;
    /*ICU_NOISE_CANCELER*/
#if ICU_NOISE_CANCELER == ICU_NOISE_CANCELER_EN
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_ICNC1_BIT);

#else
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_ICNC1_BIT);

#endif    
    /*Set STATE*/
#if TIMER_ICU_STATE == TIMER_ICU_STATE_RAISING
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_ICES1_BIT);
#elif     TIMER_ICU_STATE == TIMER_ICU_STATE_FALLING
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_ICES1_BIT);
#else
#error
    "Wrong TIMER_ICU_STATE Config"
#endif  
#endif            
    /*SET_OVERFLOW_INTERRUPT*/
#if   TIMER1_OVF_INTERRUPT == TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_TOIE1_BIT);
#elif TIMER1_OVF_INTERRUPT==TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_TOIE1_BIT);
#else
#error
    "Wrong TIMER1_INTERRUPT Config"
#endif
    /*SET_CTCA_INTERRUPT*/
#if   TIMER1_CTCA_INTERRUPT==TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_OCIE1A_BIT);
#elif TIMER1_CTCA_INTERRUPT==TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_OCIE1A_BIT);
#else
#error
    "Wrong TIMER1_INTERRUPT Config"
#endif            
    /*SET_CTCB_INTERRUPT*/
#if   TIMER1_CTCB_INTERRUPT==TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_OCIE1B_BIT);
#elif TIMER1_CTCB_INTERRUPT==TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_OCIE1B_BIT);
#else
#error
    "Wrong TIMER1_INTERRUPT Config"
#endif
    /*SET_ICU_INTERRUPT*/
#if   TIMER1_ICU_INTERRUPT==TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_TICIE1_BIT);
#elif TIMER1_ICU_INTERRUPT==TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_TICIE1_BIT);
#else
#error
    "Wrong TIMER1_INTERRUPT Config"
#endif


#elif (TIMER1_MODE==TIMER1_FAST_PWM_8_BIT_MODE) || (TIMER1_MODE==TIMER1_FAST_PWM_9_BIT_MODE) || (TIMER1_MODE==TIMER1_FAST_PWM_10_BIT_MODE) || (TIMER1_MODE==TIMER1_FAST_PWM_ICR1_MODE) || (TIMER1_MODE==TIMER1_FAST_PWM_OCR1A_MODE)
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM12_BIT);
#if   (TIMER1_MODE==TIMER1_FAST_PWM_8_BIT_MODE) 
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);
#elif (TIMER1_MODE==TIMER1_FAST_PWM_9_BIT_MODE) 
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);
#elif (TIMER1_MODE==TIMER1_FAST_PWM_10_BIT_MODE) 
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);

#elif (TIMER1_MODE==TIMER1_FAST_PWM_ICR1_MODE) 
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);

#elif (TIMER1_MODE==TIMER1_FAST_PWM_OCR1A_MODE) 
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);
#else
#error
    "Wrong TIMER0_MODE Config"
#endif
#if   TIMER1_CTCA_MODE== TIMER_OC_DISCONNECTED
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A0_BIT);
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A1_BIT);

#elif TIMER1_CTCA_MODE== TIMER_OC_TOGGEL
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A0_BIT);
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A1_BIT);
#elif TIMER1_CTCA_MODE== TIMER_CLR_ON_CTC_SET_ON_TOP
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A0_BIT);
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A1_BIT);
#elif TIMER1_CTCA_MODE== TIMER_SET_ON_CTC_CLR_ON_TOP
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A0_BIT);
    SET_BIT(TIMER1_TCCRA_REG, TCCR1A_COM1A1_BIT);
#else
#error
    "Wrong TIMER1_OC Config"
#endif

#if   TIMER1_CTCB_MODE== TIMER_OC_DISCONNECTED
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B0_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B1_BIT);

#elif TIMER1_CTCB_MODE== TIMER_OC_TOGGEL
    SET_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B0_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B1_BIT);
#elif TIMER1_CTCB_MODE== TIMER_CLR_ON_CTC_SET_ON_TOP
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B0_BIT);
    SET_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B1_BIT);
#elif TIMER1_CTCB_MODE== TIMER_SET_ON_CTC_CLR_ON_TOP
    SET_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B0_BIT);
    SET_BIT(TIMER1_TCCRB_REG, TCCR1A_COM1B1_BIT);
#else
#error
    "Wrong TIMER1_OC Config"
#endif

    /*SET OCR VAL*/
    TIMER1_OCRA1_REG = TIMER1_CTCA_VAL;
    TIMER1_OCRB1_REG = TIMER1_CTCB_VAL;

    /*Set ICR1 if TIMER1_CTC_OCR1A_MODE = TIMER1_CTC_ICR1_MODE*/
#if   (TIMER1_MODE==TIMER1_FAST_PWM_ICR1_MODE) 
    TIMER1_ICR1_REG = TIMER1_ICU_VAL;
    /*ICU_NOISE_CANCELER*/
#if ICU_NOISE_CANCELER == ICU_NOISE_CANCELER_EN
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_ICNC1_BIT);

#else
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_ICNC1_BIT);

#endif    
    /*Set STATE*/
#if TIMER_ICU_STATE == TIMER_ICU_STATE_RAISING
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_ICES1_BIT);
#elif     TIMER_ICU_STATE == TIMER_ICU_STATE_FALLING
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_ICES1_BIT);
#else
#error
    "Wrong TIMER_ICU_STATE Config"
#endif  
#endif            
    /*SET_OVERFLOW_INTERRUPT*/
#if   TIMER1_OVF_INTERRUPT == TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_TOIE1_BIT);
#elif TIMER1_OVF_INTERRUPT==TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_TOIE1_BIT);
#else
#error
    "Wrong TIMER1_INTERRUPT Config"
#endif
    /*SET_CTCA_INTERRUPT*/
#if   TIMER1_CTCA_INTERRUPT==TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_OCIE1A_BIT);
#elif TIMER1_CTCA_INTERRUPT==TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_OCIE1A_BIT);
#else
#error
    "Wrong TIMER1_INTERRUPT Config"
#endif            
    /*SET_CTCB_INTERRUPT*/
#if   TIMER1_CTCB_INTERRUPT==TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_OCIE1B_BIT);
#elif TIMER1_CTCB_INTERRUPT==TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_OCIE1B_BIT);
#else
#error
    "Wrong TIMER1_INTERRUPT Config"
#endif
    /*SET_ICU_INTERRUPT*/
#if   TIMER1_ICU_INTERRUPT==TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_TICIE1_BIT);
#elif TIMER1_ICU_INTERRUPT==TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_TICIE1_BIT);
#else
#error
    "Wrong TIMER1_INTERRUPT Config"
#endif



#else
#error
    "Wrong TIMER1_OC Config"
#endif


    /*SET TIMER0 CLOCK SOURCE*/
    TIMER1_TCCRB_REG &= TCCR_PRE_MASK;
    TIMER1_TCCRB_REG |= TIMER1_CLOCK;
}

void TIMER1_voidSetPreload(u16 Copy_u16Preload) {
    /*SET PRELOAD*/
    TIMER1_TCNT1_REG = Copy_u16Preload;
}

void TIMER1_voidSetCTCA(u16 Copy_u16Preload) {
    /*SET PRELOAD*/
    TIMER1_OCRA1_REG = Copy_u16Preload;

}

void TIMER1_voidSetCTCB(u16 Copy_u16Preload) {
    /*SET PRELOAD*/
    TIMER1_OCRB1_REG = Copy_u16Preload;

}

void TIMER1_voidDisable() {
    TIMER1_TCCRB_REG &= TCCR_PRE_MASK;
    TIMER1_TCCRB_REG |= 0;

}

ErrorStatus TIMER1_enumGetTimerCounterValue(u16 *Copy_pu16Value) {
    ErrorStatus LOC_ErrorStare = OK;
    if (Copy_pu16Value != NULL) {
        *Copy_pu16Value = TIMER1_TCNT1_REG;
    } else {
        LOC_ErrorStare = NOK;
    }
    return LOC_ErrorStare;

}

/**********************************************TIMER_2*******************************************************************/
void TIMER2_voidInit() {
    /*SET TIMER0 MODE */

#if  TIMER2_MODE == TIMER_OVERFLOW_MODE
    CLEAR_BIT(TIMER2_TCCR_REG, TCCR2_WGM00_BIT);
    CLEAR_BIT(TIMER2_TCCR_REG, TCCR2_WGM01_BIT);
    /*SET TIMER0 INTERRUPT */

#if   TIMER2_INTERRUPT==TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_TOIE2_BIT);
#elif TIMER2_INTERRUPT==TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_TOIE2_BIT);
#else
#error
    "Wrong TIMER0_INTERRUPT Config"
#endif
    /*SET PRELOAD*/
    TIMER2_TCNT_REG = TIMER2_PRELOAD_VAL;


#elif TIMER2_MODE == TIMER_CTC_MODE
    CLEAR_BIT(TIMER2_TCCR_REG, TCCR2_WGM00_BIT);
    SET_BIT(TIMER2_TCCR_REG, TCCR2_WGM01_BIT);
#if   TIMER2_INTERRUPT == TIMER_INTERRUPT_EN
    SET_BIT(TIMSK_REG, TIMSK_OCIE2_BIT);
#elif TIMER2_INTERRUPT == TIMER_INTERRUPT_DIS
    CLEAR_BIT(TIMSK_REG, TIMSK_OCIE2_BIT);
#else
#error
    "Wrong TIMER2_INTERRUPT Config"
#endif
#if TIMER2_CTC_MODE == TIMER_OC_DISCONNECTED
    CLEAR_BIT(TIMER2_TCCR_REG, TCCR2_COM00_BIT);
    CLEAR_BIT(TIMER2_TCCR_REG, TCCR2_COM01_BIT);
#elif TIMER2_CTC_MODE == TIMER_OC_TOGGEL
    SET_BIT(TIMER2_TCCR_REG, TCCR2_COM00_BIT);
    CLEAR_BIT(TIMER2_TCCR_REG, TCCR2_COM01_BIT);
#elif TIMER2_CTC_MODE == TIMER_OC_LOW
    CLEAR_BIT(TIMER2_TCCR_REG, TCCR2_COM00_BIT);
    SET_BIT(TIMER2_TCCR_REG, TCCR2_COM01_BIT);
#elif TIMER2_CTC_MODE == TIMER_OC_HIGH
    SET_BIT(TIMER2_TCCR_REG, TCCR2_COM00_BIT);
    SET_BIT(TIMER2_TCCR_REG, TCCR2_COM01_BIT);
#else
#error
    "Wrong TIMER2_MODE Config"
#endif


    /*SET PRELOAD*/
    TIMER2_OCR_REG = TIMER2_CTC_VAL;



#elif TIMER2_MODE==TIMER_PWM_MODE
    SET_BIT(TIMER2_TCCR_REG, TCCR2_WGM00_BIT);
    CLEAR_BIT(TIMER2_TCCR_REG, TCCR2_WGM01_BIT);
#if TIMER2_CTC_PWM_MODE== TIMER_OC_DISCONNECTED
    CLEAR_BIT(TIMER2_TCCR_REG, TCCR2_COM00_BIT);
    CLEAR_BIT(TIMER2_TCCR_REG, TCCR2_COM01_BIT);
#elif TIMER2_CTC_PWM_MODE== TIMER_CLR_ON_CTC_SET_ON_TOP
    CLEAR_BIT(TIMER2_TCCR_REG, TCCR2_COM00_BIT);
    SET_BIT(TIMER2_TCCR_REG, TCCR2_COM01_BIT);
#elif TIMER2_CTC_PWM_MODE== TIMER_SET_ON_CTC_CLR_ON_TOP
    SET_BIT(TIMER2_TCCR_REG, TCCR2_COM00_BIT);
    SET_BIT(TIMER2_TCCR_REG, TCCR2_COM01_BIT);
#else
#error
    "Wrong TIMER2_MODE Config"
#endif
    /*   SET PRELOAD   */
    TIMER2_OCR_REG = TIMER2_CTC_VAL;

#elif TIMER2_MODE==TIMER_FASTPWM_MODE
    SET_BIT(TIMER2_TCCR_REG, TCCR2_WGM00_BIT);
    SET_BIT(TIMER2_TCCR_REG, TCCR2_WGM01_BIT);

#if TIMER2_CTC_PWM_MODE== TIMER_OC_DISCONNECTED
    CLEAR_BIT(TIMER2_TCCR_REG, TCCR2_COM00_BIT);
    CLEAR_BIT(TIMER2_TCCR_REG, TCCR2_COM01_BIT);
#elif TIMER2_CTC_PWM_MODE== TIMER_CLR_ON_CTC_SET_ON_TOP
    CLEAR_BIT(TIMER2_TCCR_REG, TCCR2_COM00_BIT);
    SET_BIT(TIMER2_TCCR_REG, TCCR2_COM01_BIT);
#elif TIMER2_CTC_PWM_MODE== TIMER_SET_ON_CTC_CLR_ON_TOP
    SET_BIT(TIMER2_TCCR_REG, TCCR2_COM00_BIT);
    SET_BIT(TIMER2_TCCR_REG, TCCR2_COM01_BIT);
#else
#error
    "Wrong TIMER2_MODE Config"
#endif
    /*   SET PRELOAD   */
    TIMER2_OCR_REG = TIMER2_CTC_VAL;


#else
#error
    "Wrong TIMER0_MODE Config"
#endif

    /*SET TIMER0 CLOCK SOURCE*/
    TIMER2_TCCR_REG &= TCCR_PRE_MASK;
    TIMER2_TCCR_REG |= TIMER2_CLOCK;
}

void TIMER2_voidSetPreload(u8 Copy_u8Preload) {
    /*SET PRELOAD*/
    TIMER2_TCNT_REG = Copy_u8Preload;
}

void TIMER2_voidSetCTC(u8 Copy_u8Preload) {
    /*SET PRELOAD*/
    TIMER2_OCR_REG = Copy_u8Preload;

}

void TIMER2_voidDisable() {
    TIMER2_TCCR_REG &= TCCR_PRE_MASK;
    TIMER2_TCCR_REG |= 0;

}

ErrorStatus TIMER2_enumGetTimerCounterValue(u8 *Copy_pu8Value) {
    ErrorStatus LOC_ErrorStare = OK;
    if (Copy_pu8Value != NULL) {
        *Copy_pu8Value = TIMER2_TCNT_REG;
    } else {
        LOC_ErrorStare = NOK;
    }
    return LOC_ErrorStare;

}

/**********************************************TIMER_1_ICU*******************************************************************/
void TIMER_voidICUInit() {
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM11_BIT);
    CLEAR_BIT(TIMER1_TCCRA_REG, TCCR1A_WGM10_BIT);

    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM12_BIT);
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_WGM13_BIT);
    /*ICU_NOISE_CANCELER*/
#if ICU_NOISE_CANCELER == ICU_NOISE_CANCELER_EN
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_ICNC1_BIT);

#else
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_ICNC1_BIT);

#endif    
    /*Set STATE*/
#if TIMER_ICU_STATE == TIMER_ICU_STATE_RAISING
    SET_BIT(TIMER1_TCCRB_REG, TCCR1B_ICES1_BIT);
#elif     TIMER_ICU_STATE == TIMER_ICU_STATE_FALLING
    CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_ICES1_BIT);
#else
#error
    "Wrong TIMER_ICU_STATE Config"
#endif     

    /*Set STATE*/
#if TIMER1_OVF_INTERRUPT == TIMER_INTERRUPT_EN
    /* Enable Interrupt of ICU */
    SET_BIT(TIMSK_REG, TIMSK_TOIE1_BIT);
#elif   TIMER1_OVF_INTERRUPT == TIMER_INTERRUPT_DIS
    /* Enable Interrupt of ICU */
    CLEAR_BIT(TIMSK_REG, TIMSK_TOIE1_BIT);
#else
#error
    "Wrong TIMER_ICU_STATE Config"
#endif     

    TIMER1_TCCRB_REG &= TCCR_PRE_MASK;
    TIMER1_TCCRB_REG |= TIMER1_CLOCK;


}

ErrorStatus TIMER_enumICUSetTrigger(u8 Copy_u8Trigger) {
    ErrorStatus LOC_ErrorStare = OK;

    /*Set STATE*/
    if (Copy_u8Trigger == TIMER_ICU_STATE_RAISING) {
        SET_BIT(TIMER1_TCCRB_REG, TCCR1B_ICES1_BIT);
    } else if (Copy_u8Trigger == TIMER_ICU_STATE_FALLING) {
        CLEAR_BIT(TIMER1_TCCRB_REG, TCCR1B_ICES1_BIT);
    } else {
        LOC_ErrorStare = NOK;
    }
    return LOC_ErrorStare;
}

ErrorStatus TIMER_enumDetectCaptureSync(u8 Copy_u8Trigger, u16 *Copy_u8Ticks) {
    ErrorStatus LOC_Err = OK;
    TIMER_enumICUSetTrigger(Copy_u8Trigger);

    if (ICU_u8State == IDLE) {
        if (Copy_u8Ticks != NULL) {
            ICU_u8State = BUSY;
            while (GET_BIT(TIFR_REG, TIFR_ICF1_BIT) == 0);
            SET_BIT(TIFR_REG, TIFR_ICF1_BIT);
            SET_BIT(TIFR_REG, TIFR_TOV1_BIT);
            *Copy_u8Ticks = TIMER1_ICR1_REG;
            ICU_u8State = IDLE;
        } else {
            LOC_Err = NULL_PointerState;
        }
    } else {
        LOC_Err = Busy_State;
    }
    return LOC_Err;

}

void TIMER_voidICUEnableInterrupt() {
    /* Enable Interrupt of ICU */
    SET_BIT(TIMSK_REG, TIMSK_TICIE1_BIT);

}

void TIMER_voidICUDisableInterrupt() {
    /* Enable Interrupt of ICU */
    CLEAR_BIT(TIMSK_REG, TIMSK_TICIE1_BIT);

}

ErrorStatus TIMER_enumICRValue(u16 *Copy_pu16Value) {
    ErrorStatus LOC_ErrorStare = OK;

    /*Set STATE*/
    if (Copy_pu16Value != NULL) {
        *Copy_pu16Value = TIMER1_ICR1_REG;
    } else {
        LOC_ErrorStare = NOK;
    }

    return LOC_ErrorStare;
}

/**********************************************WDT*******************************************************************/

void WDT_voidSleap() {
    WDTCR_REG &= WDTCR_PRE_MASK;
    WDTCR_REG |= WDT_PRESCALER;
}

void WDT_voidEnable() {
    SET_BIT(WDTCR_REG, WDTCR_WDE_BIT);
}

void WDT_voidDisable() {
    WDTCR_REG |= WDTCR_DISABLE_MASK;
    WDTCR_REG = 0;
}

/**********************************************CallBack*******************************************************************/
ErrorStatus TIMER_SetCallBack(u8 Copy_u8VectorID, void (*Copy_pvoidCallBackFunc)(void)) {
    if (Copy_pvoidCallBackFunc != NULL) {
        TIMER_pvoidCallBackFunc[Copy_u8VectorID] = Copy_pvoidCallBackFunc;

    }
}

/**********************************************ISR_FUNC*******************************************************************/
void __vector_11(void) __attribute__((signal));

void __vector_11(void) {
    if (TIMER_pvoidCallBackFunc[TIMER0_OVF_VECTOR] != NULL) {

        TIMER_pvoidCallBackFunc[TIMER0_OVF_VECTOR]();
    }
}

void __vector_10(void) __attribute__((signal));

void __vector_10(void) {
    if (TIMER_pvoidCallBackFunc[TIMER0_CTC_VECTOR] != NULL) {

        TIMER_pvoidCallBackFunc[TIMER0_CTC_VECTOR]();

    }
}


void __vector_9(void) __attribute__((signal));

void __vector_9(void) {
    if (TIMER_pvoidCallBackFunc[TIMER1_OVF_VECTOR] != NULL) {

        TIMER_pvoidCallBackFunc[TIMER1_OVF_VECTOR]();

    }
}


void __vector_8(void) __attribute__((signal));

void __vector_8(void) {
    if (TIMER_pvoidCallBackFunc[TIMER1_CTCB_VECTOR] != NULL) {

        TIMER_pvoidCallBackFunc[TIMER1_CTCB_VECTOR]();

    }
}


void __vector_7(void) __attribute__((signal));

void __vector_7(void) {
    if (TIMER_pvoidCallBackFunc[TIMER1_CTCA_VECTOR] != NULL) {

        TIMER_pvoidCallBackFunc[TIMER1_CTCA_VECTOR]();

    }
}


void __vector_6(void) __attribute__((signal));

void __vector_6(void) {
    if (TIMER_pvoidCallBackFunc[TIMER1_ICU_VECTOR] != NULL) {

        TIMER_pvoidCallBackFunc[TIMER1_ICU_VECTOR]();

    }
}

void __vector_5(void) __attribute__((signal));

void __vector_5(void) {
    if (TIMER_pvoidCallBackFunc[TIMER2_OVF_VECTOR] != NULL) {

        TIMER_pvoidCallBackFunc[TIMER2_OVF_VECTOR]();
    }
}
void __vector_4(void) __attribute__((signal));

void __vector_4(void) {

    if (TIMER_pvoidCallBackFunc[TIMER2_CTC_VECTOR] != NULL) {

        TIMER_pvoidCallBackFunc[TIMER2_CTC_VECTOR]();
    }

}


