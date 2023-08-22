/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  MCAL             *******************/
/*******************    SWC:    Timer0           *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
/*******************************************************************/
#ifndef TIMER1_CONFIG_H_
#define TIMER1_CONFIG_H_


/*	Options for WAVE_GENERATION_MODE		Description
 *
 *	NORMAL
 * 	CTC
 * 	FAST_PWM_8BIT
 * 	FAST_PWM_ICR1								choosing the fast PWM mode with ICR1 as a top value
 * 	ICU
 *
 */
#define	WAVE_GENERATION_MODE		FAST_PWM_ICR1

/*		Options 			Description
 *
 *	 	0            		No clock source (Timer/Counter stopped).
 * 		1                  	source clock (No prescaling)
 * 		2                  	source clock/8 From prescaler
 * 		3                   source clock/64 From prescaler
 * 		4                   source clock/256 From prescaler
 * 		5                   source clock/1024 From prescaler
 * 		6                   External clock source on T0 pin. Clock on falling edge.
 * 		7                   External clock source on T0 pin. Clock on rising edge.
 */
#define	CLOCK_SELECTION		2


/*		Options for non-PWM-Mode	Options for PWM Mode
 *
 *	 	DISCONNECTED           		DISCONNECTED
 * 		TOGGLE                  	INVERTED_MODE
 * 		CLEAR                  		NON_INVERTED_MODE
 * 		SET
 */
#define COMPARE_MATCH_OUTPUT_MODE_OC1A			DISCONNECTED

#define COMPARE_MATCH_VALUE_OC1A			62500		//FROM 0 TO 65535 for Compare match mode

/*		Options for non-PWM-Mode	Options for PWM Mode
 *
 *	 	DISCONNECTED           		DISCONNECTED
 * 		TOGGLE                  	INVERTED_MODE
 * 		CLEAR                   	NON_INVERTED_MODE
 * 		SET
 */
#define COMPARE_MATCH_OUTPUT_MODE_OC1B			DISCONNECTED

#define COMPARE_MATCH_VALUE_OC1B			62500		//FROM 0 TO 65535 for Compare match mode




#endif /* TIMER1_CONFIG_H_ */
