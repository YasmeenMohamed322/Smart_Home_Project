#include "stdTypes.h"
#include "errorState.h"

#include "EXTI_Private.h"
#include "EXTI_Config.h"


EXTI_T EXTI_AstrEXTIconfig[3]=
{
		{INT_DEAVTIVE},          	 			 //INT0
		{INT_ACTIVE,FALLING_EDGE},     		     //INT1
		{INT_DEAVTIVE},            	             //INT2

};