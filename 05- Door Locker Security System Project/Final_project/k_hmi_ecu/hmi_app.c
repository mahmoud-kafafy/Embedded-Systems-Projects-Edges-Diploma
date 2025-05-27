/*
 * hmi_app.c
 *
 *  Created on: Nov 2, 2022
 *      Author: HP
 */

#include"lcd.h"
#include"keypad.h"
#include <util/delay.h>
#include"uart_m.h"


//uint8 pass2 [8];

/* Random number to check if the control ECU is ready to receive
 * password or not*/
#define CONTROL_ECU_READY 0xF0
/* Global Variable to store the received state of 2 password; matched or not*/
volatile uint8 g_matchingCheck;
/*2 Passwords States*/
enum{UNMATCHED=1,MATCHED=2};
/*Door States*/
enum{OPEN,CHANGE,RESET,OPENED,CLOSED,CLOSING,DONE};

void getPassword(uint8 * password);
void setPassword(uint8 *password);
void sendPassword(uint8 *password);
void changePassword(uint8 *password);
void openDoor(uint8 *password);
int main()
{
	volatile uint8 pass1 [12];
	UART_Configuration hmi_conf = {DISABLE,STOP1_BIT,BITS_8,9600};
	UART_init(8000000, &hmi_conf);
	uint8 key;
	LCD_init();
	while(UART_recieveByte() != CONTROL_ECU_READY){}
	setPassword(pass1);
	while(1)
	{
		/*Display the default message on the LCD*/
		LCD_displayString("+ : Open Door");
		LCD_moveCursor(1,0);
		LCD_displayString("- : Change Pass");
		/*Wait the user to choose if he want to open the door or change the password*/
		key=KEYPAD_getPressedKey();
		switch(key){
		case '-':
			UART_sendByte(CHANGE);
			changePassword(pass1);
			break;
		case '+':
			UART_sendByte(OPEN);
			openDoor(pass1);
			break;
		}
	}
	return 0;
}



void changePassword(uint8 *password){
	uint8 n=0;
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	LCD_displayString("Enter Old Pass:");
	LCD_moveCursor(1,0);
	getPassword(password);
	sendPassword(password);
	g_matchingCheck=UART_recieveByte();
	while(((g_matchingCheck==UNMATCHED) && (n<2))){
		n++;
		LCD_sendCommand(LCD_CLEAR_COMMAND);
		LCD_displayString("Wrong Password");
		_delay_ms(200);
		LCD_sendCommand(LCD_CLEAR_COMMAND);
		LCD_displayString("Enter Old Pass:");
		LCD_moveCursor(1,0);
		getPassword(password);
		sendPassword(password);
		g_matchingCheck=UART_recieveByte();
	}
	if(n==2){
		LCD_sendCommand(LCD_CLEAR_COMMAND);
		LCD_displayString("Error !!!");
		while(UART_recieveByte()!=RESET){};
	}
	else if (g_matchingCheck==MATCHED){
		setPassword(password);
		while(UART_recieveByte()!=DONE){};
	}
}


void openDoor(uint8 *password){
	uint8 n=0;
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	LCD_displayString("plz enter pass:");
	LCD_moveCursor(1,0);
	getPassword(password);
	sendPassword(password);
	g_matchingCheck= UART_recieveByte();
	while(((g_matchingCheck==UNMATCHED) && (n<2))){
		n++;
		LCD_sendCommand(LCD_CLEAR_COMMAND);
		LCD_displayString("Wrong Password");
		_delay_ms(200);
		LCD_sendCommand(LCD_CLEAR_COMMAND);
		LCD_displayString("plz enter pass:");
		LCD_moveCursor(1,0);
		getPassword(password);
		sendPassword(password);
		g_matchingCheck=UART_recieveByte();
	}
	if(n==2){
		LCD_sendCommand(LCD_CLEAR_COMMAND);
		LCD_displayString("Thief !!!");
		while(UART_recieveByte()!=RESET){};
	}
	else if (g_matchingCheck==MATCHED){
		LCD_sendCommand(LCD_CLEAR_COMMAND);
		LCD_displayString("Door is opening");
		while(UART_recieveByte()!=OPENED){};
		LCD_sendCommand(LCD_CLEAR_COMMAND);
		LCD_displayString("Door is opened");
		while(UART_recieveByte()!=CLOSING){};
		LCD_sendCommand(LCD_CLEAR_COMMAND);
		LCD_displayString("Door is closing");
		while(UART_recieveByte()!=CLOSED){};
	}
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}


void getPassword(uint8 * password){
	uint8 i=0,key;
	_delay_ms(100);
	key=KEYPAD_getPressedKey();
	while(key!=13){
		LCD_moveCursor(1,i);
		password[i]=key;
		i++;
		//LCD_intgerToString(key);
		LCD_displayString("*");
		_delay_ms(400);
		key=KEYPAD_getPressedKey();
	}
	password[i]=key;
}

void sendPassword(uint8 *password){
	uint8 i=0;
	while(password[i]!= 13){
		UART_sendByte(password[i]);
		i++;
	}
	UART_sendByte(password[i]);
}

void setPassword(uint8 *password)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	LCD_displayString("plz enter pass:");
	LCD_moveCursor(1,0);
	getPassword(password);
	sendPassword(password);
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	LCD_displayString("plz re-enter ps:");
	LCD_moveCursor(1,0);
	getPassword(password);
	sendPassword(password);
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	g_matchingCheck=UART_recieveByte();
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	/*Check from the Control ECU if 2 entered password is matched or not*/
	while(g_matchingCheck==UNMATCHED){
		/*as long as the 2 entered password is not matched display error on LCD
		 * and repeat setting password for first time*/
		LCD_displayString("Error Try again");
		_delay_ms(200);  /*Displaying time for error message*/
		LCD_sendCommand(LCD_CLEAR_COMMAND);
		LCD_displayString("plz enter pass:");
		LCD_moveCursor(1,0);
		getPassword(password);
		sendPassword(password);
		LCD_sendCommand(LCD_CLEAR_COMMAND);
		LCD_displayString("plz re-enter ps:");
		LCD_moveCursor(1,0);
		getPassword(password);
		sendPassword(password);
		g_matchingCheck=UART_recieveByte();
		LCD_sendCommand(LCD_CLEAR_COMMAND);	}
	/*If the 2 entered passwords are matched display successful */
	LCD_displayString("Successful !");
	_delay_ms(300);
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}
