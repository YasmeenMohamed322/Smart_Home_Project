/*
 * DCMOTOR_int.h
 *
 *  Created on: Aug 16, 2023
 *      Author: user
 */

#ifndef HAL_DCMOTOR_DCMOTOR_INT_H_
#define HAL_DCMOTOR_DCMOTOR_INT_H_

ES_t DCMOTOR_enuInit(void);

ES_t DCMOTOR_enuChangeDirection(u8 Copy_u8Direction);

ES_t DCMOTOR_enuSpeed(u8 Copy_u8Speed);

ES_t DCMOTOR_enuStop();

#define ROTATE_CLKWISE                           0
#define ROTATE_ANTI_CLKWISE                      1

#endif /* HAL_DCMOTOR_DCMOTOR_INT_H_ */
