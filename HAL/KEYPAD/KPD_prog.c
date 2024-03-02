/*
 * KPD_prog.c
 *
 *  Created on: Aug 18, 2023
 *      Author: aya
 */

#include "../../LIB/types.h"
#include "../../LIB/errorState.h"

#include "../../MCAL/DIO_int.h"

#include "../LCD/LCD_int.h"

#include "KPD_config.h"
#include "KPD_priv.h"


u8 KPD_u8GetPressedKey_SamePORT(void)
{
	u8 Local_u8PressedKey=KPD_NO_PRESSED_KEY;
	u8 Local_u8ColumIdx,Local_u8RowIdx,Local_u8PinState;

	static u8 Local_u8KPDArr[4][4]=KPD_ARR_VAL;

	static u8 Local_u8KPDColumArr[COLUM_NUM]={KPD_COLUM0_PIN,KPD_COLUM1_PIN,KPD_COLUM2_PIN,KPD_COLUM3_PIN};
	static u8 Local_u8KPDRowArr[ROW_NUM]={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};


	for(Local_u8ColumIdx=0;Local_u8ColumIdx<COLUM_NUM;Local_u8ColumIdx++ )
	{
		//activate current colum
		DIO_enuSetPinValue(KPD_PORT,Local_u8KPDColumArr[Local_u8ColumIdx],DIO_u8LOW);

		for(Local_u8RowIdx=0;Local_u8RowIdx<ROW_NUM;Local_u8RowIdx++)
		{
			//read current row
			DIO_enuGetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8RowIdx],&Local_u8PinState);

			//check if switch pressed
			if(Local_u8PinState==DIO_u8LOW)
			{
				Local_u8PressedKey=Local_u8KPDArr[Local_u8RowIdx][Local_u8ColumIdx];

				//polling(busy waiting) until the key is realeased
				while(Local_u8PinState==DIO_u8LOW)
				{
					DIO_enuGetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8RowIdx],&Local_u8PinState);
				}

				return Local_u8PressedKey;
			}

		}
		//deactivate current colum
		DIO_enuSetPinValue(KPD_PORT,Local_u8KPDColumArr[Local_u8ColumIdx],DIO_u8HIGH);

	}


	return Local_u8PressedKey;
}

u8 KPD_u8GetPressedKey_DifPORT(void)
{
	u8 Local_u8PressedKey=KPD_NO_PRESSED_KEY;
	u8 Local_u8ColumIdx,Local_u8RowIdx,Local_u8PinState;

	static u8 Local_u8KPDArr[4][4]=KPD_ARR_VAL;

	static u8 Local_u8KPDColumArr_PORT[COLUM_NUM]={KPD_COLUM0_PORT,KPD_COLUM1_PORT,KPD_COLUM2_PORT,KPD_COLUM3_PORT};
	static u8 Local_u8KPDColumArr_PIN[COLUM_NUM]={KPD_COLUM0_PIN,KPD_COLUM1_PIN,KPD_COLUM2_PIN,KPD_COLUM3_PIN};

	static u8 Local_u8KPDRowArr_PORT[ROW_NUM]={KPD_ROW0_PORT,KPD_ROW1_PORT,KPD_ROW2_PORT,KPD_ROW3_PORT};
	static u8 Local_u8KPDRowArr_PIN[ROW_NUM]={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};


	for(Local_u8ColumIdx=0;Local_u8ColumIdx<COLUM_NUM;Local_u8ColumIdx++ )
	{
		//activate current colum
		DIO_enuSetPinValue(Local_u8KPDColumArr_PORT[Local_u8ColumIdx],Local_u8KPDColumArr_PIN[Local_u8ColumIdx],DIO_u8LOW);

		for(Local_u8RowIdx=0;Local_u8RowIdx<ROW_NUM;Local_u8RowIdx++)
		{
			//read current row
			DIO_enuGetPinValue(Local_u8KPDRowArr_PORT[Local_u8RowIdx],Local_u8KPDRowArr_PIN[Local_u8RowIdx],&Local_u8PinState);

			//check if switch pressed
			if(Local_u8PinState==DIO_u8LOW)
			{
				Local_u8PressedKey=Local_u8KPDArr[Local_u8RowIdx][Local_u8ColumIdx];

				//polling(busy waiting) until the key is realeased
				while(Local_u8PinState==DIO_u8LOW)
				{
					DIO_enuGetPinValue(Local_u8KPDRowArr_PORT[Local_u8RowIdx],Local_u8KPDRowArr_PIN[Local_u8RowIdx],&Local_u8PinState);
				}

				return Local_u8PressedKey;
			}

		}
		//deactivate current colum
		DIO_enuSetPinValue(Local_u8KPDColumArr_PORT[Local_u8ColumIdx],Local_u8KPDColumArr_PIN[Local_u8ColumIdx],DIO_u8HIGH);

	}


	return Local_u8PressedKey;
}

