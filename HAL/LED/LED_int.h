/*
 * LED_int.h
 *
 *  Created on: Aug 16, 2023
 *      Author: user
 */

#ifndef HAL_LED_LED_INT_H_
#define HAL_LED_LED_INT_H_

ES_t LED_enuInit(void);
ES_t LED_enuTurnON(u8 Copy_LedPORT,u8 Copy_LedPIN);
ES_t LED_enuTurnOFF(u8 Copy_LedPORT,u8 Copy_LedPIN);

#endif /* HAL_LED_LED_INT_H_ */
