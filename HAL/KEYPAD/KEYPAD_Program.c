#include "stdTypes.h"
#include "errorStates.h"

#include "DIO_int.h"
#include "DIO_config.h"

#include "KeyPad_config.h"
#include "KeyPad_priv.h"

#include <util/delay.h>


#define KeyNotPressed 0xff
ES_t KeyPad_enuInit(void)
{
	ES_t Local_u8ErrorState=ES_NOK;

	//Rows input
	Local_u8ErrorState=DIO_enuSetPinDirection(R1_PORT,R1_PIN,DIO_u8INPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(R2_PORT,R2_PIN,DIO_u8INPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(R3_PORT,R3_PIN,DIO_u8INPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(R4_PORT,R4_PIN,DIO_u8INPUT);

	//pull up
	Local_u8ErrorState=DIO_enuSetPinValue(R1_PORT,R1_PIN,DIO_u8PULLUP);
	Local_u8ErrorState=DIO_enuSetPinValue(R2_PORT,R2_PIN,DIO_u8PULLUP);
	Local_u8ErrorState=DIO_enuSetPinValue(R3_PORT,R3_PIN,DIO_u8PULLUP);
	Local_u8ErrorState=DIO_enuSetPinValue(R4_PORT,R4_PIN,DIO_u8PULLUP);

	//Columns output
	Local_u8ErrorState=DIO_enuSetPinDirection(C1_PORT,C1_PIN,DIO_u8OUTPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(C2_PORT,C2_PIN,DIO_u8OUTPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(C3_PORT,C3_PIN,DIO_u8OUTPUT);
	Local_u8ErrorState=DIO_enuSetPinDirection(C4_PORT,C4_PIN,DIO_u8OUTPUT);

	//Columns high
	Local_u8ErrorState=DIO_enuSetPinValue(C1_PORT,C1_PIN,DIO_u8HIGH);
	Local_u8ErrorState=DIO_enuSetPinValue(C2_PORT,C2_PIN,DIO_u8HIGH);
	Local_u8ErrorState=DIO_enuSetPinValue(C3_PORT,C3_PIN,DIO_u8HIGH);
	Local_u8ErrorState=DIO_enuSetPinValue(C4_PORT,C4_PIN,DIO_u8HIGH);

	return Local_u8ErrorState;
}

ES_t KeyPad_enuKeyPressed(u8* Copy_pu8PressedKey)
{
	ES_t Local_u8ErrorState=ES_NOK;

	if(Copy_pu8PressedKey!=NULL)
	{

		*Copy_pu8PressedKey=KeyNotPressed;
		u8 Local_u8ArrRowsPins[ROWS_NUM]={R1_PIN,R2_PIN,R3_PIN,R4_PIN};
		u8 Local_u8ArrRowsPorts[ROWS_NUM]={R1_PORT,R2_PORT,R3_PORT,R4_PORT};
		u8 Local_u8ArrColumnsPins[COLUMNS_NUM]={C1_PIN,C2_PIN,C3_PIN,C4_PIN};
		u8 Local_u8ArrColumnsPorts[COLUMNS_NUM]={C1_PORT,C2_PORT,C3_PORT,C4_PORT};

		u8 Local_Au8KeyValues[ROWS_NUM][COLUMNS_NUM] = KEY_VALUES;

		u8 Local_u8ColIterator,Local_u8RowIterator,Local_u8PinState=KeyNotPressed;
		for(Local_u8ColIterator=0;Local_u8ColIterator<COLUMNS_NUM;Local_u8ColIterator++)
		{
			
			Local_u8ErrorState=DIO_enuSetPinValue(Local_u8ArrColumnsPorts[Local_u8ColIterator],Local_u8ArrColumnsPins[Local_u8ColIterator],DIO_u8LOW);
			for(Local_u8RowIterator=0;Local_u8RowIterator<ROWS_NUM;Local_u8RowIterator++)
			{
			
				Local_u8ErrorState=DIO_enuGetPinValue(Local_u8ArrRowsPorts[Local_u8RowIterator],Local_u8ArrRowsPins[Local_u8RowIterator],&Local_u8PinState);

			
				if(Local_u8PinState==DIO_u8LOW)
				{

					_delay_ms(10);
					Local_u8ErrorState=DIO_enuGetPinValue(Local_u8ArrRowsPorts[Local_u8RowIterator],Local_u8ArrRowsPins[Local_u8RowIterator],&Local_u8PinState);
					if(Local_u8PinState==DIO_u8LOW)
					{

					
					while(Local_u8PinState==DIO_u8LOW)
					{
						Local_u8ErrorState=DIO_enuGetPinValue(Local_u8ArrRowsPorts[Local_u8RowIterator],Local_u8ArrRowsPins[Local_u8RowIterator],&Local_u8PinState);
					}

			
					*Copy_pu8PressedKey=Local_Au8KeyValues[Local_u8RowIterator][Local_u8ColIterator];
					return Local_u8ErrorState=ES_OK;
					}
				}
			}

			Local_u8ErrorState=DIO_enuSetPinValue(Local_u8ArrColumnsPorts[Local_u8ColIterator],Local_u8ArrColumnsPins[Local_u8ColIterator],DIO_u8HIGH);
		}

	}
	else
	{
		Local_u8ErrorState=ES_NULL_POINTER;
	}
	return Local_u8ErrorState;
}