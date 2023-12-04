/*
 * File:   DIO_program.c
 * Author: nour
 *
 * Created on August 29, 2023, 8:51 PM
 */


#include <xc.h>
#include"DIO_interface.h"
#include "../../lip/Macros.h"

DIO_ErrorStatus DIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction) {
    DIO_ErrorStatus LOC_enumState = DIO_OK;
    if (Copy_u8Port <= DIO_PORTD && Copy_u8Pin <= DIO_PIN7) {
        if (Copy_u8Direction == DIO_PIN_OUTPUT) {
            switch (Copy_u8Port) {
                case DIO_PORTA:
                    SET_BIT(DDRA, Copy_u8Pin);
                    break;
                case DIO_PORTB:
                    SET_BIT(DDRB, Copy_u8Pin);
                    break;
                case DIO_PORTC:
                    SET_BIT(DDRC, Copy_u8Pin);
                    break;
                case DIO_PORTD:
                    SET_BIT(DDRD, Copy_u8Pin);
                    break;
            }

        } else if (Copy_u8Direction == DIO_PIN_INPUT) {
            switch (Copy_u8Port) {
                case DIO_PORTA:
                    CLEAR_BIT(DDRA, Copy_u8Pin);
                    break;
                case DIO_PORTB:
                    CLEAR_BIT(DDRB, Copy_u8Pin);
                    break;
                case DIO_PORTC:
                    CLEAR_BIT(DDRC, Copy_u8Pin);
                    break;
                case DIO_PORTD:
                    CLEAR_BIT(DDRD, Copy_u8Pin);
                    break;
            }
        }


    } else {
             LOC_enumState = DIO_NOK;
    }

    return LOC_enumState;
}

DIO_ErrorStatus DIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Value) {

    DIO_ErrorStatus LOC_enumState = DIO_OK;
    if (Copy_u8Port <= DIO_PORTD && Copy_u8Pin <= DIO_PIN7) {

        if (Value == DIO_PIN_HIGH) {

            switch (Copy_u8Port) {
                case DIO_PORTA:
                    SET_BIT(PORTA, Copy_u8Pin);
                    break;
                case DIO_PORTB:
                    SET_BIT(PORTB, Copy_u8Pin);
                    break;
                case DIO_PORTC:
                    SET_BIT(PORTC, Copy_u8Pin);
                    break;
                case DIO_PORTD:
                    SET_BIT(PORTD, Copy_u8Pin);
                    break;
            }
        } else if (Value == DIO_PIN_LOW) {
            switch (Copy_u8Port) {
                case DIO_PORTA:
                    CLEAR_BIT(PORTA, Copy_u8Pin);
                    break;
                case DIO_PORTB:
                    CLEAR_BIT(PORTB, Copy_u8Pin);
                    break;
                case DIO_PORTC:
                    CLEAR_BIT(PORTC, Copy_u8Pin);
                    break;
                case DIO_PORTD:
                    CLEAR_BIT(PORTD, Copy_u8Pin);
                    break;
            }
        }
    } else {
        LOC_enumState = DIO_NOK;
    }

    return LOC_enumState;
}

