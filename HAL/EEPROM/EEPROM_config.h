/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  HAL              *******************/
/*******************    SWC:    EEPROM           *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
/*******************************************************************/
#ifndef HAL_EEPROM_EEPROM_CONFIG_H_
#define HAL_EEPROM_EEPROM_CONFIG_H_

//this driver is implemented for 24C08

/*	Options		Description
 *
 * 	GND			Ground
 * 	VCC			5V
 *
 */
//Note: if you put this as GND so the second must be VCC and vice versa
#define EEPROM_FIRST_MEMORY_ENABLE_BIT		GND
#define EEPROM_SECOND_MEMORY_ENABLE_BIT		VCC


#endif /* HAL_EEPROM_EEPROM_CONFIG_H_ */
