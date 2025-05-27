/*
 * name : Mahmoud kafafy
 * diploma : 69
 * project: mini 3 project
 */

#include"lcd.h"
#include"lm35_sensor.h"
#include"adc.h"
#include"dc_motor.h"

int main()
{

	ADC_ConfigType config = {INTERNAL,prescalar_8};
	ADC_init(&config);
	LCD_init();
	DcMotor_Init();
	LCD_moveCursor(1,2);
	LCD_displayString("Temp =    C");
	uint16 temp;
	while(1)
	{
		temp = LM35_getTemperature();
		/* Display the temperature value every time at same position */
		LCD_moveCursor(1,9);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}

        /*Control speed of motor depend on tempreature*/
		if(temp <  30 )
		{
			DcMotor_Rotate(CW,0);
		}
		else if(temp >=  30 && temp <60 )
		{
			DcMotor_Rotate(CW,25);
		}
		else if(temp >= 60 && temp < 90 )
		{
			DcMotor_Rotate(CW,50);
		}
		else if(temp >= 90 && temp<120)
		{
			DcMotor_Rotate(CW,75);
		}
		else if(temp > 120)
		{
			DcMotor_Rotate(CW,100);
		}

       /*Display on LCD the state of fan*/
		LCD_moveCursor(0,4);
		if(temp <  30 )
		{
			LCD_displayStringRowColumn(0,3,"Fan is OFF");
		}
		else
		{
			LCD_displayStringRowColumn(0,2,"Fan is ON  ");
		}
	}

}

