/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  HAL              *******************/
/*******************    SWC:    Servo            *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
/*******************************************************************/


#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"

#include "../../MCAL/TIMER1/Timer1_interface.h"

#include "SERVOMOTOR_priv.h"
#include "SERVOMOTOR_config.h"
#include "SERVOMOTOR_int.h"

void 	Servo_voidInit(void)
{
#if SERVO_MODE_TOP_TICKS >=0 && SERVO_MODE_TOP_TICKS <= MAX_VALUE_16_BIT
	Timer1_enuSetCounterTopValue(SERVO_MODE_TOP_TICKS);
#else
#error "Wrong Configuration of FAST_PWM_ICR1"
#endif

}
ES_t	Servo_enuSetAngle(u8 Copy_u8RequiredAngle, u8 Copy_u8Channel)
{
	ES_t Local_enuErrorState = ES_NOK;

	u16  Local_u16RequiredTicks = ((((u32)(SERVO_MODE_TOP_TICKS)*Copy_u8RequiredAngle) + (180*(u32)SERVO_MODE_TOP_TICKS))/3600);
	if(Copy_u8RequiredAngle>= 0 && Copy_u8RequiredAngle <= 180)
	{

		switch(Copy_u8Channel)
		{
		case CHANNEL_OC1A : Timer1_enuSetRequiredTicks(Local_u16RequiredTicks, CHANNEL_A); break;
		case CHANNEL_OC1B : Timer1_enuSetRequiredTicks(Local_u16RequiredTicks, CHANNEL_B); break;
		default : Local_enuErrorState = ES_NOK;
		}

	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

