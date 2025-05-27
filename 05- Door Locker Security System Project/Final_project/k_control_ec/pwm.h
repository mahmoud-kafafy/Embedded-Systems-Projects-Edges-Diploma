/*
 * pwm.h
 *
 *  Created on: Oct 8, 2022
 *      Author: HP
 */

#ifndef PWM_H_
#define PWM_H_

#include"std_types.h"
#define PERCENT_FACTOR  2.55  // 255-->100%   speed percent-->duty cycle

void Timer0_PWM_Init(uint8 duty_cycle_percent,uint8 out_pin);

#endif /* PWM_H_ */
