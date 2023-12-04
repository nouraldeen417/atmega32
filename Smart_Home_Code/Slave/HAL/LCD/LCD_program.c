/*
 * File:   LCD_interface.c
 * Author: nour
 *
 * Created on September 1, 2023, 5:29 PM
 */


#include <xc.h>
#include<util/delay.h>
#include"LCD_interface.h"

static void LCD_voidSendFallinEdge() {
    DIO_voidSetPinValue(LCD_Control_PORT, LCD_EN_PIN, DIO_PIN_HIGH);
    _delay_ms(100);
    DIO_voidSetPinValue(LCD_Control_PORT, LCD_EN_PIN, DIO_PIN_LOW);
    _delay_ms(1);

}

void LCD_voidDisplayClear() {
    LCD_voidSendCommand(lcd_Clear);
    _delay_ms(10);
}

void LCD_voidSendData(u8 LCD_u8Data) {
#if LCD_MODE==8
    DIO_voidSetPORTValue(LCD_Data_PORT, LCD_u8Data);
    DIO_voidSetPinValue(LCD_Control_PORT, LCD_RS_PIN, DIO_PIN_HIGH);
    DIO_voidSetPinValue(LCD_Control_PORT, LCD_RW_PIN, DIO_PIN_LOW);
    LCD_voidSendFallinEdge();
#elif LCD_MODE==4
#if LCD_DATA_PIN == LCD_PINS_0_3
    DIO_voidSetPinValue(LCD_Control_PORT, LCD_RS_PIN, DIO_PIN_HIGH);
    DIO_voidSetPinValue(LCD_Control_PORT, LCD_RW_PIN, DIO_PIN_LOW);
    DIO_voidSetPortLOWNibble(LCD_Data_PORT, (LCD_u8Data >> 4));
    LCD_voidSendFallinEdge();
    DIO_voidSetPortLOWNibble(LCD_Data_PORT, LCD_u8Data);
    LCD_voidSendFallinEdge();
#elif LCD_DATA_PIN == LCD_PINS_4_8
    DIO_voidSetPinValue(LCD_Control_PORT, LCD_RS_PIN, DIO_PIN_HIGH);
    DIO_voidSetPinValue(LCD_Control_PORT, LCD_RW_PIN, DIO_PIN_LOW);
    DIO_voidSetPortHIGHNibble(LCD_Data_PORT, (LCD_u8Data >> 4));
    LCD_voidSendFallinEdge();
    DIO_voidSetPortHIGHNibble(LCD_Data_PORT, LCD_u8Data);
    LCD_voidSendFallinEdge();
#else
#endif
#endif


    
    _delay_ms(1);

}

void LCD_voidSendCommand(u8 LCD_u8Command) {
#if LCD_MODE==8
    DIO_voidSetPORTValue(LCD_Data_PORT, LCD_u8Command);
    DIO_voidSetPinValue(LCD_Control_PORT, LCD_RS_PIN, DIO_PIN_LOW);
    DIO_voidSetPinValue(LCD_Control_PORT, LCD_RW_PIN, DIO_PIN_LOW);
    LCD_voidSendFallinEdge();
#elif LCD_MODE==4
#if LCD_DATA_PIN == LCD_PINS_0_3
    DIO_voidSetPinValue(LCD_Control_PORT, LCD_RS_PIN, DIO_PIN_LOW);
    DIO_voidSetPinValue(LCD_Control_PORT, LCD_RW_PIN, DIO_PIN_LOW);
    DIO_voidSetPortLOWNibble(LCD_Data_PORT, (LCD_u8Command >> 4));
    LCD_voidSendFallinEdge();
    DIO_voidSetPortLOWNibble(LCD_Data_PORT, LCD_u8Command);
    LCD_voidSendFallinEdge();
#elif LCD_DATA_PIN == LCD_PINS_4_8
    DIO_voidSetPinValue(LCD_Control_PORT, LCD_RS_PIN, DIO_PIN_LOW);
    DIO_voidSetPinValue(LCD_Control_PORT, LCD_RW_PIN, DIO_PIN_LOW);
    DIO_voidSetPortHIGHNibble(LCD_Data_PORT, (LCD_u8Command >> 4));
    LCD_voidSendFallinEdge();
    DIO_voidSetPortHIGHNibble(LCD_Data_PORT, LCD_u8Command);
    LCD_voidSendFallinEdge();
#else
#endif
    
#endif    
    _delay_ms(1);

}

