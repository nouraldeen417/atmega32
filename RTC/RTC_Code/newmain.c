/*
 * File:   newmain.c
 * Author: nour
 *
 * Created on August 29, 2023, 4:06 PM
 */

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
#define F_CPU 8000000UL
#include "MCAL/DIO/DIO_interface.h"
#include "lip/STD_TYPES.h"
#include"lip/Macros.h"
#include<util/delay.h>
#include"HAL/LCD/LCD_interface.h"
#include"HAL/KPD/KPD_interface.h"
#include"MCAL/GIE/GIE_interface.h"
#include"MCAL/TIMER/TIMER_interface.h"
#include "HAL/7Seg/7Seg_interface.h"
/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
/*Init 7segment Display */
// display Second First digit 
SSD_Type ssd2 = {
    SSD_COMMON_CATHODE,
    DIO_PORTB,
    DIO_PORTC,
    DIO_PIN0,

};
// display Seconds second digit
SSD_Type ssd1 = {
    SSD_COMMON_CATHODE,
    DIO_PORTB,
    DIO_PORTC,
    DIO_PIN1,

};
// display Minutes First digit
SSD_Type ssd3 = {
    SSD_COMMON_CATHODE,
    DIO_PORTB,
    DIO_PORTC,
    DIO_PIN2,

};
// display Minutes Second digit
SSD_Type ssd4 = {
    SSD_COMMON_CATHODE,
    DIO_PORTB,
    DIO_PORTC,
    DIO_PIN3,

};
// display Hours First digit
SSD_Type ssd5 = {
    SSD_COMMON_CATHODE,
    DIO_PORTB,
    DIO_PORTC,
    DIO_PIN4,

};
// display Hours second digit
SSD_Type ssd6 = {
    SSD_COMMON_CATHODE,
    DIO_PORTB,
    DIO_PORTC,
    DIO_PIN5,

};
// variable to count sec
static u8 Secound_Count;
// variable to count Minutes
static u8 Minute_Count;
// variable to count Hours
static u8 Hours_Count;
// variable to count ticks for 1 sec in timer0 
volatile u8 counter = 0;

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void Timer0_voidHandler();
static u8 APP_GetKPDInput();
static u8 APP_GetKPDNumber();
static void APP_Init();
static void APP_SevenSegDisable();

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
 * \Description     : ISR For Timer0                                    
 *                                                                             
 * \Sync\Async      : Synchronous                                               
 * \Reentrancy      : Non Reentrant                                             
 * \Parameters (in) : None                     
 * \Parameters (out): None                                                      
 * \Return value:   : None
 *                                  
 *******************************************************************************/

void Timer0_voidHandler() {
    if (counter == 30) {
        Secound_Count++;
        counter = 0;
    }
    counter++;

}
/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
 * \Description     : Get pressed button                                    
 *                                                                             
 * \Sync\Async      : Synchronous                                               
 * \Reentrancy      : Non Reentrant                                             
 * \Parameters (in) : None                     
 * \Parameters (out): None                                                      
 * \Return value:   : Pressed Button
 *                                  
 *******************************************************************************/

static u8 APP_GetKPDInput() {
    u8 Copy_PresssdVal = KPD_u8GetPressed();

    while (Copy_PresssdVal == KPD_NOTPRESSED) {
        Copy_PresssdVal = KPD_u8GetPressed();
    }

    return Copy_PresssdVal;

}
/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
 * \Description     : Get Number from KPD                                    
 *                                                                             
 * \Sync\Async      : Synchronous                                               
 * \Reentrancy      : Non Reentrant                                             
 * \Parameters (in) : None                     
 * \Parameters (out): None                                                      
 * \Return value:   : Number that user Enter form 2 digit
 *                                  
 *******************************************************************************/

static u8 APP_GetKPDNumber() {

    u8 LOC_u8Iterator;
    u8 Copy_u8TempVal = 0;
    for (LOC_u8Iterator = 0; LOC_u8Iterator < 2; LOC_u8Iterator++) {
        u8 Temp = APP_GetKPDInput();
        Copy_u8TempVal *= 10; // to form number from two digit 0:9 48:57
        Copy_u8TempVal += Temp - 48; // transform number from asci to decimal
        LCD_voidSetPosition(LCD_ROW_1, LCD_COL_10 + LOC_u8Iterator);
        LCD_voidSendData(Temp);
    }
    return Copy_u8TempVal;
}
/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
 * \Description     : Init Required Module                                    
 *                                                                             
 * \Sync\Async      : Synchronous                                               
 * \Reentrancy      : Non Reentrant                                             
 * \Parameters (in) : None                     
 * \Parameters (out): None                                                      
 * \Return value:   : None
 *                                  
 *******************************************************************************/
