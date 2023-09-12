/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  MCAL             *******************/
/*******************    SWC:    TWI              *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
/*******************************************************************/
#ifndef MCAL_TWI_TWI_CONFIG_H_
#define MCAL_TWI_TWI_CONFIG_H_

/*	OPTIONS
 *
 * 	TWI_SLAVE
 * 	TWI_MASTER
 */


#define TWI_MODE		TWI_SLAVE


#define TWI_CLOCK_SPEED	100000UL		//From 100k to 400k

/*	OPTIONS
 *
 * 	1
 * 	4
 * 	16
 * 	64
 */

#define TWI_PRESCALER	1UL


#define TWI_NODE_ADDRESS		5 	// from 1 to 128 ,but make sure it is not reserved(MSBs = 1111)


#endif /* MCAL_TWI_TWI_CONFIG_H_ */
