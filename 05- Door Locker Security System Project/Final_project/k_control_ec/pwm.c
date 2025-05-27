/*
 * pwm.c
 *
 *  Created on: Oct 8, 2022
 *      Author: HP
 */

#include<avr/io.h>
#include"pwm.h"
#include"common_macros.h"

void Timer0_PWM_Init(uint8 duty_cycle_percent,uint8 out_pin)
{
	TCNT0 = 0; // Set Timer Initial Value to 0

	/* configure the timer
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
	uint8 set_duty_cycle= duty_cycle_percent * PERCENT_FACTOR;

	OCR0  = set_duty_cycle;

	DDRB|=(1<<3);
}