u8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8PressedKey=KPD_NO_PRESSED_KEY;
	u8 Local_u8ColumIdx,Local_u8RowIdx,Local_u8PinState;

	static u8 Local_u8KPDArr[4][4]=KPD_ARR_VAL;

#if KPD_SAMEPORT!=1
	static u8 Local_u8KPDColumArr_PORT[COLUM_NUM]={KPD_COLUM0_PORT,KPD_COLUM1_PORT,KPD_COLUM2_PORT,KPD_COLUM3_PORT};
	static u8 Local_u8KPDRowArr_PORT[ROW_NUM]={KPD_ROW0_PORT,KPD_ROW1_PORT,KPD_ROW2_PORT,KPD_ROW3_PORT};
#endif

	static u8 Local_u8KPDColumArr_PIN[COLUM_NUM]={KPD_COLUM0_PIN,KPD_COLUM1_PIN,KPD_COLUM2_PIN,KPD_COLUM3_PIN};
	static u8 Local_u8KPDRowArr_PIN[ROW_NUM]={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};


	for(Local_u8ColumIdx=0;Local_u8ColumIdx<COLUM_NUM;Local_u8ColumIdx++ )
	{
		//activate current colum
#if KPD_SAMEPORT==1

		DIO_enuSetPinValue(KPD_PORT,Local_u8KPDColumArr_PIN[Local_u8ColumIdx],DIO_u8LOW);
#else
		DIO_enuSetPinValue(Local_u8KPDColumArr_PORT[Local_u8ColumIdx],Local_u8KPDColumArr_PIN[Local_u8ColumIdx],DIO_u8LOW);
#endif

		for(Local_u8RowIdx=0;Local_u8RowIdx<ROW_NUM;Local_u8RowIdx++)
		{
			//read current row
#if KPD_SAMEPORT==1
			DIO_enuGetPinValue(KPD_PORT,Local_u8KPDRowArr_PIN[Local_u8RowIdx],&Local_u8PinState);
#else
			DIO_enuGetPinValue(Local_u8KPDRowArr_PORT[Local_u8RowIdx],Local_u8KPDRowArr_PIN[Local_u8RowIdx],&Local_u8PinState);
#endif

			//check if switch pressed
			if(Local_u8PinState==DIO_u8LOW)
			{
				Local_u8PressedKey=Local_u8KPDArr[Local_u8RowIdx][Local_u8ColumIdx];

				//polling(busy waiting) until the key is realeased
				while(Local_u8PinState==DIO_u8LOW)
				{
#if KPD_SAMEPORT==1
					DIO_enuGetPinValue(KPD_PORT,Local_u8KPDRowArr_PIN[Local_u8RowIdx],&Local_u8PinState);
#else
					DIO_enuGetPinValue(Local_u8KPDRowArr_PORT[Local_u8RowIdx],Local_u8KPDRowArr_PIN[Local_u8RowIdx],&Local_u8PinState);
#endif
				}

				return Local_u8PressedKey;
			}

		}
		//deactivate current colum
#if KPD_SAMEPORT==1
		DIO_enuSetPinValue(KPD_PORT,Local_u8KPDColumArr_PIN[Local_u8ColumIdx],DIO_u8HIGH);
#else
		DIO_enuSetPinValue(Local_u8KPDColumArr_PORT[Local_u8ColumIdx],Local_u8KPDColumArr_PIN[Local_u8ColumIdx],DIO_u8HIGH);
#endif

	}


	return Local_u8PressedKey;
}