DIO_ErrorStatus DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 * Copy_PtrData) {
    DIO_ErrorStatus LOC_enumState = DIO_OK;
    if (Copy_u8Port <= DIO_PORTD && Copy_u8Pin <= DIO_PIN7) {

        switch (Copy_u8Port) {
            case DIO_PORTA:
                * Copy_PtrData = GET_BIT(PINA, Copy_u8Pin);
                break;
            case DIO_PORTB:
                * Copy_PtrData = GET_BIT(PINB, Copy_u8Pin);
                break;
            case DIO_PORTC:
                * Copy_PtrData = GET_BIT(PINC, Copy_u8Pin);
                break;
            case DIO_PORTD:
                * Copy_PtrData = GET_BIT(PIND, Copy_u8Pin);
                break;
        }
    } else {
        LOC_enumState = DIO_NOK;
    }
    return LOC_enumState;
}
DIO_ErrorStatus DIO_u8ReadPinState(u8 Copy_u8Port, u8 Copy_u8Pin, u8 * Copy_PtrData) {
    DIO_ErrorStatus LOC_enumState = DIO_OK;
    if (Copy_u8Port <= DIO_PORTD && Copy_u8Pin <= DIO_PIN7) {

        switch (Copy_u8Port) {
            case DIO_PORTA:
                * Copy_PtrData = GET_BIT(PORTA, Copy_u8Pin);
                break;
            case DIO_PORTB:
                * Copy_PtrData = GET_BIT(PORTB, Copy_u8Pin);
                break;
            case DIO_PORTC:
                * Copy_PtrData = GET_BIT(PORTC, Copy_u8Pin);
                break;
            case DIO_PORTD:
                * Copy_PtrData = GET_BIT(PORTD, Copy_u8Pin);
                break;
        }
    } else {
        LOC_enumState = DIO_NOK;
    }
    return LOC_enumState;
}

DIO_ErrorStatus DIO_voidSetPORTDirection(u8 Copy_u8Port, u8 Copy_u8Direction) {
    DIO_ErrorStatus LOC_enumState = DIO_OK;
    if (Copy_u8Port <= DIO_PORTD) {
        if (Copy_u8Direction == DIO_PORT_OUTPUT) {
            switch (Copy_u8Port) {
                case DIO_PORTA:
                    DDRA = DIO_PORT_OUTPUT;
                    break;
                case DIO_PORTB:
                    DDRB = DIO_PORT_OUTPUT;
                    break;
                case DIO_PORTC:
                    DDRC = DIO_PORT_OUTPUT;
                    break;
                case DIO_PORTD:
                    DDRD = DIO_PORT_OUTPUT;
                    break;
            }

        } else if (Copy_u8Direction == DIO_PORT_INPUT) {
            switch (Copy_u8Port) {
                case DIO_PORTA:
                    DDRA = DIO_PORT_INPUT;
                    break;
                case DIO_PORTB:
                    DDRB = DIO_PORT_INPUT;
                    break;
                case DIO_PORTC:
                    DDRC = DIO_PORT_INPUT;
                    break;
                case DIO_PORTD:
                    DDRD = DIO_PORT_INPUT;
                    break;
            }
        }


    } else {
        LOC_enumState = DIO_NOK;
    }

    return LOC_enumState;
}

DIO_ErrorStatus DIO_voidSetPORTValue(u8 Copy_u8Port, u8 Copy_u8Value) {
    DIO_ErrorStatus LOC_enumState = DIO_OK;
    if (Copy_u8Port <= DIO_PORTD) {
       
            switch (Copy_u8Port) {
                case DIO_PORTA:
                    PORTA = Copy_u8Value;
                    break;
                case DIO_PORTB:
                    PORTB = Copy_u8Value;
                    break;
                case DIO_PORTC:
                    PORTC = Copy_u8Value;
                    break;
                case DIO_PORTD:
                    PORTD = Copy_u8Value;
                    break;
            }

        }  
        

     else {
         LOC_enumState = DIO_NOK;
    }

    return LOC_enumState;
}

DIO_ErrorStatus DIO_u8GetPORTValue(u8 Copy_u8Port, u8 * Copy_PtrData) {
    DIO_ErrorStatus LOC_enumState = DIO_OK;
    if (Copy_u8Port <= DIO_PORTD) {

        switch (Copy_u8Port) {
            case DIO_PORTA:
                * Copy_PtrData = PINA;
                break;
            case DIO_PORTB:
                * Copy_PtrData = PINB;
                break;
            case DIO_PORTC:
                * Copy_PtrData = PINC;
                break;
            case DIO_PORTD:
                * Copy_PtrData = PIND;
                break;
        }





    } else {
        LOC_enumState = DIO_NOK;
    }

    return LOC_enumState;
}

