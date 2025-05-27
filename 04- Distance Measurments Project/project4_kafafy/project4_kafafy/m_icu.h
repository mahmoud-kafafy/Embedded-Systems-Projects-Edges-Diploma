/*
 * m_icu.h
 *
 *  Created on: Oct 15, 2022
 *      Author: HP
 */

#ifndef M_ICU_H_
#define M_ICU_H_
#include"std_types.h"

typedef enum {
	NO_CLK,CLK_CPU,CLK_8,CLK_64,CLK_256,CLK_1024
}Icu_Prescular;

typedef enum {
	FALLING_EDGE,RISING_EDGE
}Icu_EdgeCapture;

typedef struct {
	Icu_Prescular clk;
	Icu_EdgeCapture edge;
}Icu_configuration;


/*PROTOTYPES*/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void Icu_init(Icu_configuration * config );

/*
 * Description: Function to set the required edge detection.
 */
void Icu_EdgeDetectionType(Icu_EdgeCapture edge);
/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 Icu_getInputCaptureValue(void);
/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void Icu_ClearTime();
/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void Icu_DeInit(void);
/*
 * Description: Function to set the Call Back function address.
 */
void Icu_CallBackFunction (void (*ptr2func)(void));
#endif /* M_ICU_H_ */
