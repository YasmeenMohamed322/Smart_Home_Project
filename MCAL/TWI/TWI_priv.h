/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  MCAL             *******************/
/*******************    SWC:    TWI              *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
/*******************************************************************/

#ifndef MCAL_TWI_TWI_PRIV_H_
#define MCAL_TWI_TWI_PRIV_H_

#define TWBR								*((volatile u8*)0x20)		//TWI Bit Rate Register

#define TWCR								*((volatile u8*)0x56)		//TWI Control Register
#define TWCR_TWINT							7							//TWI Interrupt Flag
#define TWI_WAIT_UNTIL_FLAG_IS_RAISED		while(!((TWCR>>TWCR_TWINT)&1))
#define TWCR_TWEA							6							//TWI Enable Acknowledge Bit
#define TWI_ENABLE_ACK						TWCR|=(1<<TWCR_TWEA)
#define TWCR_TWSTA							5							//TWI START Condition Bit
#define TWCR_TWSTO							4							//TWI STOP Condition Bit
#define TWCR_TWWC							3							//TWI Write Collision Flag
#define TWCR_TWEN							2							//TWI Enable Bit
#define TWCR_TWIE							0							//TWI Interrupt Enable

#define TWSR								*((volatile u8*)0x21)		//TWI Status Register
#define TWI_CHECK_STATUS(REQUIRED_STATUS)	((REQUIRED_STATUS) == (TWSR&(0xf8)))
#define TWI_START_CONDITION_STATUS			0x08
#define TWI_REPEATED_START_STATUS			0x10
#define TWI_ADDRESS_WRITE_ACK				0x18
#define TWI_ADDRESS_WRITE_NOTACK			0x20
#define TWI_ADDRESS_READ_ACK				0x40
#define TWI_ADDRESS_READ_NOTACK				0x48
#define TWI_DATA_BYTE_TRANSMITTED_NOTACK	0x30
#define TWI_DATA_BYTE_TRANSMITTED_ACK		0x28
#define TWI_DATA_BYTE_RECEIVED_NOTACK		0x58
#define TWI_DATA_BYTE_RECEIVED_ACK			0x50
#define TWI_ADDRESS_RECEIVED_WRITE			0x80
#define TWI_ADDRESS_RECEIVED_READ			0xA8

#define TWI_PRESCALER_1						TWSR &=~(3<<0)
#define TWI_PRESCALER_4						TWSR =	TWSR&(~(1<<1)) |(1<<0)
#define TWI_PRESCALER_16					TWSR =	TWSR&(~(1<<0)) |(1<<1)
#define TWI_PRESCALER_64					TWSR |=(3<<0)

#define TWDR								*((volatile u8*)0x23)		//TWI Data Register

#define TWAR								*((volatile u8*)0x22)		//TWI (Slave) Address Register
#define TWI_LEASET_POSSIBLE_ADDRESS 		1
#define TWI_MOST_POSSIBLE_ADDRESS			128


#define BITRATE(TWI_SPEED)					(F_CPU-16UL*TWI_SPEED)/(2UL*TWI_SPEED*TWI_PRESCALER)


#define TWI_SLAVE	10
#define TWI_MASTER	11

#define	TWI_READ	1
#define TWI_WRITE	0


#endif /* MCAL_TWI_TWI_PRIV_H_ */
