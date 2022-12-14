/*
 * hw.h
 *
 *  Created on: 2021. 12. 9.
 *      Author: gns2l
 */

#ifndef SRC_HW_HW_H_
#define SRC_HW_HW_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "hw_def.h"

#include "led.h"
#include "rtc.h"
#include "reset.h"
#include "button.h"
#include "cdc.h"
#include "usb.h"
#include "uart.h"
#include "cli.h"
#include "can.h"
#include "i2c.h"
#include "spi.h"
#include "log.h"
#include "flash.h"
#include "gpio.h"
#include "tim.h"


bool hwInit(void);


#ifdef __cplusplus
}
#endif


#endif /* SRC_HW_HW_H_ */
