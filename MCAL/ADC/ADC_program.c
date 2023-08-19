/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  MCAL             *******************/
/*******************    SWC:    ADC              *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/

#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"

#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"


void (*ADC_pfunInterrupt)(void) = 	NULL;


void	ADC_voidInit(void)
{
	ADCSRA |=(1<<ADCSRA_ADEN);															//Enable the ADC//
#if		ADC_REFERENCE_VOLATGE == AREF                                  					//Choosing the Voltage reference//
	ADMUX &=~(0xc0);                                              						//////////////////////////////////
#elif	ADC_REFERENCE_VOLATGE == AVCC                          					     	//////////////////////////////////
	ADMUX &=~(0xc0);                                                					//////////////////////////////////
	ADMUX |=(0x80);                                                 					//////////////////////////////////
#elif	ADC_REFERENCE_VOLATGE == INTERNAL                           					//////////////////////////////////
	ADMUX |=(0xc0);                                                 					//////////////////////////////////
#else 																					//////////////////////////////////
#error "Wrong configuration! Please check the ADC_REFERENCE_VOLATGE"					//////////////////////////////////
#endif                                                              					//////////////////////////////////


#if	ADC_PRESCALAR_DIVSION_FACTOR >= 1 && ADC_PRESCALAR_DIVSION_FACTOR <=7               //Choosing the Prescalar//
	ADCSRA &=~(0x07);                                                                   //////////////////////////
	ADCSRA |= ADC_PRESCALAR_DIVSION_FACTOR;                                             //////////////////////////
#else                                                                                   //////////////////////////
#error "Wrong configuration! Please check the ADC_PRESCALAR_DIVSION_FACTOR"             //////////////////////////
#endif                                                                                  //////////////////////////


#if		ADC_READING_RESOULTION == EIGHT_BIT_REOULSTION                                  //Choosing between right and left adjustment//
	ADMUX |=(1<<ADMUX_ADLAR);                                                           //////////////////////////////////////////////
#elif	ADC_READING_RESOULTION == TEN_BIT_REOULSTION                                    //////////////////////////////////////////////
	ADMUX &=~(1<<ADMUX_ADLAR);                                                          //////////////////////////////////////////////
#else                                                                                   //////////////////////////////////////////////
#error "Wrong configuration! Please check the ADC_READING_RESOULTION"                   //////////////////////////////////////////////
#endif

}

u16 ADC_u16Read()
{
	u16 Local_u16Result = 0;

	if(ADC_READING_RESOULTION == EIGHT_BIT_REOULSTION)
		{
			Local_u16Result = ADCH;
		}
		else if(ADC_READING_RESOULTION == TEN_BIT_REOULSTION)
		{
			Local_u16Result =ADCL;
			Local_u16Result |= ((u16)ADCH<<8);
		}
	return Local_u16Result;
}
ES_t ADC_enuSelectChannel(u8 Copy_u8Channel)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_u8Channel<= 7 && Copy_u8Channel >= 0)
	{
		ADMUX &=~(0x1f);																	//seletion of the channel//
		ADMUX |=(Copy_u8Channel);															///////////////////////////
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}

u16 ADC_u16PollingRead(u8 Copy_u8Channel)
{

	ADC_enuSelectChannel(Copy_u8Channel);												//Selection of the channel
	ADCSRA |=(1<<ADCSRA_ADSC);															//start conversion//
	while(((ADCSRA>>ADCSRA_ADIF)&1) == 0){}												//poling
	ADCSRA |=(1<<ADCSRA_ADIF);															//clearing the flag

	return ADC_u16Read();

}

void ADC_voidEnableAutoTriggeringMode()
{
	SFIOR &=~(0xe0);						//clearing the 3 bits of auto triggering
	SFIOR |=(ADC_AUTO_TRIGGER_SOURCE<<5);	//choosing the triggering source
	ADCSRA |=(1<<ADCSRA_ADATE);				//enable the triggering source
	ADCSRA |=(1<<ADCSRA_ADSC);				//start conversion for the first time
	ADCSRA |=(1<<ADCSRA_ADIE);				//enable specific interrupt
}

ES_t __vector_16 (void) __attribute__((signal));
ES_t __vector_16 (void)
{
	ES_t Local_enuErrorState = ES_NOK;
	if(ADC_pfunInterrupt == NULL)
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	else
	{
		ADC_pfunInterrupt();
		Local_enuErrorState = ES_OK;
	}
	return Local_enuErrorState;
}

ES_t ADC_enuCallback(void(*pfunc))
{
	ES_t Local_enuErrorState = ES_NOK;
	if(pfunc == NULL)
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	else
	{
		ADC_pfunInterrupt = pfunc;
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}


