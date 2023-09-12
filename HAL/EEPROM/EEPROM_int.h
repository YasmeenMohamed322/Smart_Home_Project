/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  HAL              *******************/
/*******************    SWC:    EEPROM           *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
/*******************************************************************/
#ifndef HAL_EEPROM_EEPROM_INT_H_
#define HAL_EEPROM_EEPROM_INT_H_

//This driver is implemented for 24C08 chip

//Options for Copy_u8MemorySelection
#define EEPROM_FIRST_MEMORY			10
#define EEPROM_SECOND_MEMORY		11
//you can choose from 0 to 3 for Copy_u8blockSelection
//you can choose from 0 to 255 for Copy_u8MemoryLocation

void EEPROM_voidWriteByte(u8 Copy_u8DataByte, u8 Copy_u8MemorySelection, u8 Copy_u8blockSelection, u8 Copy_u8MemoryLocation);
u8 EEPROM_u8ReadByte(u8 Copy_u8MemorySelection, u8 Copy_u8blockSelection, u8 Copy_u8MemoryLocation);

#endif /* HAL_EEPROM_EEPROM_INT_H_ */
