/*
 * pwm.h
 *
 *  Created on: Jan 2, 2022
 *      Author: gns2l
 */

#ifndef SRC_COMMON_INC_HW_PWM_H_
#define SRC_COMMON_INC_HW_PWM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hw_def.h"

#ifdef _USE_HW_PWM



#define PWM_MAX_CH       HW_PWM_MAX_CH


bool pwmInit(void);
bool pwmIsInit(void);
void pwmWrite(uint8_t ch, uint16_t pwm_data);
uint16_t pwmRead(uint8_t ch);
uint16_t pwmGetMax(uint8_t ch);



#endif /*_USE_HW_PWM*/

#ifdef __cplusplus
}
#endif

#endif /* SRC_COMMON_INC_HW_PWM_H_ */
