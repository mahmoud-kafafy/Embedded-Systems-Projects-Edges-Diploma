/*
 * project.c
 *
 *  Created on: Sep 17, 2022
 *      Author: HP
 */
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

unsigned char tick= 0;
/* 6 variables to control digits on stopwatch*/
unsigned char secound_0 = 0;
unsigned char secound_1 = 0;
unsigned char minutes_0 = 0;
unsigned char minutes_1 = 0;
unsigned char hours_0 = 0;
unsigned char hours_1 = 0;

//reset digits on stopwatch
void clear_stopwatch()
{
	secound_0 = 0;
	secound_1 = 0;
	minutes_0 = 0;
	minutes_1 = 0;
	hours_0 = 0;
	hours_1 = 0;
}

//timer1 ISR count each interrupt
ISR(TIMER1_COMPA_vect)
{
	secound_0 ++;
	if(secound_0 == 10) //second_0 reach 10 then increment the next digit and reset others (00:10)
	{
		secound_0 = 0;
		secound_1 ++;
	}
	if (secound_1 == 6 ) //seconds reach 60 second then increment minutes to 1 minute & reset others (01:00)
	{
		minutes_0 ++;
		secound_0 = 0;
		secound_1 = 0;
	}
	if (minutes_0 == 10) //minute_0 reach 10 then increment the next digit and reset others(10:00)
	{
		minutes_1 ++;
		secound_0 = 0;
		secound_1 = 0;
		minutes_0 =0;
	}
	if (minutes_1 == 6) //minutes reach 60 minute then increment hours to 1 hour(01:00:00)
	{
		secound_0 = 0;
		secound_1 = 0;
		minutes_0 = 0;
		minutes_1 = 0;
		hours_0 ++;
		if(hours_1 == 2 && hours_0 == 4) // reset stopwatch when 24 hour (00:00:00)
		{
			clear_stopwatch();
		}
	}
	if (hours_0 == 10) //hours_0 reach 10 then increment the next digit and reset others(10:00:00)
	{
		hours_1 ++;
		secound_0 = 0;
		secound_1 = 0;
		minutes_0 = 0;
		minutes_1 = 0;
		hours_0 = 0;
	}

}

ISR(INT1_vect)
{
		TCCR1B=0; // turn off timer register to stop counter
}

ISR(INT0_vect)
{
	clear_stopwatch(); // reset all digits on stopwatch
}


ISR(INT2_vect)
{
	TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10); // continue count by active clock again of timer by prescular 1024
}

void Timer1_CTC (void)
{
	TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10);
	TCNT1=0;
	OCR1A=1000;
	TIMSK|= (1<<OCIE1A);
	TCCR1A = (1<<FOC1A);
}

void paused_INT1 ()
{
	DDRD  &= (~(1<<PD3));
	MCUCR|=(1<<ISC11) | (1<<ISC10);
	SREG|=(1<<7);
	GICR|=(1<<INT1);
}

void resume_INT2()
{
	DDRB &= (~(1<<PB2));
	PORTB|=(1<<PB2);
	MCUCSR &=~(1<<ISC2);
	SREG|=(1<<7);
	GICR|=(1<<INT2);
}

void reset_INT0()
{
	DDRD &= (~(1<<PD2));
	PORTD|=(1<<PD2);
	GICR|=(1<<INT0);
	MCUCR |=(1<<ISC01);
	SREG|=(1<<7);
}


int main(void)
{
	SREG|=(1<<7);
	DDRC|=0x0f;         //4 output for decoder by write needed number
	DDRA|=0X3f;         //6 output to enable 7 segment

	/*definitions of functions in main*/
	Timer1_CTC();
	paused_INT1();
	resume_INT2();
	reset_INT0();


	while(1)
	{
		//display
		PORTA = (1<<0);  //enable first 7 segment and disable others
		PORTC= (PORTC & 0xf0) | (hours_1 & 0x0f);
		_delay_ms(2);

		PORTA = (1<<1);   //enable second 7 segment and disable others
		PORTC= (PORTC & 0xf0) | (hours_0 & 0x0f);
		_delay_ms(2);

		PORTA = (1<<2);  //enable third 7 segment and disable others
		PORTC= (PORTC & 0xf0) | (minutes_1 & 0x0f);
		_delay_ms(2);

		PORTA = (1<<3);  //enable fourth 7 segment and disable others
		PORTC= (PORTC & 0xf0) | (minutes_0 & 0x0f);
		_delay_ms(2);

		PORTA = (1<<4);  //enable fifth 7 segment and disable others
		PORTC= (PORTC & 0xf0) | (secound_1 & 0x0f);
		_delay_ms(2);

		PORTA = (1<<5);  //enable sixth 7 segment and disable others
		PORTC= (PORTC & 0xf0) | (secound_0 & 0x0f) ;
		_delay_ms(2);

	}
}
