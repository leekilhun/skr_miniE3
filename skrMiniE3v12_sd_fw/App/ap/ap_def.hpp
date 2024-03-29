/*
 * ap_def.h
 *
 *  Created on: Aug 26, 2023
 *      Author: gns2.lee
 */

#ifndef AP_AP_DEF_H_
#define AP_AP_DEF_H_


#include "exhw.h"




#include <array>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>

#ifndef errno_t
#define errno_t int
//typedef int errno_t;
#endif

#ifndef ERROR_SUCCESS
#define ERROR_SUCCESS 0
#endif

#ifndef ERROR_FAIL
#define ERROR_FAIL -1
#endif

#define GPIO_IN_STATE_ON    GPIO_PIN_RESET
#define GPIO_IN_STATE_OFF   GPIO_PIN_SET
#define GPIO_OUT_STATE_ON   GPIO_PIN_RESET
#define GPIO_OUT_STATE_OFF  GPIO_PIN_SET

//#define  APP_USE_MOTOR_HIGH
//#define APP_USE_MOTOR_CNT_TWO

#include "def_obj.hpp"
#include "def_err.hpp"

typedef void (*evt_cb)(void* obj, void* w_parm, void* l_parm);




#endif /* AP_AP_DEF_H_ */
