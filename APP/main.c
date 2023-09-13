/**************************************************************/
/**************************************************************/
/**************    Project		: Smart Home  *****************/
/**************    Platform		: AVR         *****************/
/**************    Peripheral	: ATMEGA32    *****************/
/**************    Version		: 1.00        *****************/
/**************************************************************/
/**************************************************************/

/*	you should give a brief of the content of this file
 *
 */


/********** Includes Section Start ********************************/

#include "../LIB/stdTypes.h"
#include "../LIB/errorStates.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/USART/USART_int.h"
#include "../MCAL/TWI/TWI_int.h"

#include "../HAL/EEPROM/EEPROM_int.h"

#include <util/delay.h>

/********** Includes Section End ********************************/



/********** Macros Section Start ********************************/

#define USERNAME_MAXIMUM_LENGTH		8
#define PASSWORD_MAXIMUM_LENGTH		8

#define SYSTEM_MAXIMUM_USERS		5

#define ADMIN_INDEX					0

#define SYSTEM_USERNAMES_START_LOCATION		0x8
#define SYSTEM_PASSWORDS_START_LOCATION		0x30
#define SYSTEM_USERNAMES_AND_PASSWORDS_MEMORY_BLOCK		0

#define SYSTEM_USERS_AVAILABILITY_START_LOCATION		0x0
#define SYSTEM_USERS_AVAILABILITY_MEMORY_BLOCK			0

/********** Macros Section End ********************************/


/********** Global Variables Section Start ********************************/

u8 Global_u8isAdminSet;	//This variable indicates whether the username and password of the admin is set or not

u8 Global_u8VirtualTerminal;	//This variable choose between using virtual terminal or LCD and keypad


//These two arrays is used to save the usernames and passwords
//of the system from EEPROM into RAM
u8 Global_u8SystemUsernames [SYSTEM_MAXIMUM_USERS][USERNAME_MAXIMUM_LENGTH];
u8 Global_u8SystemPasswords [SYSTEM_MAXIMUM_USERS][PASSWORD_MAXIMUM_LENGTH];

//This array indicates whether a user location is set or no
//if the index is zero, that shows that it's available to set new user in this location and vice versa
u8 Global_u8UsersAvailabilityStatus[SYSTEM_MAXIMUM_USERS];

u8 Global_u8CurrentNumberOfUsers; //This variable is updated with the current number of users of the system

/********** Global Variables Section End ********************************/


/********** User Functions Prototype Section Start ********************************/

/*	you should make description for each function
 *
 */


//This function initialize Global_u8UsersAvailabilityStatus
void usersAvailabilityStatusInit(void);

//This function initialize Global_u8SystemUsernames and Global_u8SystemPasswords
void systemUsersInit(void);

//This function return zero if admin is not set and one if is set
u8 checkAdminStatus(void);

//This function set the username and password of the admin for starting the system for the first time
void setAdmin(void);

//This function take the username and the index as parameters and set the username
ES_t setUsername(u8* Copy_pu8Username, u8 Copy_u8UserIndex);

//This function take the password and the index as parameters and set the password
ES_t setPassword(u8* Copy_pu8Password, u8 Copy_u8UserIndex);

/*
//This function takes the username from the user
u8* getUsername(void);

//This function takes the password from the user
u8* getPassword(void);
*/
/********** User Functions Prototype Section End ********************************/


void main (void)
{
	//u8 Local_u8Counter1 = 0, Local_u8Counter2 = 0;

	DIO_enuInit();		//Initialize the DIO driver
	UART_enuInit();		//Initialize the UART driver
	TWI_voidInit();		//Initialize the Two Wire Interface driver

	usersAvailabilityStatusInit();	//Initialize the the status of the users
	systemUsersInit();		//Initialize the users system

	Global_u8isAdminSet = checkAdminStatus();	//It will be assigned with one if the admin is set and zero if not

	UART_enuSendString("////////////////////////////////////////\r");
	UART_enuSendString("/**************************************/\r");
	UART_enuSendString("/***** Welcome to your smart home *****/\r");
	UART_enuSendString("/**************************************/\r");
	UART_enuSendString("////////////////////////////////////////\r\r");

	while(1)
	{

		if(!Global_u8isAdminSet)
		{
			setAdmin();
		}
		else
		{

			if(Global_u8VirtualTerminal)
			{

			}
			else
			{

			}

		}
	}
}


