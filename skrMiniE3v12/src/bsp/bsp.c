/*
 * bsp.c
 *
 *  Created on: 2021. 12. 9.
 *      Author: gns2l
 */




#include "bsp.h"
#include "hw_def.h"
#include "usb.h"


void SystemClock_Config(void);



bool bspInit(void)
{
  HAL_Init ();

  SystemClock_Config ();

  return true;
}

void delay(uint32_t ms)
{
#ifdef _USE_HW_RTOS
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
    osDelay(ms);
  }
  else
  {
    HAL_Delay(ms);
  }
#else
  HAL_Delay(ms);
#endif
}

uint32_t millis(void)
{
  return HAL_GetTick();
}



void bspDeInit(void)
{
  usbDeInit ();
  HAL_RCC_DeInit ();

  // Disable Interrupts
  //
  for (int i = 0; i < 8; i++)
  {
    NVIC->ICER[i] = 0xFFFFFFFF;
    __DSB ();
    __ISB ();
  }
  SysTick->CTRL = 0;
}



void SystemClock_Config(void)
{
  LL_FLASH_SetLatency (LL_FLASH_LATENCY_2);
  while (LL_FLASH_GetLatency () != LL_FLASH_LATENCY_2)
  {
  }
  LL_RCC_HSE_Enable ();

  /* Wait till HSE is ready */
  while (LL_RCC_HSE_IsReady () != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS (LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
  LL_RCC_PLL_Enable ();

  /* Wait till PLL is ready */
  while (LL_RCC_PLL_IsReady () != 1)
  {

  }
  LL_RCC_SetAHBPrescaler (LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler (LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler (LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource (LL_RCC_SYS_CLKSOURCE_PLL);

  /* Wait till System clock is ready */
  while (LL_RCC_GetSysClkSource () != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_SetSystemCoreClock (72000000);

  /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler ();
  }
  LL_RCC_SetUSBClockSource (LL_RCC_USB_CLKSOURCE_PLL_DIV_1_5);
}

void Error_Handler(void)
{
  while(1)
  {
  }

}
