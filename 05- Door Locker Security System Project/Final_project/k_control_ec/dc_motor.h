/*
 * dc_motor.h
 *
 *  Created on: Oct 8, 2022
 *      Author: HP
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include"std_types.h"

typedef enum {
	STOP,CW,CCW
}DcMotor_State;

#define MOTOR_IN1_PORT     PORTB_ID
#define MOTOR_IN1_PIN      PIN0_ID
#define MOTOR_IN2_PORT     PORTB_ID
#define MOTOR_IN2_PIN      PIN1_ID
#define MOTOR_ENABLE_PORT  PORTB_ID
#define MOTOR_ENABLE_PIN   PIN3_ID

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);
#endif /* DC_MOTOR_H_ */