DIO_ErrorStatus DIO_voidTogglePinValue(u8 Copy_u8Port, u8 Copy_u8Pin) {
    DIO_ErrorStatus LOC_enumState = DIO_OK;
    if (Copy_u8Port <= DIO_PORTD && Copy_u8Pin <= DIO_PIN7) {

        switch (Copy_u8Port) {
            case DIO_PORTA:
                TOGGLE_BIT(PORTA, Copy_u8Pin);
                break;
            case DIO_PORTB:
                TOGGLE_BIT(PORTB, Copy_u8Pin);
                break;
            case DIO_PORTC:
                TOGGLE_BIT(PORTC, Copy_u8Pin);
                break;
            case DIO_PORTD:
                TOGGLE_BIT(PORTD, Copy_u8Pin);
                break;
        }
    } else {
       LOC_enumState = DIO_NOK;
    }

    return LOC_enumState;
}

DIO_ErrorStatus DIO_voidSetPortLOWNibble(u8 Copy_u8Port, u8 Copy_u8Value) {
    Copy_u8Value &= 0x0f;
    DIO_ErrorStatus LOC_enumState = DIO_OK;

    if (Copy_u8Port <= DIO_PORTD) {
        switch (Copy_u8Port) {
            case DIO_PORTA:
                PORTA &= 0xf0;
                PORTA |= Copy_u8Value;
                break;
            case DIO_PORTB:
                PORTB &= 0xf0;
                PORTB |= Copy_u8Value;
                break;
            case DIO_PORTC:
                PORTC &= 0xf0;
                PORTC |= Copy_u8Value;
                break;
            case DIO_PORTD:
                PORTD &= 0xf0;
                PORTD |= Copy_u8Value;
                break;
        }

    } else {
        LOC_enumState = DIO_NOK;
    }

    return LOC_enumState;

}

DIO_ErrorStatus DIO_voidSetPortHIGHNibble(u8 Copy_u8Port, u8 Copy_u8Value) {
    DIO_ErrorStatus LOC_enumState = DIO_OK;

    Copy_u8Value &= 0x0f;

    if (Copy_u8Port <= DIO_PORTD) {
        switch (Copy_u8Port) {
            case DIO_PORTA:
                PORTA &= 0x0f;
                PORTA |= (Copy_u8Value << 4);
                break;
            case DIO_PORTB:
                PORTB &= 0x0f;
                PORTB |= (Copy_u8Value << 4);
                break;
            case DIO_PORTC:
                PORTC &= 0x0f;
                PORTC |= (Copy_u8Value << 4);
                break;
            case DIO_PORTD:
                PORTD &= 0x0f;
                PORTD |= (Copy_u8Value << 4);
                break;
        }

    } else {
        LOC_enumState = DIO_NOK;
    }

    return LOC_enumState;

}

DIO_ErrorStatus DIO_voidEnablePullup(u8 Copy_u8Port, u8 Copy_u8Pin) {
    DIO_ErrorStatus LOC_enumState = DIO_OK;
    CLEAR_BIT(SFIOR, DIO_PULLUP_BIT);
    if (Copy_u8Port <= DIO_PORTD && Copy_u8Pin <= DIO_PIN7) {

        switch (Copy_u8Port) {
            case DIO_PORTA:
                CLEAR_BIT(DDRA, Copy_u8Pin);
                SET_BIT(PORTA, Copy_u8Pin);
                break;
            case DIO_PORTB:
                CLEAR_BIT(DDRB, Copy_u8Pin);
                SET_BIT(PORTB, Copy_u8Pin);
                break;
            case DIO_PORTC:
                CLEAR_BIT(DDRC, Copy_u8Pin);
                SET_BIT(PORTC, Copy_u8Pin);
                break;
            case DIO_PORTD:
                CLEAR_BIT(DDRD, Copy_u8Pin);
                SET_BIT(PORTD, Copy_u8Pin);
                break;
        }

    } else {
        LOC_enumState = DIO_NOK;
    }

    return LOC_enumState;
}

DIO_ErrorStatus DIO_voidDisablePullup() {
    DIO_ErrorStatus LOC_enumState = DIO_OK;

    SET_BIT(SFIOR, DIO_PULLUP_BIT);


    return LOC_enumState;
}