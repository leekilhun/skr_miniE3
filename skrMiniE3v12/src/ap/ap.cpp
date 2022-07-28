/*
 * ap.cpp
 *
 *  Created on: 2022. 7. 24.
 *      Author: gns2l
 */


#include "ap.h"

static void threadLed(void const *argument);

void apInit(void)
{
  cliOpen(_DEF_UART2, 115200);


  osThreadDef(threadLed, threadLed, _HW_DEF_RTOS_THREAD_PRI_LED, 0, _HW_DEF_RTOS_THREAD_MEM_LED);
  if (osThreadCreate(osThread(threadLed), NULL) != NULL)
  {
    logPrintf("threadLed \t\t: OK\r\n");
  }
  else
  {
    logPrintf("threadLed \t\t: Fail\r\n");
  }

}


void apMain(void)
{
  while(1)
  {
    cliMain();
  }

}




void threadLed(void const *argument)
{
  UNUSED(argument);
  ledOff(_DEF_LED1);
  uint32_t pre_main_ms = millis();

  while(1)
  {

    if (millis() - pre_main_ms >= 1000)
    {
      pre_main_ms = millis();
      ledToggle(_DEF_LED1);
    }

  }
}

