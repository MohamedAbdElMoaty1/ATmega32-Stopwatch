#include "STD_TYPES.h"
#include <util/delay.h>

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "SWITCH_interface.h"
#include "KPD_interface.h"

uint8 Local_u8Arrow[8] = {
		0b00000100,
		0b00001110,
		0b00011111,
		0b00000100,
		0b00000100,
		0b00000100,
		0b00000100,
		0
};

SWITCH_config_t SWITCH_Right = {
		.SWITCH_u8Port = DIO_u8PORTB,
		.SWITCH_u8Pin = DIO_u8PIN0,
		.SWITCH_u8Pull_t = SWITCH_u8PULL_UPP
};

SWITCH_config_t SWITCH_Left = {
		.SWITCH_u8Port = DIO_u8PORTB,
		.SWITCH_u8Pin = DIO_u8PIN1,
		.SWITCH_u8Pull_t = SWITCH_u8PULL_UPP
};

SWITCH_config_t SWITCH_Start = {
		.SWITCH_u8Port = DIO_u8PORTB,
		.SWITCH_u8Pin = DIO_u8PIN2,
		.SWITCH_u8Pull_t = SWITCH_u8PULL_UPP
};

uint8 Local_u8State1, Local_u8State2, Local_u8State3;
uint8 Local_u8Counter = 0;
uint8 Local_u8KeypadKey = 0 ;
uint8 Local_u8num[8] = {0} ;
uint8 Local_u8Sec = 0 ;
uint8 Local_u8HR,Local_u8MN,Local_u8SC;


void main(void)
{

	/* Set direction */
	PORT_voidInit();
	/* Initialize LCD */
	CLCD_voidInit();

	/* Display initial time and arrow */
	CLCD_voidSendNumber(0);
	CLCD_voidSendNumber(0);
	CLCD_voidSendData(':');
	CLCD_voidSendNumber(0);
	CLCD_voidSendNumber(0);
	CLCD_voidSendData(':');
	CLCD_voidSendNumber(0);
	CLCD_voidSendNumber(0);
	CLCD_u8SendSpecialCharacter(0, Local_u8Arrow, 0, 1);
	CLCD_voidGoToXY(0, 0);

	while(1)
	{

		Local_u8KeypadKey = KPD_u8GetPressedKey();

		if(Local_u8KeypadKey != 0xff)
		{
			if(Local_u8Counter == 2 || Local_u8Counter == 5)
			{
				continue;
			}
			Local_u8num[Local_u8Counter]= Local_u8KeypadKey ;
			CLCD_voidGoToXY(Local_u8Counter, 0);  // Move to the current cursor position
			CLCD_voidSendNumber(Local_u8num[Local_u8Counter]);  // Display the pressed key
		}

		SWITCH_u8GetState(&SWITCH_Right, &Local_u8State1);
		SWITCH_u8GetState(&SWITCH_Left, &Local_u8State2);
		SWITCH_u8GetState(&SWITCH_Start, &Local_u8State3);

		if (Local_u8State1 == SWITCH_u8RELEASED)
		{
			_delay_ms(300);  // Debounce delay
			CLCD_voidGoToXY(Local_u8Counter, 1);  // Move to current arrow position
			CLCD_voidSendData(' ');  // Clear current arrow
			Local_u8Counter++;
			if (Local_u8Counter == 8)  // Wrap around if beyond last position
			{
				Local_u8Counter = 0;
			}


			CLCD_u8SendSpecialCharacter(0, Local_u8Arrow, Local_u8Counter, 1);  // Draw arrow at new position
		}

		if (Local_u8State2 == SWITCH_u8RELEASED)
		{
			_delay_ms(300);  // Debounce delay

			CLCD_voidGoToXY(Local_u8Counter, 1);  // Move to current arrow position
			CLCD_voidSendData(' ');  // Clear current arrow

			if (Local_u8Counter <= 0)  // Wrap around if at first position
			{
				Local_u8Counter = 7;
			}
			else
			{
				Local_u8Counter--;
			}

			CLCD_u8SendSpecialCharacter(0, Local_u8Arrow, Local_u8Counter, 1);  // Draw arrow at new position
		}

		if (Local_u8State3 == SWITCH_u8RELEASED)
		{
			_delay_ms(300);  // Debounce delay
			CLCD_voidGoToXY(Local_u8Counter, 1);  // Move to current arrow position
			CLCD_voidSendData(' ');  // Clear current arrow

			Local_u8HR = ((Local_u8num[0])*10) + (Local_u8num[1]) ;
			Local_u8MN = ((Local_u8num[3])*10) + (Local_u8num[4]) ;
			Local_u8SC = ((Local_u8num[6])*10) + (Local_u8num[7]) ;
			for(Local_u8Sec = Local_u8SC ; Local_u8Sec >= 0 ; Local_u8Sec--)
			{

				if(Local_u8HR > 0 && Local_u8MN == 0 && Local_u8Sec == 0)
				{
					Local_u8HR--;
					Local_u8MN  = 60 ;
					if(Local_u8HR >= 10)
					{
						CLCD_voidGoToXY(0, 0);             // Move to the current cursor position
						CLCD_voidSendNumber(Local_u8HR);  // Display the pressed key
					}
					else
					{
						CLCD_voidGoToXY(0,0);
						CLCD_voidSendNumber(0);
						CLCD_voidGoToXY(1,0);              // Move to the current cursor position
						CLCD_voidSendNumber(Local_u8HR);  // Display the pressed key
					}
				}


				if(Local_u8MN > 0 && Local_u8Sec == 0)
				{
					Local_u8MN--;
					Local_u8Sec = 60 ;
					if(Local_u8MN >= 10)
					{
						CLCD_voidGoToXY(3, 0);             // Move to the current cursor position
						CLCD_voidSendNumber(Local_u8MN);  // Display the pressed key
					}
					else
					{
						CLCD_voidGoToXY(3,0);
						CLCD_voidSendNumber(0);
						CLCD_voidGoToXY(4,0);              // Move to the current cursor position
						CLCD_voidSendNumber(Local_u8MN);  // Display the pressed key
					}
				}

				if(Local_u8Sec < 10)
				{
					CLCD_voidGoToXY(6,0);
					CLCD_voidSendNumber(0);
					CLCD_voidGoToXY(7,0);              // Move to the current cursor position
					CLCD_voidSendNumber(Local_u8Sec);  // Display the pressed key
				}
				else if(Local_u8Sec >= 10)
				{
					CLCD_voidGoToXY(6, 0);             // Move to the current cursor position
					CLCD_voidSendNumber(Local_u8Sec);  // Display the pressed key
				}
				if(Local_u8Sec == 0 && Local_u8MN == 0 && Local_u8HR == 0 )
				{
					_delay_ms(500);
					CLCD_voidGoToXY(0,0);
					CLCD_u8SendString("    TIME OUT   ");
					Local_u8HR = 0 ;
					Local_u8MN = 0 ;
					Local_u8SC = 0 ;
					Local_u8Counter = 0;
					Local_u8KeypadKey = 0 ;
					Local_u8Sec = 0 ;
					return;
				}
				_delay_ms(1000);
			}

		}

	}  // while(1)

}  // main
