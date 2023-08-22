/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  MCAL             *******************/
/*******************    SWC:    Timer0           *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
/*******************************************************************/

#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"

#include "Timer1_private.h"
#include "Timer1_config.h"
#include "Timer1_interface.h"


void (*Timer1_pfunOverflowInterrupt)(void) = NULL;
void (*Timer1_pfunCompareMatchInterruptChannelA)(void) = NULL;
void (*Timer1_pfunCompareMatchInterruptChannelB)(void) = NULL;
void (*Timer1_pfunICU)(void) = NULL;



void Timer1_voidInit()
{

#if	WAVE_GENERATION_MODE	== NORMAL

	TCCR1A &=~(1<<TCCR1A_WGM10);			//choosing the Normal mode
	TCCR1A &=~(1<<TCCR1A_WGM11);            //choosing the Normal mode
	TCCR1B &=~(1<<TCCR1B_WGM12);            //choosing the Normal mode
	TCCR1B &=~(1<<TCCR1B_WGM13);            //choosing the Normal mode

	TIMSK |=(1<<TIMSK_TOIE1);				//Overflow Interrupt Enable



#elif	WAVE_GENERATION_MODE	== CTC

	TCCR1A &=~(1<<TCCR1A_WGM10);			//choosing the Compare Match mode
	TCCR1A &=~(1<<TCCR1A_WGM11);            //choosing the Compare Match mode
	TCCR1B |=(1<<TCCR1B_WGM12);      	    //choosing the Compare Match mode
	TCCR1B &=~(1<<TCCR1B_WGM13);            //choosing the Compare Match mode

	#if	 	COMPARE_MATCH_OUTPUT_MODE_OC1A 	== DISCONNECTED

	TCCR1A &=~(1<<TCCR1A_COM1A0);
	TCCR1A &=~(1<<TCCR1A_COM1A1);

	#else
	#error "Wrong configuration of COMPARE_MATCH_OUTPUT_MODE_OC1A"
	#endif

	#if	 	COMPARE_MATCH_OUTPUT_MODE_OC1B 	== DISCONNECTED

	TCCR1A &=~(1<<TCCR1A_COM1B0);
	TCCR1A &=~(1<<TCCR1A_COM1B1);

	#else
	#error "Wrong configuration of COMPARE_MATCH_OUTPUT_MODE_OC1A"
	#endif

	#if		COMPARE_MATCH_VALUE_OC1A >= 0 && COMPARE_MATCH_VALUE_OC1A <= MAX_VALUE_16_BIT

	COMPARE_MATCH_VALUE_CHANNEL_A =	COMPARE_MATCH_VALUE_OC1A;

	#else
	#error "Wrong configuration of COMPARE_MATCH_VALUE_OC1A"
	#endif

	#if		COMPARE_MATCH_VALUE_OC1B >= 0 && COMPARE_MATCH_VALUE_OC1B <= MAX_VALUE_16_BIT

	COMPARE_MATCH_VALUE_CHANNEL_B =	COMPARE_MATCH_VALUE_OC1B;

	#else
	#error "Wrong configuration of COMPARE_MATCH_VALUE_OC1B"
	#endif

	TIMSK |=(1<<TIMSK_OCIE1A);				//Output Compare A Match Interrupt Enable
	TIMSK |=(1<<TIMSK_OCIE1B);				//Output Compare B Match Interrupt Enable

#elif	WAVE_GENERATION_MODE	==	FAST_PWM_8BIT

	TCCR1A |=(1<<TCCR1A_WGM10);				//choosing the Fast PWM mode
	TCCR1A &=~(1<<TCCR1A_WGM11);            //choosing the Fast PWM mode
	TCCR1B |=(1<<TCCR1B_WGM12);      	    //choosing the Fast PWM mode
	TCCR1B &=~(1<<TCCR1B_WGM13);            //choosing the Fast PWM mode


	#if	COMPARE_MATCH_OUTPUT_MODE_OC1A	== NON_INVERTED_MODE

	TCCR1A	|=(1<<TCCR1A_COM1A1);
	TCCR1A	&=~(1<<TCCR1A_COM1A0);

	#else
	#error "Wrong configuration of COMPARE_MATCH_OUTPUT_MODE_OC1A"
	#endif

	#if	COMPARE_MATCH_OUTPUT_MODE_OC1A	== NON_INVERTED_MODE

	TCCR1A	|=(1<<TCCR1A_COM1B1);
	TCCR1A	&=~(1<<TCCR1A_COM1B0);

	#else
	#error "Wrong configuration of COMPARE_MATCH_OUTPUT_MODE_OC1B"
	#endif



#elif	WAVE_GENERATION_MODE	==		FAST_PWM_ICR1

	TCCR1A &=~(1<<TCCR1A_WGM10);				 //choosing the fast PWM mode with ICR1 as a top
	TCCR1A |=(1<<TCCR1A_WGM11);           		 //choosing the fast PWM mode with ICR1 as a top
	TCCR1B |=(1<<TCCR1B_WGM12);      	   		 //choosing the fast PWM mode with ICR1 as a top
	TCCR1B |=(1<<TCCR1B_WGM13);           		 //choosing the fast PWM mode with ICR1 as a top

	TCCR1A	|=(1<<TCCR1A_COM1A1);				 //non inverted mode
	TCCR1A	&=~(1<<TCCR1A_COM1A0);				 ///////////////////

#elif	WAVE_GENERATION_MODE	==		ICU

	TCCR1A &=~(1<<TCCR1A_WGM10);			//choosing the Normal mode
	TCCR1A &=~(1<<TCCR1A_WGM11);            //choosing the Normal mode
	TCCR1B &=~(1<<TCCR1B_WGM12);            //choosing the Normal mode
	TCCR1B &=~(1<<TCCR1B_WGM13);            //choosing the Normal mode

	TIMSK |=(1<<TIMSK_TOIE1);				//Overflow Interrupt Enable

	void Timer1_voidICRisingEdge();


#else
#error "Wrong configuration of WAVE_GENERATION_MODE"
#endif

#if CLOCK_SELECTION >=0 && CLOCK_SELECTION <= 7
	TCCR1B 	&=~(0x07);								//select the clock
	TCCR1B	|= CLOCK_SELECTION;						//select the clock
#else
#error "Wrong Configuration of CLOCK_SELECTION"
#endif


}

