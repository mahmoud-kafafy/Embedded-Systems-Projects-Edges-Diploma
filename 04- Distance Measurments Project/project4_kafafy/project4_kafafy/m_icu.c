/*
 * m_icu.c
 *
 *  Created on: Oct 15, 2022
 *      Author: HP
 */
#include"m_icu.h"
#include"common_macros.h"
#include<avr/io.h>
#include"m_gpio.h"
#include <avr/interrupt.h> /* For ICU ISR */

static volatile void (*g_ptr2func)(void) = NULL_PTR;

ISR(TIMER1_CAPT_vect)
{
	if(g_ptr2func != NULL_PTR)
	{
		g_ptr2func();
	}
}

void Icu_init(Icu_configuration * config )
{
	/* Timer1 always operates in Normal Mode */
		TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	//INTIALIZE CAPTURE WITH RISING
	TCCR1B = (TCCR1B & 0XBF) | ((config -> edge)<<6);
	TCCR1B = (TCCR1B & 0XF8) | (config -> clk);
	//setup direction of PD6 which have ICU module
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT);
	//enable interrupt of module
	SET_BIT(TIMSK,TICIE1);

}

void Icu_EdgeDetectionType(Icu_EdgeCapture edge)
{
	TCCR1B = (TCCR1B & 0XBF) | (edge<<6);
}

uint16 Icu_getInputCaptureValue(void)
{
	return ICR1;
}

/*To start time from 0 each time use timer start count from 0*/
void Icu_ClearTime()
{
	TCNT1=0;
}


/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void Icu_DeInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);
}

void Icu_CallBackFunction (void (*ptr2func)(void))
{
	g_ptr2func = ptr2func;
}




