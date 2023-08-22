/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  MCAL             *******************/
/*******************    SWC:    Timer1           *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
/*******************************************************************/
#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

#define CHANNEL_A			10
#define CHANNEL_B			11

void Timer1_voidInit();
ES_t Timer1_enuOverflowSetCallback(void(*pfunISR)(void));
ES_t Timer1_enuSetPreloadValue(u16 Copy_u16PreloadValue);
ES_t Timer1_enuCompareMatchChannelASetCallback(void(*pfunISR)(void));
ES_t Timer1_enuCompareMatchChannelBSetCallback(void(*pfunISR)(void));
ES_t Timer1_PWM_enuGenerationChannelA(u8 Copy_u8DutyCycle);
ES_t Timer1_PWM_enuGenerationChannelB(u8 Copy_u8DutyCycle);
ES_t Timer1_enuServoAngle(u8 Copy_u8RequiredAngle, u8 Copy_u8Channel);
ES_t Timer1_enuSetCounterTopValue(u16 Copy_u8Value); // this function is used in FAST_PWM_ICR1 mode
ES_t Timer1_enuSetRequiredTicks(u16 Copy_u8RequiredTicks, u8 Copy_u8Channel); // this function is used in FAST_PWM_ICR1 mode

#endif /* TIMER1_INTERFACE_H_ */
