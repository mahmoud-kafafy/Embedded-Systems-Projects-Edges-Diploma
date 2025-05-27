/*
 * dc_motor.c
 *
 *  Created on: Oct 8, 2022
 *      Author: HP
 */
#include"m_gpio.h"
#include"dc_motor.h"
#include"pwm.h"

void DcMotor_Init(void)
{
	/*Setup pin directions of motor*/
	GPIO_setupPinDirection(MOTOR_IN1_PORT, MOTOR_IN1_PIN,PIN_OUTPUT );
	GPIO_setupPinDirection(MOTOR_IN2_PORT, MOTOR_IN2_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_ENABLE_PORT, MOTOR_ENABLE_PIN,PIN_OUTPUT);

}

void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{

	switch(state)
	{

	case STOP:
		GPIO_writePin(MOTOR_IN1_PORT,  MOTOR_IN1_PIN, LOGIC_LOW);
		GPIO_writePin(MOTOR_IN2_PORT,  MOTOR_IN2_PIN, LOGIC_LOW);
		Timer0_PWM_Init (0,MOTOR_ENABLE_PIN);
		break;
	case CW:
		GPIO_writePin(MOTOR_IN1_PORT,  MOTOR_IN1_PIN, LOGIC_LOW);
		GPIO_writePin(MOTOR_IN2_PORT,  MOTOR_IN2_PIN, LOGIC_HIGH);
		Timer0_PWM_Init (speed,MOTOR_ENABLE_PIN);
		break;
	case CCW:

		GPIO_writePin(MOTOR_IN1_PORT,  MOTOR_IN1_PIN, LOGIC_HIGH);
		GPIO_writePin(MOTOR_IN2_PORT,  MOTOR_IN2_PIN, LOGIC_LOW);
		Timer0_PWM_Init (speed,MOTOR_ENABLE_PIN);
		break;
	}


}