void LCD_voidInit() {
#if LCD_MODE==8
    _delay_ms(50);
    DIO_voidSetPORTDirection(LCD_Data_PORT, DIO_PORT_OUTPUT);
    DIO_voidSetPinDirection(LCD_Control_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_Control_PORT, LCD_RW_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_Control_PORT, LCD_EN_PIN, DIO_PIN_OUTPUT);
    LCD_voidSendCommand(lcd_Home);
    _delay_ms(1);
    LCD_voidSendCommand(EIGHT_BITS);
    _delay_ms(1);
    LCD_voidSendCommand(lcd_DisplayOn_CursorOff);
    _delay_ms(100);
    LCD_voidDisplayClear();
    LCD_voidSendCommand(lcd_EntryMode);
    _delay_ms(1);
#elif LCD_MODE==4
    _delay_ms(50);
    DIO_voidSetPinDirection(LCD_Data_PORT, LCD_DATA_PIN1, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_Data_PORT, LCD_DATA_PIN2, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_Data_PORT, LCD_DATA_PIN3, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_Data_PORT, LCD_DATA_PIN4, DIO_PIN_OUTPUT);

    DIO_voidSetPinDirection(LCD_Control_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_Control_PORT, LCD_RW_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_Control_PORT, LCD_EN_PIN, DIO_PIN_OUTPUT);
    LCD_voidSendCommand(lcd_Home);
    _delay_ms(1);
    LCD_voidSendCommand(FOUR_BITS);
    _delay_ms(50);
    LCD_voidSendCommand(lcd_DisplayOn_CursorOff);
    _delay_ms(100);
    LCD_voidDisplayClear();
    LCD_voidSendCommand(lcd_EntryMode);
    _delay_ms(1);

#endif    

}

void LCD_voidSendString(const u8* LCD_u8PtrString) {
    u8 LOC_u8Iterator = 0;
    while (LCD_u8PtrString[LOC_u8Iterator] != '\0') {
        LCD_voidSendData(LCD_u8PtrString[LOC_u8Iterator]);
        LOC_u8Iterator++;
    }
}

void LCD_voidSetPosition(u8 LCD_u8Row, u8 LCD_u8Colum) {
    u8 LOC_u8Data; //0x80
    if (LCD_u8Row > LCD_ROW_2 && LCD_u8Colum > LCD_COL_16) {
        LOC_u8Data = lcd_SetCursor; //0x80
    } else if (LCD_u8Row == LCD_ROW_1) {

        LOC_u8Data = lcd_SetCursor + LCD_u8Colum;
    } else if (LCD_u8Row == LCD_ROW_2) {
        LOC_u8Data = lcd_SetCursor + LCD_u8Colum + (64);
    }
    LCD_voidSendCommand(LOC_u8Data);
    _delay_ms(1);
}

void LCD_voidSendExtraChar(u8 LCD_u8Row, u8 LCD_u8Colum) {
    u8 LOC_u8Iterator = 0;
    LCD_voidSendCommand(lcd_CGRAM);

    for (LOC_u8Iterator = 0; LOC_u8Iterator< sizeof (LCD_u8ExtraChars) / sizeof (LCD_u8ExtraChars[0]); LOC_u8Iterator++) {
        LCD_voidSendData(LCD_u8ExtraChars[LOC_u8Iterator]);
    }

    LCD_voidSetPosition(LCD_u8Row, LCD_u8Colum);

    for (LOC_u8Iterator = 0; LOC_u8Iterator < 8; LOC_u8Iterator++) {
        LCD_voidSendData(LOC_u8Iterator);
    }



}

void LCD_voidSendNumber(u64 Copy_u64Number) {
    u64 LOC_u64Temp = 1;
    if (Copy_u64Number == 0) {
        LCD_voidSendData('0');
    } else {
        while (Copy_u64Number != 0) {
            LOC_u64Temp = (LOC_u64Temp * 10)+(Copy_u64Number % 10);
            Copy_u64Number /= 10;
        }
        while (LOC_u64Temp != 1) {
            LCD_voidSendData((LOC_u64Temp % 10) + 48);
            LOC_u64Temp /= 10;
        }
    }

}