static void APP_Init() {
    LCD_voidInit();
    KPD_voidInit();
    SSD_voidInitDataPort(& ssd1);
    SSD_voidInitDataPort(& ssd2);
    SSD_voidInitDataPort(& ssd3);
    SSD_voidInitDataPort(& ssd4);
    SSD_voidInitDataPort(& ssd5);
    SSD_voidInitDataPort(& ssd6);
    DIO_voidSetPORTDirection(DIO_PORTC, DIO_PORT_OUTPUT);
    TIMER_SetCallBack(TIMER0_OVF_VECTOR, Timer0_voidHandler);
    TIMER0_voidInit();

}
/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
 * \Description     : Disable all Seven Segment                                   
 *                                                                             
 * \Sync\Async      : Synchronous                                               
 * \Reentrancy      : Non Reentrant                                             
 * \Parameters (in) : None                     
 * \Parameters (out): None                                                      
 * \Return value:   : Pressed Button
 *                                  
 *******************************************************************************/
static void APP_SevenSegDisable() {
    SSD_voidDisable(&ssd1);
    SSD_voidDisable(&ssd2);
    SSD_voidDisable(&ssd3);
    SSD_voidDisable(&ssd4);
    SSD_voidDisable(&ssd5);
    SSD_voidDisable(&ssd6);
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
void main(void) {
    u8 Copy_u8Choice;
    APP_Init();

    GIE_voidEnableInterrupt();

    LCD_voidSendString("Press 1 to");
    LCD_voidSetPosition(LCD_ROW_2, LCD_COL_2);
    LCD_voidSendString("Set Time");
    TIMER0_voidSetPreload(0);
    while (1) {
        Copy_u8Choice = KPD_u8GetPressed();
        if (Copy_u8Choice == '1') {
            GIE_voidDisableInterrupt();
            APP_SevenSegDisable();
            LCD_voidDisplayClear();
            LCD_voidSendString("Hours =");
            Hours_Count = APP_GetKPDNumber();
            _delay_ms(500);
            while (Hours_Count > 24) {
                LCD_voidDisplayClear();
                LCD_voidSendString("Try Again ");
                LCD_voidSetPosition(LCD_ROW_2, LCD_COL_1);
                LCD_voidSendString("Range 0:23");
                _delay_ms(500);
                LCD_voidDisplayClear();
                LCD_voidSendString("Hours =");
                Hours_Count = APP_GetKPDNumber();
            }
            LCD_voidDisplayClear();
            LCD_voidSendString("Minutes =");
            Minute_Count = APP_GetKPDNumber();
            while (Minute_Count > 60) {
                LCD_voidDisplayClear();
                LCD_voidSendString("Try Again ");
                LCD_voidSetPosition(LCD_ROW_2, LCD_COL_1);
                LCD_voidSendString("Range 0:59");
                _delay_ms(500);
                LCD_voidDisplayClear();
                LCD_voidSendString("Minutes =");
                Minute_Count = APP_GetKPDNumber();
            }
            _delay_ms(500);
            LCD_voidDisplayClear();
            LCD_voidSendString("Seconds =");
            Secound_Count = APP_GetKPDNumber();
            while (Secound_Count > 60) {
                LCD_voidDisplayClear();
                LCD_voidSendString("Try Again ");
                LCD_voidSetPosition(LCD_ROW_2, LCD_COL_1);
                LCD_voidSendString("Range 0:59");
                _delay_ms(500);
                LCD_voidDisplayClear();
                LCD_voidSendString("Seconds =");
                Secound_Count = APP_GetKPDNumber();
            }
            _delay_ms(500);
            LCD_voidDisplayClear();
            LCD_voidSendString("Press 1 to");
            LCD_voidSetPosition(LCD_ROW_2, LCD_COL_1);
            LCD_voidSendString("Set Time");
            GIE_voidEnableInterrupt();
            counter = 0;
            TIMER0_voidSetPreload(0);
        }

        DIO_voidSetPORTValue(DIO_PORTC, 0xFD);
        SSD_voidSendNumber(& ssd1, Secound_Count / 10);
        _delay_ms(1);
        DIO_voidSetPORTValue(DIO_PORTC, 0xFE);
        SSD_voidSendNumber(& ssd2, Secound_Count % 10);
        _delay_ms(1);
        DIO_voidSetPORTValue(DIO_PORTC, 0xFB);
        SSD_voidSendNumber(& ssd3, Minute_Count % 10);
        _delay_ms(1);
        DIO_voidSetPORTValue(DIO_PORTC, 0xF7);
        SSD_voidSendNumber(& ssd4, Minute_Count / 10);
        _delay_ms(1);
        DIO_voidSetPORTValue(DIO_PORTC, 0xEF);
        SSD_voidSendNumber(& ssd5, Hours_Count % 10);
        _delay_ms(1);
        DIO_voidSetPORTValue(DIO_PORTC, 0xDF);
        SSD_voidSendNumber(& ssd6, Hours_Count / 10);
        _delay_ms(1);
        if (Secound_Count == 60) {
            Secound_Count = 0;
            Minute_Count++;
        }
        if (Minute_Count == 60) {
            Minute_Count = 0;
            Hours_Count++;
        }
        if (Hours_Count == 24) {
            Hours_Count = 0;
        }

    }


}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/


