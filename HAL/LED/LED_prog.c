/*
 * LED_prog.c
 *
 *  Created on: Aug 16, 2023
 *      Author: user
 */


#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "LED_priv.h"
#include "LED_config.h"

#include "../../MCAL/DIO/DIO_int.h"

ES_t LED_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;

Local_enuErrorState = DIO_enuSetPinDirection(LED_PORTID,LED_PINID,DIO_u8OUTPUT);
if(LED_CONNECTION == LED_SINK)
{
	if(LED_INITSTATE == LED_ON)
	{
		Local_enuErrorState = DIO_enuSetPinValue(LED_PORTID,LED_PINID,DIO_u8LOW);
	}
	else if(LED_INITSTATE == LED_OFF)
	{
		Local_enuErrorState=DIO_enuSetPinValue(LED_PORTID,LED_PINID,DIO_u8HIGH);
	}
	else
	{
		return ES_OUT_OF_RANGE;
	}
}
else if(LED_CONNECTION == LED_SOURCE)
{
if(LED_INITSTATE == LED_ON)
    {
        Local_enuErrorState = DIO_enuSetPinValue(LED_PORTID,LED_PINID,DIO_u8HIGH);
	 }
	 else if(LED_INITSTATE == LED_OFF)
	 {
	 	Local_enuErrorState = DIO_enuSetPinValue(LED_PORTID,LED_PINID,DIO_u8LOW);
	 }
	 else
	 {
	 	return ES_OUT_OF_RANGE;
	 }
		}
else
{
		return ES_OUT_OF_RANGE;
	}


	return Local_enuErrorState;
}
ES_t LED_enuTurnON(u8 Copy_LedPORT,u8 Copy_LedPIN)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(LED_CONNECTION == LED_SINK)
	{
		 Local_enuErrorState = DIO_enuSetPinValue(Copy_LedPORT,Copy_LedPIN,DIO_u8LOW);
	}
	else if(LED_CONNECTION == LED_SOURCE)
	{
		 Local_enuErrorState = DIO_enuSetPinValue(Copy_LedPORT,Copy_LedPIN,DIO_u8HIGH);
	}
	else
	{
		return ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}
ES_t LED_enuTurnOFF(u8 Copy_LedPORT,u8 Copy_LedPIN)
{
	ES_t Local_enuErrorState = ES_NOK;

		if(LED_CONNECTION == LED_SINK)
		{
			 Local_enuErrorState = DIO_enuSetPinValue(Copy_LedPORT,Copy_LedPIN,DIO_u8HIGH);
		}
		else if(LED_CONNECTION == LED_SOURCE)
		{
			 Local_enuErrorState = DIO_enuSetPinValue(Copy_LedPORT,Copy_LedPIN,DIO_u8LOW);
		}
		else
		{
			return ES_OUT_OF_RANGE;
		}

		return Local_enuErrorState;
}

