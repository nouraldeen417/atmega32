/*
 * File:   newmain.c
 * Author: nour
 *
 * Created on August 29, 2023, 4:06 PM
 */


#define F_CPU 8000000UL
#include "MCAL/DIO/DIO_interface.h"
#include "lip/STD_TYPES.h"
#include"lip/Macros.h"
#include<util/delay.h>
#include"HAL/LCD/LCD_interface.h"
#include"MCAL/GIE/GIE_interface.h"
#include"MCAL/TIMER/TIMER_interface.h"
#include"HAL/Ultrasonic/ULTRA_interface.h"

UltraS_Type sens = {
    DIO_PORTD,
    DIO_PIN5
};

void main(void) {
    LCD_voidInit();
    _delay_ms(100);
    u8 dis = 0xFF;
    u8 LOC_Err;
    GIE_voidEnableInterrupt();
    ULTRA_voidInit();
   

    while (1) {
        LCD_voidDisplayClear();
      LCD_voidSetPosition(LCD_ROW_1,LCD_COL_1);
     ULTRA_SetTrigger(& sens);
    LOC_Err = ULTRA_GetDistance(& dis);
    if (LOC_Err == OK) {
        LCD_voidSendString("Distance is = ");
        LCD_voidSendNumber(dis);
        LCD_voidSendString("cm");
    } else if (LOC_Err == NOK) {
        LCD_voidSendString("Distance is Out of range");
    }
    _delay_ms(2000);
    }
}


