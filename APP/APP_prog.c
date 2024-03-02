/*
 * KPD_APP.c
 *
 *  Created on: Aug 19, 2023
 *      Author: aya
 */

#include "../LIB/types.h"
#include "../LIB/errorState.h"

#include "../MCAL/DIO_int.h"

#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LCD/LCD_config.h"

#include "../HAL/KEYPAD/KPD_int.h"
#include "../HAL/KEYPAD/KPD_config.h"

#include "APP_priv.h"




s16 APP_s16Solve(s16 Copy_s16Operand1 , s16 Copy_s16Operand2 , u8 Copy_u8Operation)
{
	switch(Copy_u8Operation)
	{
	case '+':
		if(APP_SignBit)
		{
			if(Copy_s16Operand2>=Copy_s16Operand1)
			{
				APP_SignBit=0;
			return Copy_s16Operand2-Copy_s16Operand1;
			}
			else
			{
				return Copy_s16Operand1 - Copy_s16Operand2;
			}
		}
		else
		{
		return Copy_s16Operand1 + Copy_s16Operand2;
		}
	case '-':
		if(APP_SignBit)
		{
			return Copy_s16Operand1 + Copy_s16Operand2;
		}
		else
		{
			if(Copy_s16Operand1>=Copy_s16Operand2)
			{
				return Copy_s16Operand1 - Copy_s16Operand2;
			}
			else if(Copy_s16Operand1<Copy_s16Operand2)
			{
				APP_SignBit=1;
				return Copy_s16Operand2 - Copy_s16Operand1;
			}
		}
	case '*':
		return Copy_s16Operand1 * Copy_s16Operand2;
	case '/':
		if(Copy_s16Operand2==0)
		{
			return 0;
		}
		else
		{
			return Copy_s16Operand1 / Copy_s16Operand2;
		}
	default:
		return Copy_s16Operand1;
	}
}


ES_t APP_enuCalculator()
{
	ES_t Local_enuErrorState=ES_NOK;

	LCD_enuInit();

	s16 Local_u8Operand1=0,Local_u8Operand2=0;

	u8 Local_u8Operation , Local_OPflag , Local_NUMflag;


	while(1)
	{
		u8 Local_u8PressedKey;

		do
		{
			Local_u8PressedKey=KPD_u8GetPressedKey();
		}while(Local_u8PressedKey==0xff);

		if(Local_u8PressedKey>='0' && Local_u8PressedKey<='9')
		{
			if(Local_NUMflag==0)
			{
				Local_NUMflag=1;

				Local_u8Operand1=Local_u8PressedKey-'0';

				LCD_enuClearLcd();
				LCD_enuDisplayNum(Local_u8Operand1);

			}
			else if(Local_NUMflag==1)
			{
				Local_u8Operand1=Local_u8Operand1*10+(Local_u8PressedKey-'0');

				LCD_enuClearLcd();
				LCD_enuDisplayNum(Local_u8Operand1);

			}
			else if(Local_NUMflag==2)
			{
				Local_u8Operand2=Local_u8Operand2*10+(Local_u8PressedKey-'0');

				Local_OPflag=0;

				LCD_enuClearLcd();
				LCD_enuDisplayNum(Local_u8Operand2);
			}
		}
		else if (Local_u8PressedKey == '+' || Local_u8PressedKey == '-' || Local_u8PressedKey == '*' || Local_u8PressedKey == '/')
		{
			if(!Local_OPflag)
			{
				if(Local_NUMflag==2)
				{
					Local_u8Operand1=APP_s16Solve(Local_u8Operand1,Local_u8Operand2,Local_u8Operation);

					Local_u8Operand2=0;

					LCD_enuClearLcd();
					if(APP_SignBit)
					{
						//APP_SignBit=0;
						LCD_enuDisplayChar('-');
						LCD_enuDisplayNum(Local_u8Operand1);
					}
					else
					{
						LCD_enuDisplayNum(Local_u8Operand1);
					}
				}
				Local_NUMflag=2;
			}
			Local_u8Operation=Local_u8PressedKey;

			Local_OPflag=1;
		}
		else if(Local_u8PressedKey=='=')
		{
			Local_u8Operand1=APP_s16Solve(Local_u8Operand1,Local_u8Operand2,Local_u8Operation);

			Local_u8Operand2=0;

			Local_u8Operation=0;

			Local_OPflag=0;

			Local_NUMflag=0;

			LCD_enuClearLcd();
			if(APP_SignBit)
			{
				//APP_SignBit=0;
				LCD_enuDisplayChar('-');
				LCD_enuDisplayNum(Local_u8Operand1);
			}
			else
			{
				LCD_enuDisplayNum(Local_u8Operand1);
			}
		}
		else if(Local_u8PressedKey=='c')
		{
			Local_u8Operand1=0;

			Local_u8Operand2=0;

			Local_u8Operation=0;

			Local_OPflag=0;

			Local_NUMflag=0;

			APP_SignBit=0;

			LCD_enuClearLcd();
		}
	}


	return Local_enuErrorState;
}



/*


ES_t KPD_enuCalculator()
{
	ES_t Local_enuErrorState=ES_NOK;

	u8 Local_u8Operand1=0,Local_u8Operand2=0 ,Local_u8Operation='\0',Local_u8PressedKey,Local_u8SignBit=0;
	u64 Local_u64Result;


	do
	{
		Local_u8PressedKey=KPD_u8GetPressedKey();
	}while(Local_u8PressedKey==0xff);

	Local_u8Operand1=Local_u8PressedKey;
	LCD_enuClearLcd();
	LCD_enuDisplayNum(Local_u8Operand1);

	do
	{
		Local_u8PressedKey=KPD_u8GetPressedKey();
	}while(Local_u8PressedKey==0xff);

	Local_u8Operation=Local_u8PressedKey;
	LCD_enuClearLcd();
	LCD_enuDisplayChar(Local_u8Operation);

	do
	{
		Local_u8PressedKey=KPD_u8GetPressedKey();
	}while(Local_u8PressedKey==0xff);

	Local_u8Operand2=Local_u8PressedKey;
	LCD_enuClearLcd();
	LCD_enuDisplayNum(Local_u8Operand2);

	switch(Local_u8Operation)
	{
	case '+':
		Local_u64Result=Local_u8Operand1 + Local_u8Operand2;
		break;
	case '-':
		if(Local_u8Operand1>=Local_u8Operand2)
		{
			Local_u64Result=Local_u8Operand1 - Local_u8Operand2;
		}
		else
		{
			Local_u8SignBit=1;
			Local_u64Result=Local_u8Operand2 - Local_u8Operand1;
		}
		break;
	case '*':
		Local_u64Result=Local_u8Operand1 * Local_u8Operand2;
		break;
	case '/':
		if(Local_u8Operand2!=0)
		{
			Local_u64Result=Local_u8Operand1 / Local_u8Operand2;
		}
		else
		{
			LCD_enuClearLcd();
			LCD_enuDisplayString("error");
		}
		break;
	}

	do
	{
		Local_u8PressedKey=KPD_u8GetPressedKey();
	}while(Local_u8PressedKey==0xff);

	if(Local_u8PressedKey=='=')
	{
		LCD_enuClearLcd();
		if(Local_u8SignBit)
		{
			LCD_enuDisplayChar('-');
		}
		LCD_enuDisplayNum(Local_u64Result);
	}


	return Local_enuErrorState;
}

*/
