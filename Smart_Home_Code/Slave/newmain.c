/*
 * File:   
 * Author: Nour Aldeen Nabil
 *
 * Created on October 1, 2023, 4:06 PM
 */


#define F_CPU  8000000UL
#include"APP/APP_Slaveinterface.h"

void main(void) {
    u8 Copy_u8Datareceived = 255;
    APP_Init();
    while (1) {
        if (APP_MasterGetId(& Copy_u8Datareceived) == OK) {
            if (Copy_u8Datareceived > 0 && Copy_u8Datareceived < APP_TV) {
                APP_RommsControl(Copy_u8Datareceived);
            }
            if (Copy_u8Datareceived == APP_TV) {
                APP_TVControl();
            }
            if (Copy_u8Datareceived == APP_AIR_COND) {
                APP_AirCondControl();
            }

        }else{
            // do nothing
        }

    }
}