/********** User Functions Section Start ********************************/


void usersAvailabilityStatusInit(void)
{
	u8 Local_u8Counter1 = 0;

	//This loop iterates over the Global_u8UsersAvailabilityStatus in order to save the availability status
	//of the users from EEPROM to RAM
	for(Local_u8Counter1 = 0 ; Local_u8Counter1 < SYSTEM_MAXIMUM_USERS ; Local_u8Counter1++)
	{
		Global_u8UsersAvailabilityStatus[Local_u8Counter1] = EEPROM_u8ReadByte(
				EEPROM_FIRST_MEMORY,
				SYSTEM_USERS_AVAILABILITY_MEMORY_BLOCK,
				SYSTEM_USERS_AVAILABILITY_START_LOCATION + Local_u8Counter1
				);
	}

}

void systemUsersInit(void)
{
	u8 Local_u8Counter1 = 0, Local_u8Counter2 = 0;

	//The outer loop iterates over the system users and the inner loop iterates over each
	//username and password.
	//This nested loop save the usernames and passwords of the system from EEPROM into RAM in
	//defined arrays.
	for(Local_u8Counter1 = 0 ; Local_u8Counter1 < SYSTEM_MAXIMUM_USERS ; Local_u8Counter1++)
	{
		for(Local_u8Counter2 = 0 ; Local_u8Counter2 < USERNAME_MAXIMUM_LENGTH ; Local_u8Counter2++)
		{
			Global_u8SystemUsernames[Local_u8Counter1][Local_u8Counter2] = EEPROM_u8ReadByte(
					EEPROM_FIRST_MEMORY,
					SYSTEM_USERNAMES_AND_PASSWORDS_MEMORY_BLOCK,
					SYSTEM_USERNAMES_START_LOCATION+Local_u8Counter2
					);
		}

		for(Local_u8Counter2 = 0 ; Local_u8Counter2 < PASSWORD_MAXIMUM_LENGTH ; Local_u8Counter2++)
		{
			Global_u8SystemPasswords[Local_u8Counter1][Local_u8Counter2] = EEPROM_u8ReadByte(
					EEPROM_FIRST_MEMORY,
					SYSTEM_USERNAMES_AND_PASSWORDS_MEMORY_BLOCK,
					SYSTEM_PASSWORDS_START_LOCATION+Local_u8Counter2
					);
		}
	}

}

