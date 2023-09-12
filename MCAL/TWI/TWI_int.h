/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  MCAL             *******************/
/*******************    SWC:    TWI              *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
/*******************************************************************/

#ifndef MCAL_TWI_TWI_INT_H_
#define MCAL_TWI_TWI_INT_H_

typedef enum
{
	TWI_noErrors =1,
	TWI_StartConditionError,
	TWI_RepeatedStartError,
	TWI_SlaveAddressWithWriteError,
	TWI_SlaveAddressWithReadError,
	TWI_MasterWriteByteError,
	TWI_MasterReadByteError,
	TWI_CheckAddressError,


}TWI_ErrorState;

#define	TWI_READ	1
#define TWI_WRITE	0


void TWI_voidInit(void);
TWI_ErrorState TWI_enuSendStartCondition(void);
TWI_ErrorState TWI_enuSendRepeatedStartCondition(void);

/* OPTIONS FOR Copy_u8Operation
 *
 * TWI_READ
 * TWI_WRITE
 *
 */
TWI_ErrorState TWI_enuSendSlaveAddress(u8 Copy_u8SlaveAddress , u8 Copy_u8Operation);
TWI_ErrorState TWI_enuWriteDataByte(u8 Copy_u8DataByte);
TWI_ErrorState TWI_enuReadDataByte(u8 *ptr_u8DataBuffer);
void TWI_voidStopCondition(void);
TWI_ErrorState TWI_enuCheckMyAddress(void);

#endif /* MCAL_TWI_TWI_INT_H_ */
