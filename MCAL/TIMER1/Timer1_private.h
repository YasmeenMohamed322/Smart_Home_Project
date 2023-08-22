/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  MCAL             *******************/
/*******************    SWC:    Timer1           *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
/*******************************************************************/

#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

#define TCCR1A								*((volatile u8*) 0x4F)			//Timer/Counter1 Control Register A – TCCR1A
#define TCCR1A_COM1A1						7								//Compare Output Mode for Channel A
#define TCCR1A_COM1A0						6								//Compare Output Mode for Channel A
#define TCCR1A_COM1B1						5								//Compare Output Mode for Channel B
#define TCCR1A_COM1B0						4								//Compare Output Mode for Channel B
#define DISCONNECTED						10								//configuration of COMPARE_MATCH_MODE_CHANNEL
#define TOGGLE								11								//configuration of COMPARE_MATCH_MODE_CHANNEL
#define CLEAR								12								//configuration of COMPARE_MATCH_MODE_CHANNEL
#define SET									13								//configuration of COMPARE_MATCH_MODE_CHANNEL
#define INVERTED_MODE						14								//configuration of COMPARE_MATCH_MODE_CHANNEL
#define NON_INVERTED_MODE					15								//configuration of COMPARE_MATCH_MODE_CHANNEL
#define FAST_PWM_ICR1						16								//configuration of COMPARE_MATCH_MODE_CHANNEL
#define ICU									17								//configuration of COMPARE_MATCH_MODE_CHANNEL



#define TCCR1A_WGM11						1								//Waveform Generation Mode
#define TCCR1A_WGM10						0								//Waveform Generation Mode
#define CTC									10
#define NORMAL								11


#define TCCR1B								*((volatile u8*) 0x4E)			//Timer/Counter1 Control Register B – TCCR1B
#define TCCR1B_ICNC1						7								//Input Capture Noise Canceler
#define TCCR1B_ICES1						6								//Input Capture Edge Select

#define TCCR1B_WGM13						4								//Waveform Generation Mode
#define TCCR1B_WGM12						3								//Waveform Generation Mode

#define TCCR1B_CS12							2								//Clock Select
#define TCCR1B_CS11							1								//Clock Select
#define TCCR1B_CS10							0								//Clock Select

#define TIMER_PRELOAD_VALUE					*((volatile u16*)0x4C)			//the timer counter

#define COMPARE_MATCH_VALUE_CHANNEL_A		*((volatile u16*)0x4A)			//Output Compare Register 1 A

#define COMPARE_MATCH_VALUE_CHANNEL_B		*((volatile u16*)0x48)			//Output Compare Register 1 B

#define ICR_VALUE							*((volatile u16*)0x46)			//Input Capture Register 1

#define TIMSK								*((volatile u8*) 0x59)			//Timer/Counter Interrupt Mask Register
#define TIMSK_TICIE1						5								//Input Capture Interrupt Enable

#define TIMSK_OCIE1A						4								//Output Compare A Match Interrupt Enable
#define TIMSK_OCIE1B						3								//Output Compare B Match Interrupt Enable
#define TIMSK_TOIE1							2								//Overflow Interrupt Enable

#define TIFR								*((volatile u8*) 0x58)			//Timer/Counter Interrupt Flag Register
#define TIFR_ICF1							5								//Input Capture Flag
#define TIFR_OCF1A							4
#define TIFR_OCF1B							3
#define TIFR_TOV1							2

#define MAX_VALUE_16_BIT					65535

#endif /* TIMER1_PRIVATE_H_ */