u8 checkAdminStatus(void)
{
	//This variable is assigned with the status of the admin
	u8 Local_u8AdminStatus = EEPROM_u8ReadByte(
			EEPROM_FIRST_MEMORY,
			SYSTEM_USERS_AVAILABILITY_MEMORY_BLOCK,
			SYSTEM_USERS_AVAILABILITY_START_LOCATION
			);


	if(Local_u8AdminStatus == '1') // check if the admin is set or not, if it's 1 so it's set and vice versa
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

void setAdmin(void)
{
	u8  Local_u8Counter2 = 0, Local_u8ReceiveCharacter;

	//taking the username from the user
	UART_enuSendString("Please set your username\r");
	UART_enuRecieveString((char*)Global_u8SystemUsernames[ADMIN_INDEX]);
	setUsername(Global_u8SystemUsernames[ADMIN_INDEX], ADMIN_INDEX);

	//taking the password from the user
	UART_enuSendString("Please set your password\r");
	for(Local_u8Counter2 = 0 ; Local_u8Counter2 < USERNAME_MAXIMUM_LENGTH ; Local_u8Counter2++)
	{
		UART_enuRecieveChar(&Local_u8ReceiveCharacter);

		//To make the password in the form of "*"
		if(Local_u8Counter2!=0)
		{
			UART_enuSendString("\b\b*");
			UART_enuSendChar(Local_u8ReceiveCharacter);
		}

		//check if it's the end of the password
		if(Local_u8ReceiveCharacter == 0x0d)
		{
			break;
		}
		else
		{

			Global_u8SystemPasswords[ADMIN_INDEX][Local_u8Counter2] = Local_u8ReceiveCharacter;

		}

	}
	setPassword(Global_u8SystemPasswords[ADMIN_INDEX], ADMIN_INDEX);

	UART_enuSendString("Your username and password are set successfully.");

	//update the status of users system
	Global_u8UsersAvailabilityStatus[ADMIN_INDEX] = '1';
	Global_u8isAdminSet = 1;
	EEPROM_voidWriteByte(
			'1',
			EEPROM_FIRST_MEMORY,
			SYSTEM_USERS_AVAILABILITY_MEMORY_BLOCK,
			SYSTEM_USERS_AVAILABILITY_START_LOCATION
			);
	Global_u8CurrentNumberOfUsers++;
	_delay_ms(10);


}

ES_t setUsername(u8* Copy_pu8Username, u8 Copy_u8UserIndex)
{
	u8  Local_u8Counter2 = 0, Local_u8ReceiveCharacter;
	ES_t Local_enuErrorState = ES_OK;

	if(Copy_u8UserIndex > SYSTEM_MAXIMUM_USERS) //Check if user location is exist
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	else
	{

		//This loop takes the username assigning it into Global_u8SystemUsernames
		for(Local_u8Counter2 = 0 ; Local_u8Counter2 < USERNAME_MAXIMUM_LENGTH ; Local_u8Counter2++)
		{
			Local_u8ReceiveCharacter = *(Copy_pu8Username+Local_u8Counter2);

			if(Local_u8ReceiveCharacter != (u8)(NULL)) //Check if it is the end of the username or not
			{
				Global_u8SystemUsernames[Copy_u8UserIndex][Local_u8Counter2] = Local_u8ReceiveCharacter;
			}
			else
			{
				break;
			}

		}

		//Storing the username into the EEPROM memory
		for(Local_u8Counter2 = 0 ; Local_u8Counter2 < USERNAME_MAXIMUM_LENGTH ; Local_u8Counter2++)
		{


			EEPROM_voidWriteByte(
					*(Global_u8SystemUsernames[Copy_u8UserIndex] + Local_u8Counter2),
					EEPROM_FIRST_MEMORY,
					SYSTEM_USERNAMES_AND_PASSWORDS_MEMORY_BLOCK,
					SYSTEM_USERNAMES_START_LOCATION + Local_u8Counter2
					);
			_delay_ms(10);
		}
	}

	return Local_enuErrorState;

}

ES_t setPassword(u8* Copy_pu8Password, u8 Copy_u8UserIndex)
{
	u8  Local_u8Counter2 = 0, Local_u8ReceiveCharacter;
	ES_t Local_enuErrorState = ES_OK;

	if(Copy_u8UserIndex > SYSTEM_MAXIMUM_USERS) //Check if user location is exist
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	else
	{
		//This loop takes the password assigning it into Global_u8SystemPasswords
		for(Local_u8Counter2 = 0 ; Local_u8Counter2 < PASSWORD_MAXIMUM_LENGTH ; Local_u8Counter2++)
		{
			Local_u8ReceiveCharacter = *(Copy_pu8Password+Local_u8Counter2);

			if(Local_u8ReceiveCharacter != (u8)(NULL)) //Check if it is the end of the password or not
			{
				Global_u8SystemPasswords[Copy_u8UserIndex][Local_u8Counter2] = Local_u8ReceiveCharacter;
			}
			else
			{
				break;
			}

		}

		//Storing the password into the EEPROM memory
		for(Local_u8Counter2 = 0 ; Local_u8Counter2 < PASSWORD_MAXIMUM_LENGTH ; Local_u8Counter2++)
		{
			EEPROM_voidWriteByte(
					*(Global_u8SystemPasswords[Copy_u8UserIndex] + Local_u8Counter2),
					EEPROM_FIRST_MEMORY,
					SYSTEM_USERNAMES_AND_PASSWORDS_MEMORY_BLOCK,
					SYSTEM_PASSWORDS_START_LOCATION + Local_u8Counter2
					);
			_delay_ms(10);
		}
	}

	return Local_enuErrorState;
}


/********** User Functions Section End ********************************/

