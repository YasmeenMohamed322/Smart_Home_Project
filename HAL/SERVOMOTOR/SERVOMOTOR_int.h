/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  HAL              *******************/
/*******************    SWC:    Servo            *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
/*******************************************************************/
#ifndef HAL_SERVOMOTOR_SERVOMOTOR_INT_H_
#define HAL_SERVOMOTOR_SERVOMOTOR_INT_H_

#define 	CHANNEL_OC1A			10
#define 	CHANNEL_OC1B			11


void 	Servo_voidInit(void);
ES_t	Servo_enuSetAngle(u8 Copy_u8RequiredAngle, u8 Copy_u8Channel);
#endif /* HAL_SERVOMOTOR_SERVOMOTOR_INT_H_ */
