/*
 ================================================================================================
 Name        : Mahmoud Kafafy
 Description : mini_Project_4
 diploma     : 69
 ================================================================================================
 */

#include "lcd.h"
#include <avr/io.h> /* To use the SREG register */
#include"ultrasonic.h"
#include<util/delay.h>

int main()
{
	uint16 distance = 0;
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	LCD_init();
	//Icu_init(&Icu_Config);
	Ultrasonic_init();
	LCD_displayString("Distance=     cm");
	while(1)
	{
		distance = Ultrasonic_readDistance();
		LCD_moveCursor(0,11);
		LCD_intgerToString(distance);
		_delay_ms(100);

	}
}
