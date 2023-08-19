/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  MCAL             *******************/
/*******************    SWC:    ADC              *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
/*******************************************************************/
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/*		OPTIONS >> ADC_REFERENCE_VOLATGE					DESCRIPTION
 *
 * 		AREF												Internal Vref turned off
 * 		AVCC												AVCC with external capacitor at AREF pin
 * 		INTERNAL											Internal 2.56V Voltage Reference with external capacitor at AREF pin
 */

#define 	ADC_REFERENCE_VOLATGE							AREF

/*		OPTIONS >> ADC_READING_RESOULTION					DESCRIPTION
 *
 * 		EIGHT_BIT_REOULSTION								The result will be presented in 8 bits
 * 		TEN_BIT_REOULSTION									The result will be presented in 10 bits
 */

#define 	ADC_READING_RESOULTION							TEN_BIT_REOULSTION

/*		OPTIONS >> ADC_PRESCALAR_DIVSION_FACTOR				DESCRIPTION
 *
 * 		1													The system clock will be divided by 2
 * 		2								                    The system clock will be divided by 4
 * 		3									                The system clock will be divided by 8
 * 		4									                The system clock will be divided by 16
 * 		5									                The system clock will be divided by 32
 * 		6									                The system clock will be divided by 64
 * 		7													The system clock will be divided by 128
 */

#define 	ADC_PRESCALAR_DIVSION_FACTOR					7


/*		OPTIONS >> ADC_AUTO_TRIGGER_SOURCE					DESCRIPTION
 *
 * 		FREE_RUNNING_MODE
 * 		ANALOG_COMPARATOR
 * 		EXTERNAL_INTERRUPT_REQUEST0
 * 		TIMER0_COMPARE_MATCH
 * 		TIMER0_OVERFLOW
 * 		TIMER_COMPARE_MATCH_B
 * 		TIMER1_OVERFLOW
 * 		TIMER1_CAPTURE_EVENT
 */

#define 	ADC_AUTO_TRIGGER_SOURCE		EXTERNAL_INTERRUPT_REQUEST0	//this configuration has no effect if ADC_AUTO_TRIGGER is not enabled

#endif /* ADC_CONFIG_H_ */
