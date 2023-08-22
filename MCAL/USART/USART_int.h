/*
 * USART_int.h
 *
 *  Created on: Aug 16, 2023
 *      Author: user
 */

#ifndef MCAL_USART_USART_INT_H_
#define MCAL_USART_USART_INT_H_

ES_t UART_enuInit(void);

ES_t UART_enuSendChar(u8 Copy_u8Data);

ES_t UART_enuRecieveChar(u8 *Copy_u8Data);

ES_t UART_enuSendString(const char* Copy_sData);

ES_t UART_enuRecieveString(char* Copy_sData);


#endif /* MCAL_USART_USART_INT_H_ */