ES_t __vector_9 (void) __attribute__((signal));
ES_t __vector_9	(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Timer1_pfunOverflowInterrupt == NULL)
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	else
	{
	 Timer1_pfunOverflowInterrupt();
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES_t Timer1_enuOverflowSetCallback(void(*pfunISR)(void))
{
	ES_t Local_enuErrorState = ES_NOK;

	if(pfunISR == NULL)
	{
		Local_enuErrorState =  ES_NULL_POINTER;
	}
	else
	{
		Timer1_pfunOverflowInterrupt = pfunISR;

		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES_t Timer1_enuSetPreloadValue(u16 Copy_u16PreloadValue)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_u16PreloadValue>= 0 && Copy_u16PreloadValue <= MAX_VALUE_16_BIT)
	{
		TIMER_PRELOAD_VALUE = Copy_u16PreloadValue;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}


ES_t __vector_7 (void) __attribute__((signal));
ES_t __vector_7	(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Timer1_pfunCompareMatchInterruptChannelA == NULL)
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	else
	{
		Timer1_pfunCompareMatchInterruptChannelA();
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES_t Timer1_enuCompareMatchChannelASetCallback(void(*pfunISR)(void))
{
	ES_t Local_enuErrorState = ES_NOK;

	if(pfunISR == NULL)
	{
		Local_enuErrorState =  ES_NULL_POINTER;
	}
	else
	{
		Timer1_pfunCompareMatchInterruptChannelA = pfunISR;

		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES_t __vector_8 (void) __attribute__((signal));
ES_t __vector_8	(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Timer1_pfunCompareMatchInterruptChannelB == NULL)
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	else
	{
		Timer1_pfunCompareMatchInterruptChannelB();
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}


ES_t 	Timer1_enuCompareMatchChannelBSetCallback(void(*pfunISR)(void))
{
	ES_t Local_enuErrorState = ES_NOK;

	if(pfunISR == NULL)
	{
		Local_enuErrorState =  ES_NULL_POINTER;
	}
	else
	{
		Timer1_pfunCompareMatchInterruptChannelB = pfunISR;

		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES_t	Timer1_PWM_enuGenerationChannelA(u8 Copy_u8DutyCycle)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_u8DutyCycle >= 0 && Copy_u8DutyCycle <= 100)
	{
		Local_enuErrorState = ES_OK;

		if(COMPARE_MATCH_OUTPUT_MODE_OC1A == NON_INVERTED_MODE)
		{
			COMPARE_MATCH_VALUE_CHANNEL_A = (Copy_u8DutyCycle*256)/100;
		}
		else if(COMPARE_MATCH_OUTPUT_MODE_OC1A == INVERTED_MODE)
		{

		}
		else
		{
			Local_enuErrorState = ES_NOK;
		}
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t	Timer1_PWM_enuGenerationChannelB(u8 Copy_u8DutyCycle)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_u8DutyCycle >= 0 && Copy_u8DutyCycle <= 100)
	{
		Local_enuErrorState = ES_OK;

		if(COMPARE_MATCH_OUTPUT_MODE_OC1B == NON_INVERTED_MODE)
		{
			COMPARE_MATCH_VALUE_CHANNEL_B = (Copy_u8DutyCycle*256)/100;
		}
		else if(COMPARE_MATCH_OUTPUT_MODE_OC1B == INVERTED_MODE)
		{

		}
		else
		{
			Local_enuErrorState = ES_NOK;
		}
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t Timer1_enuSetCounterTopValue(u16 Copy_u8Value)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_u8Value>=0 && Copy_u8Value <= MAX_VALUE_16_BIT)
	{
		ICR_VALUE = Copy_u8Value;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}
ES_t Timer1_enuSetRequiredTicks(u16 Copy_u8RequiredTicks, u8 Copy_u8Channel)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(Copy_u8Channel == CHANNEL_A)
	{
		if(Copy_u8RequiredTicks>=0 && Copy_u8RequiredTicks <= MAX_VALUE_16_BIT)
		{
			COMPARE_MATCH_VALUE_CHANNEL_A = Copy_u8RequiredTicks;
		}
		else
		{
			Local_enuErrorState = ES_OUT_OF_RANGE;
		}
	}
	else if(Copy_u8Channel == CHANNEL_B)
	{
		if(Copy_u8RequiredTicks>=0 && Copy_u8RequiredTicks <= MAX_VALUE_16_BIT)
		{
			COMPARE_MATCH_VALUE_CHANNEL_B = Copy_u8RequiredTicks;
		}
		else
		{
			Local_enuErrorState = ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}
void Timer1_voidICRisingEdge()
{
	TCCR1B |=(1<<TCCR1B_ICES1);
}
void Timer1_voidICFallingEdge()
{
	TCCR1B &=~(1<<TCCR1B_ICES1);
}

ES_t __vector_6 (void) __attribute__((signal));
ES_t __vector_6	(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Timer1_pfunICU == NULL)
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	else
	{
		Timer1_pfunICU();
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}


ES_t Timer1_enuICUSetCallback(void(*pfunISR)(void))
{
	ES_t Local_enuErrorState = ES_NOK;

	if(pfunISR == NULL)
	{
		Local_enuErrorState =  ES_NULL_POINTER;
	}
	else
	{
		Timer1_pfunICU = pfunISR;

		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}


void Timer1_voidICU(u16 *pu16PeriodTicks, u16 *pu16OnTicks)
{
	static u8 Local_u8Counter = 0;
	u16 Local_u16Reading1 = 0,Local_u16Reading2 = 0,Local_u16Reading3 = 0;
	u16 Local_u16PeriodTicks = 0, Local_u16OnTicks = 0;
	Local_u8Counter++;
	if(Local_u8Counter == 1)
	{
		Local_u16Reading1 = ICR_VALUE;

	}
	else if(Local_u8Counter == 2)
	{
		Local_u16Reading2 = ICR_VALUE;
		Local_u16PeriodTicks = Local_u16Reading2 - Local_u16Reading1;
		Timer1_voidICFallingEdge();
	}
	else if (Local_u8Counter == 3)
	{
		Local_u16Reading3 = ICR_VALUE;
		Local_u16OnTicks = Local_u16Reading3 - Local_u16PeriodTicks;
		Timer1_voidICRisingEdge();
		Local_u8Counter = 0;

	}
}
