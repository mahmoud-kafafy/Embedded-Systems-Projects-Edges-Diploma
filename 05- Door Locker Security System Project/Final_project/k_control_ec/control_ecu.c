/*
 * control_ecu.c
 *
 *  Created on: Nov 4, 2022
 *      Author: HP
 */

#include "external_eeprom.h"
#include"dc_motor.h"
#include"uart_m.h"
#include <util/delay.h>
#include<avr/io.h>
#include"buzzer.h"
#include "timer1.h"


/* Random number to check if the control ECU is ready to receive
 * password or not*/
#define CONTROL_ECU_READY 0xF0
/* Global Variable to store the received state of 2 password; matched or not*/
volatile uint8 g_matchingCheck;

volatile uint8 g_seconds;
/*2 Passwords States*/
enum{UNMATCHED=1,MATCHED=2};
/*Door States*/
enum{OPEN,CHANGE,RESET,OPENED,CLOSED,CLOSING,DONE};
void setpassoward (uint8 * passoward, uint8 * passoward_2);
void recieve_passoward (uint8 * passoward);
uint8 compare_passoward (uint8 * passoward, uint8 * passoward_2);
void writePasswordToEeprom (uint8 * passoward );
void readPasswordFromEeprom(uint8 *password);
void changePassword(uint8 *password,uint8 *password_2);
void openDoor(uint8 *password,uint8 *password_2);
void periodCallBack(void);
int main()
{
	/*Setting the Timer 1 Configurations to count 1 second every Interrupt*/
	Timer1_ConfigType period;
	period.mode=TIMER1_CTC;
	period.clock=TIMER1_F_CPU_64;
	period.initialValue=0;
	period.oc1AMode=OC1_A_DISCONNECT;
	period.oc1BMode=OC1_B_DISCONNECT;
	period.tick=15625;
	TIMER1_init(&period);
	TIMER1_setCallBack(periodCallBack,TIMER1_CTC);
	TIMER1_stopCount();
	//buzzer init
	Buzzer_init();
	SREG |=(1<<7);
	volatile uint8 pass1[10];
	volatile uint8 pass2[10];
	UART_Configuration hmi_conf = {DISABLE,STOP1_BIT,BITS_8,9600};
	UART_init(8000000, &hmi_conf);
	UART_sendByte(0xF0);
	setpassoward(pass1,pass2);
	uint8 system;
	while(1)
	{
		system = UART_recieveByte();
		switch(system)
		{
		case CHANGE :
			changePassword(pass1,pass2);
			break;
		case OPEN:
			openDoor(pass1,pass2);
			break;
		}
	}

}

void setpassoward (uint8 * passoward, uint8 * passoward_2)
{
	recieve_passoward(passoward);
	recieve_passoward(passoward_2);
	g_matchingCheck = compare_passoward (passoward,passoward_2);
	UART_sendByte(g_matchingCheck);
	while(g_matchingCheck == UNMATCHED)
	{
		UART_sendByte(g_matchingCheck);
		recieve_passoward(passoward);
		recieve_passoward(passoward_2);
		g_matchingCheck = compare_passoward (passoward,passoward_2);
	}
	/*Once they are matched save the password into the EEPROM*/
	UART_sendByte(MATCHED);
	writePasswordToEeprom(passoward);
}

void recieve_passoward (uint8 * passoward)
{
	uint8 i = 0;
	passoward[i]= UART_recieveByte();
	while(passoward[i] != 13)
	{
		i++;
		passoward[i]= UART_recieveByte();
	}
}

uint8 compare_passoward (uint8 * passoward, uint8 * passoward_2)
{
	for(int i =0 ; i<5 ; i++)
	{
		if(passoward[i] != passoward_2[i])
		{
			/* if only one element in passoward1 does not match the corresponding element in passoward2 return UNMATCHED */
			return UNMATCHED;
		}
	}
	/* both passowards are identical retrun MATCHED*/
	return MATCHED;
}


void writePasswordToEeprom (uint8 * passoward )
{
	uint8 i = 0;
	while(passoward[i] != 13)
	{
		EEPROM_writeByte(0x0311+i, passoward[i]); /* Write passoward in the external EEPROM */
		_delay_ms(10);
		i++;
	}
	EEPROM_writeByte(0x0311+i, passoward[i]);
}

void readPasswordFromEeprom(uint8 *password){
	uint8 i=0;
	EEPROM_readByte((0x0311+i),&password[i]);
	while(password[i]!=13){
		i++;
		EEPROM_readByte((0x0311+i),&password[i]); /* read passoward in the external EEPROM */
	}
}

void changePassword(uint8 *password,uint8 *password_2){
	uint8 n=0;
	recieve_passoward(password);
	readPasswordFromEeprom(password_2);
	g_matchingCheck=compare_passoward(password,password_2);
	UART_sendByte(g_matchingCheck);
	while((g_matchingCheck==UNMATCHED) & (n<2)){
		n++;
		recieve_passoward(password);
		g_matchingCheck=compare_passoward(password,password_2);
		UART_sendByte(g_matchingCheck);
	}
	if(n==2){
		Buzzer_ON();
	}
	else if(g_matchingCheck==MATCHED){
		setpassoward(password,password_2);
		UART_sendByte(DONE);
	}
}


void openDoor(uint8 *password,uint8 *password_2){
	uint8 n=0;
	recieve_passoward(password);
	readPasswordFromEeprom(password_2);
	g_matchingCheck=compare_passoward(password,password_2);
	UART_sendByte(g_matchingCheck);
	while((g_matchingCheck==UNMATCHED) & (n<2)){
		n++;
		recieve_passoward(password);
		g_matchingCheck=compare_passoward(password,password_2);
		UART_sendByte(g_matchingCheck);
	}
	if(n==2){
		Buzzer_ON();
	}
	else if(g_matchingCheck==MATCHED){
		UART_sendByte(OPENED);
		DcMotor_Rotate(CW,75);
		TIMER1_startCount(TIMER1_F_CPU_64);
		while(g_seconds<15){};
		TIMER1_stopCount();
		g_seconds=0;
		DcMotor_Rotate(STOP,0);
		TIMER1_startCount(TIMER1_F_CPU_64);
		while(g_seconds<3){};
		TIMER1_stopCount();
		g_seconds=0;
		UART_sendByte(CLOSING);
		DcMotor_Rotate(CCW,75);
		TIMER1_startCount(TIMER1_F_CPU_64);
		while(g_seconds<15){};
		g_seconds=0;
		TIMER1_stopCount();
		DcMotor_Rotate(STOP,0);
		UART_sendByte(CLOSED);
	}

}

/* ---------------------------------------------------------------------------
[FUNCTION NAME] : periodCallBack
[DESCRIPTION]   : Function is responsible for incrementing the seconds global
			      variable each timer interrupt.

[Args]		    :
				void
[Return]	   :
				void
------------------------------------------------------------------------------*/
void periodCallBack(void){
	g_seconds++;
}
