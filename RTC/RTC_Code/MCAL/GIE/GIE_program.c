/*
 * File:   GIE_program.c
 * Author: nour
 *
 * Created on September 12, 2023, 11:53 PM
 */


#include"GIE_interface.h"
void GIE_voidEnableInterrupt (){
   SET_BIT(SREG,SREG_IBIT);
}
void GIE_voidDisableInterrupt(){
    CLEAR_BIT(SREG,SREG_IBIT);
}
