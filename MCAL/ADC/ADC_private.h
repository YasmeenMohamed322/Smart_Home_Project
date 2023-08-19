/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  MCAL             *******************/
/*******************    SWC:    ADC              *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADMUX						*((volatile u8*) 0x27) 		//ADC Multiplexer Selection Register

#define ADMMUX_REFS1				7							//Reference Selection Bits
#define ADMMUX_REFS2				6							//Reference Selection Bits
#define AREF						10							//Option in the configuration of ADC_REFERENCE_VOLATGE
#define AVCC						11							//Option in the configuration of ADC_REFERENCE_VOLATGE
#define INTERNAL					12							//Option in the configuration of ADC_REFERENCE_VOLATGE


#define ADMUX_ADLAR					5							//ADC Left Adjust Result
#define EIGHT_BIT_REOULSTION 		10							//Option in the configuration of ADC_READING_RESOULTION
#define TEN_BIT_REOULSTION 			11							//Option in the configuration of ADC_READING_RESOULTION

#define ADMUX_MUX4					4							//Analog Channel and Gain Selection Bits
#define ADMUX_MUX3					3                           //Analog Channel and Gain Selection Bits
#define ADMUX_MUX2					2                           //Analog Channel and Gain Selection Bits
#define ADMUX_MUX1					1                           //Analog Channel and Gain Selection Bits
#define ADMUX_MUX0					0                           //Analog Channel and Gain Selection Bits

//##################################################################################################################//
//##################################################################################################################//

#define ADCSRA						*((volatile u8*) 0x26) 		//ADC Multiplexer Selection Register

#define ADCSRA_ADEN					7							//ADC Enable

#define ADCSRA_ADSC					6							//ADC Start Conversion

#define ADCSRA_ADATE				5							//ADC Auto Trigger Enable

#define ADCSRA_ADIF					4							//ADC Interrupt Flag

#define ADCSRA_ADIE					3							//ADC Interrupt Enable

#define ADCSRA_ADPS2				2						    //ADC Prescaler Select Bits
#define ADCSRA_ADPS1				1						    //ADC Prescaler Select Bits
#define ADCSRA_ADPS0				0						    //ADC Prescaler Select Bits

//##################################################################################################################//
//##################################################################################################################//

#define ADCL						*((volatile u8*) 0x24) 		//The ADC Data Register
#define ADCH						*((volatile u8*) 0x25) 		//The ADC Data Register

//##################################################################################################################//
//##################################################################################################################//

#define SFIOR						*((volatile u8*) 0x50) 		//Special FunctionIO Register

#define SFIOR_ADTS2					7
#define SFIOR_ADTS1					6
#define SFIOR_ADTS0					5

#define	FREE_RUNNING_MODE			0
#define	ANALOG_COMPARATOR			1
#define	EXTERNAL_INTERRUPT_REQUEST0	2
#define	TIMER0_COMPARE_MATCH		3
#define	TIMER0_OVERFLOW				4
#define	TIMER_COMPARE_MATCH_B		5
#define	TIMER1_OVERFLOW				6
#define	TIMER1_CAPTURE_EVENT		7


#endif /* ADC_PRIVATE_H_ */
