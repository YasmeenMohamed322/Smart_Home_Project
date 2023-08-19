



#include "../../LIB/errorStates.h"
#include "../../LIB/stdTypes.h"

#include "../../MCAL/ADC/ADC_interface.h"

#include "LM35_priv.h"
#include "LM35_int.h"



u8 LM35_getTemperature(u8 Copy_u8Channel)
{
	u16 Local_u16ADCValue = ADC_u16PollingRead(Copy_u8Channel);
	u8  Local_u8tempValue =(u8)((u32)(Local_u16ADCValue*LM_MAX_VOLT)/((u32)(ADC_MAX_READ*LM_SCALE))); // map between ADC read and temperature
	return Local_u8tempValue;

}
