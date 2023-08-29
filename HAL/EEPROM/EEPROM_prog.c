/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  HAL              *******************/
/*******************    SWC:    EEPROM           *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
/*******************************************************************/



#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"

#include "../../MCAL/TWI/TWI_int.h"

#include "EEPROM_priv.h"
#include "EEPROM_config.h"
#include "EEPROM_int.h"


void EEPROM_voidWriteByte(u8 Copy_u8DataByte, u8 Copy_u8MemorySelection, u8 Copy_u8blockSelection, u8 Copy_u8MemoryLocation)
{
	u8 Local_u8Address = 0;
	if(Copy_u8MemorySelection == EEPROM_FIRST_MEMORY)
	{
		Local_u8Address = EEPROM_CONTROL_CODE|(EEPROM_FIRST_MEMORY_ENABLE_BIT<<2)|(Copy_u8blockSelection);
	}
	else if(Copy_u8MemorySelection == EEPROM_SECOND_MEMORY)
	{
		Local_u8Address = EEPROM_CONTROL_CODE|(EEPROM_SECOND_MEMORY_ENABLE_BIT<<2)|(Copy_u8blockSelection);
	}
	if(TWI_noErrors == TWI_enuSendStartCondition())
	{
		if(TWI_noErrors == TWI_enuSendSlaveAddress(Local_u8Address,TWI_WRITE))
		{
			if(TWI_noErrors == TWI_enuWriteDataByte(Copy_u8MemoryLocation))
			{
				if(TWI_noErrors == TWI_enuWriteDataByte(Copy_u8DataByte))
				{
					TWI_voidStopCondition();
				}
			}

		}
	}

}

u8 EEPROM_u8ReadByte(u8 Copy_u8MemorySelection, u8 Copy_u8blockSelection, u8 Copy_u8MemoryLocation)
{
	u8 Local_u8Address = 0, Local_u8Data = 3;

	if(Copy_u8MemorySelection == EEPROM_FIRST_MEMORY)
	{
		Local_u8Address = EEPROM_CONTROL_CODE|(EEPROM_FIRST_MEMORY_ENABLE_BIT<<2)|(Copy_u8blockSelection);
	}
	else if(Copy_u8MemorySelection == EEPROM_SECOND_MEMORY)
	{
		Local_u8Address = EEPROM_CONTROL_CODE|(EEPROM_SECOND_MEMORY_ENABLE_BIT<<2)|(Copy_u8blockSelection);
	}

	if(TWI_noErrors == TWI_enuSendStartCondition())
	{
		if(TWI_noErrors == TWI_enuSendSlaveAddress(Local_u8Address,TWI_WRITE))
		{
			if(TWI_noErrors == TWI_enuWriteDataByte(Copy_u8MemoryLocation))
			{
				if(TWI_noErrors == TWI_enuSendRepeatedStartCondition())
				{
					if(TWI_noErrors == TWI_enuSendSlaveAddress(Local_u8Address,TWI_READ))
					{
							if(TWI_noErrors == TWI_enuReadDataByte(&Local_u8Data))
							{
								TWI_voidStopCondition();
							}

					}

				}
			}

		}
	}


	return Local_u8Data;

}

