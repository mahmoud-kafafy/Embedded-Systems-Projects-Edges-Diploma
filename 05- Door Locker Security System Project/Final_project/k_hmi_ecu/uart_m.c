/*
 * uart_m.c
 *
 *  Created on: Oct 13, 2022
 *      Author: HP
 */
#include<avr/io.h>
#include"uart_m.h"
#include"common_macros.h"

void UART_init( uint32 f_cpu ,UART_Configuration * config_ptr)
{
	SET_BIT(UCSRA,U2X);
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRC,URSEL);

	UCSRC = (UCSRC & 0XCF) | ((config_ptr->parity) << 4);
	UCSRC = (UCSRC & 0XF7) | ((config_ptr->stop_bit) << 3);
	UCSRC = (UCSRC & 0XFC) | ((config_ptr->no_digit) << 1);

	uint16 ubrr_value = (uint16)(((f_cpu / (config_ptr->baud_rate * 8UL))) - 1);
	UBRRL=ubrr_value;
	UBRRH=ubrr_value>>8;
}

void UART_sendByte(uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	UDR = data;
	/* another method**
	 * UDR = data;
	 * while(CLEAR_BIT(UCSRA,TXC)){}
	 */
}

uint8 UART_recieveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	return UDR;
}

void UART_sendString(uint8 * data)
{
	uint8  i =0 ;
	while(data[i] != '\0')
	{
		UART_sendByte(data[i]);
		i++;
	}
}

void UART_recieveString(uint8 * recieve_arr)
{
	uint8 i = 0;
	recieve_arr[i] = UART_recieveByte();
	while(recieve_arr[i] != '$')
	{
		i++;
		recieve_arr[i] = UART_recieveByte();
	}

	recieve_arr[i] = '\0';
}

