/*******************************************************************/
/*******************************************************************/
/*******************    Author: Mohamed Fathy    *******************/
/*******************    Layer:  MCAL             *******************/
/*******************    SWC:    ADC              *******************/
/*******************    Version:1.00             *******************/
/*******************************************************************/
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


void	ADC_voidInit(void);
u16 ADC_u16PollingRead(u8 Copy_u8Channel);

void ADC_voidEnableAutoTriggeringMode();

ES_t ADC_enuCallback(void(*pfunc));

u16 ADC_u16Read();									//included in polling read

ES_t ADC_enuSelectChannel(u8 Copy_u8Channel);		//in case of auto triggering, you should select the channel at first (included in polling read)
#endif /* ADC_INTERFACE_H_ */
