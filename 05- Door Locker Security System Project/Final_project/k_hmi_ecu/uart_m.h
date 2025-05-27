/*
 * uart_m.h
 *
 *  Created on: Oct 13, 2022
 *      Author: HP
 */

#ifndef UART_M_H_
#define UART_M_H_

#include"std_types.h"

typedef enum {
  DISABLE,EVEN_PARITY=2,ODD_PARITY=3
}Parity_mode;

typedef enum {
	STOP1_BIT,STOP2_BIT
}Stop_Bit_No;

typedef enum {
	BITS_5,BITS_6,BITS_7,BITS_8
}Frame_Digits_No;


typedef struct {
	Parity_mode parity;
	Stop_Bit_No stop_bit;
	Frame_Digits_No no_digit;
	uint16 baud_rate;
}UART_Configuration;
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init( uint32 f_cpu ,UART_Configuration * config_ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(uint8 * data);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_recieveString(uint8 * recieve_arr); // Receive until $

#endif /* UART_M_H_ */
