/*
 * hw.c
 *
 *  Created on: 2021. 12. 9.
 *      Author: gns2l
 */



#include "hw.h"



bool hwInit(void)
{
  bool ret = true;

#ifndef _USE_HW_RTOS
  ret &= bspInit();
#endif

  ret &= cliInit();

  ret &= usbInit();

  ret &= uartInit();

  ret &= flashInit();

  ret &= ledInit();

  ret &= gpioInit();

  //ret &= rtcInit();
  //ret &= resetInit();


#ifdef _USE_HW_TIM
  ret &= timInit();
#endif


  //ret &= buttonInit();
  //ret &= gpioInit();

  ret &= logInit();

  uartOpen(_DEF_UART1, 115200);

  logOpen(_DEF_UART1, 115200);
  logPrintf("\r\n[ Firmware Begin... ]\r\n");

  //ret &= spiInit();
  //ret &= i2cInit();
  //ret &= canInit();
  return ret;
}
