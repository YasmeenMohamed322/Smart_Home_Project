/*
 * GIE_prog.c
 *
 *  Created on: Aug 15, 2023
 *      Author: user
 */


#include "../../LIB/stdTypes.h"
#include "../../LIB/errorStates.h"

#include "GIE_priv.h"


ES_t GIE_enuEnable(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	SREG |= ( 1 << I );

	return Local_enuErrorState;
}

ES_t GIE_enuDisable(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	SREG &= ~ ( 1<< I );

	return Local_enuErrorState;
}

