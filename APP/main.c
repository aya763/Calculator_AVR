/*
 * main.c
 *
 *  Created on: Aug 8, 2023
 *      Author: aya
 */

#include "../LIB/types.h"
#include "../LIB/errorState.h"

#include "../MCAL/DIO_int.h"

#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LCD/LCD_config.h"

#include "../HAL/KEYPAD/KPD_int.h"
#include "../HAL/KEYPAD/KPD_config.h"

#include "APP_int.h"

#include "util/delay.h"

int main(void)
{
	DIO_enuInit();
	LCD_enuInit();
	APP_enuCalculator();


	while(1);


	return 0;
}
