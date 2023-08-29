/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  MCAL             *******************/
/*******************    SWC:    TWI              *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
/*******************************************************************/

#include "../../LIB/stdTypes.h"
#include "TWI_priv.h"
#include "TWI_config.h"
#include "TWI_int.h"

void TWI_voidInit(void)
{
#if 	TWI_MODE == TWI_MASTER
	TWBR = BITRATE(TWI_CLOCK_SPEED);
	#if	 	TWI_PRESCALER == 1UL
		TWI_PRESCALER_1;
	#elif	TWI_PRESCALER == 4UL
		TWI_PRESCALER_4;
	#elif	TWI_PRESCALER == 16UL
		TWI_PRESCALER_16;
	#elif	TWI_PRESCALER == 64UL
		TWI_PRESCALER_64;
	#else
	#error "Wrong configuration of TWI_PRESCALER"
	#endif

	#if TWI_NODE_ADDRESS>=TWI_LEASET_POSSIBLE_ADDRESS && TWI_NODE_ADDRESS <= TWI_MOST_POSSIBLE_ADDRESS
		TWAR = TWI_NODE_ADDRESS<<1;
	#else
	#error "Wrong configuration of TWI_NODE_ADDRESS"
	#endif

	TWCR |=(1<<TWCR_TWEN);					//Enable TWI

#elif 	TWI_MODE == TWI_SLAVE
	#if TWI_NODE_ADDRESS>=TWI_LEASET_POSSIBLE_ADDRESS && TWI_NODE_ADDRESS <= TWI_MOST_POSSIBLE_ADDRESS
		TWAR = TWI_NODE_ADDRESS<<1;
	#else
	#error "Wrong configuration of TWI_NODE_ADDRESS"
	#endif
	TWCR |=(1<<TWCR_TWEN);					//Enable TWI
#else
#error "Wrong configuration of TWI_MODE"
#endif

}

TWI_ErrorState TWI_enuSendStartCondition(void)
{
	TWI_ErrorState Local_enuErrorState = TWI_noErrors;
	TWCR = (1<<TWCR_TWINT)|(1<<TWCR_TWSTA)|(1<<TWCR_TWEN);  //clearing the flag and sending start condition
	TWI_WAIT_UNTIL_FLAG_IS_RAISED;

	if(!TWI_CHECK_STATUS(TWI_START_CONDITION_STATUS))
	{
		Local_enuErrorState = TWI_StartConditionError;
	}
	else
	{
		//Nothing to do
	}

	return Local_enuErrorState;
}

TWI_ErrorState TWI_enuSendRepeatedStartCondition(void)
{
	TWI_ErrorState Local_enuErrorState = TWI_noErrors;
	TWCR = (1<<TWCR_TWINT)|(1<<TWCR_TWSTA)|(1<<TWCR_TWEN);  //clearing the flag and sending start condition
	TWI_WAIT_UNTIL_FLAG_IS_RAISED;

	if(!TWI_CHECK_STATUS(TWI_REPEATED_START_STATUS))
	{

		Local_enuErrorState = TWI_RepeatedStartError;
	}
	else
	{
		//Nothing to do
	}

	return Local_enuErrorState;
}

TWI_ErrorState TWI_enuSendSlaveAddress(u8 Copy_u8SlaveAddress , u8 Copy_u8Operation)
{
	TWI_ErrorState Local_enuErrorState = TWI_noErrors;

	TWDR = Copy_u8SlaveAddress<<1 | Copy_u8Operation;	//the slave address ORed with operation(read or write)
	TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN);  //clearing the flag
	TWI_WAIT_UNTIL_FLAG_IS_RAISED;

	if(Copy_u8Operation == TWI_WRITE && !TWI_CHECK_STATUS(TWI_ADDRESS_WRITE_ACK))
	{
		Local_enuErrorState = TWI_SlaveAddressWithWriteError;
	}
	else if(Copy_u8Operation == TWI_READ && !TWI_CHECK_STATUS(TWI_ADDRESS_READ_ACK))
	{
		Local_enuErrorState = TWI_SlaveAddressWithReadError;
	}
	else
	{
		//Nothing to do
	}

	return Local_enuErrorState;
}

TWI_ErrorState TWI_enuWriteDataByte(u8 Copy_u8DataByte)
{
	TWI_ErrorState Local_enuErrorState = TWI_noErrors;

	TWDR = Copy_u8DataByte;
	TWCR = (1<<TWCR_TWINT)|(1<<TWCR_TWEN);		 //clearing the flag
	TWI_WAIT_UNTIL_FLAG_IS_RAISED;

	if(!TWI_CHECK_STATUS(TWI_DATA_BYTE_TRANSMITTED_ACK))
	{
		Local_enuErrorState = TWI_MasterWriteByteError;
	}
	else
	{
		//Nothing to do
	}

	return Local_enuErrorState;
}

TWI_ErrorState TWI_enuReadDataByte(u8 *ptr_u8DataBuffer)
{
	TWI_ErrorState Local_enuErrorState = TWI_noErrors;

	TWCR = (1<<TWCR_TWINT)|(1<<TWCR_TWEN); //clearing the flag firstly in order to put the data into TWDR
	TWI_WAIT_UNTIL_FLAG_IS_RAISED;
	*ptr_u8DataBuffer = TWDR;
	if(!(TWI_CHECK_STATUS(TWI_DATA_BYTE_RECEIVED_ACK) || TWI_CHECK_STATUS(TWI_DATA_BYTE_RECEIVED_NOTACK)))
	{
		Local_enuErrorState = TWI_MasterReadByteError;
	}
	else
	{

		//Nothing to do
	}

	return Local_enuErrorState;
}

void TWI_voidStopCondition(void)
{
	TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN) | (1 << TWCR_TWSTO); //clearing the flag and sending stop condition
}

TWI_ErrorState TWI_enuCheckMyAddress(void)
{
	TWI_ErrorState Local_enuErrorState = TWI_noErrors;

	TWI_ENABLE_ACK;
	TWCR = (1<<TWCR_TWINT)|(1<<TWCR_TWEN);  //clearing the flag
	TWI_WAIT_UNTIL_FLAG_IS_RAISED;
	if(!(TWI_CHECK_STATUS(TWI_ADDRESS_RECEIVED_WRITE) || TWI_CHECK_STATUS(TWI_ADDRESS_RECEIVED_READ)))
	{
		Local_enuErrorState = TWI_CheckAddressError;
	}
	else
	{
		//Nothing to do
	}

	return Local_enuErrorState;
}


