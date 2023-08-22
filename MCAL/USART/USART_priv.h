/*
 * USART_priv.h
 *
 *  Created on: Aug 16, 2023
 *      Author: user
 */

#ifndef MCAL_USART_USART_PRIV_H_
#define MCAL_USART_USART_PRIV_H_

//Registers
#define UCSRC                            *((volatile u8*)0x40)
#define UBRRH                            UCSRC
#define URSEL                                     7
#define UMSEL                                     6
#define UPM1                                      5
#define UPM0                                      4
#define USBS                                      3
#define UCSZ1                                     2
#define UCSZ0                                     1
#define UCPOL                                     0


#define UDR                              *((volatile u8*)0x2C)

#define UCSRA                            *((volatile u8*)0x2B)
#define RXC                                       7
#define TXC                                       6
#define UDRE                                      5
#define FE                                        4
#define DOR                                       3
#define PE                                        2
#define U2X                                       1
#define MPCM                                      0

#define UCSRB                            *((volatile u8*)0x2A)
#define RXCIE                                     7
#define TXCIE                                     6
#define UDRIE                                     5
#define RXEN                                      4
#define TXEN                                      3
#define UCSZ2                                     2
#define RXB8                                      1
#define TXB8                                      0

#define UBRRL                            *((volatile u8*)0x29)
//Speed Modes
#define NORMAL                            2
#define DOUBLE                            1

//Data length
#define FIVE_BIT                          5
#define SIX_BIT                           6
#define SEVEN_BIT                         7
#define EIGHT_BIT                         8
#define NINE_BIT                          9

//UART Modes
#define TRANSMITTER                       0
#define RECIEVER                          1
#define TRANSCIEVER                       2

//Parity
#define NO_PARITY                         0
#define EVEN_PARITY                       1
#define ODD_PARITY                        2

//Stop State
#define ONE_STOP_BIT                      1
#define TWO_STOP_BIT                      2

//Clock Modes
#define ASYCH                             0
#define SYCH                              1


//equation for baud rate
#define BAUDEQN(BAUD_RATE)                (u16)((F_CPU/SPEED_MODE*8*BAUD_RATE)-1)


#endif /* MCAL_USART_USART_PRIV_H_ */
