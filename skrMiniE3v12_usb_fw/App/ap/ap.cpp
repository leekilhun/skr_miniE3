/*
 * ap.c
 *
 *  Created on: Dec 27, 2021
 *      Author: gns2.lee
 */



#include "ap.hpp"



static void apISR_1ms(void *arg);
static void apISR_10ms(void *arg);



void apInit(void)
{

	/**
	 * @brief
	 * register the function to the 1ms interrupt sw-timer.
	 */
	{
		swtimer_handle_t timer_ch;
		timer_ch = swtimerGetHandle();
		if (timer_ch >= 0)
		{
			swtimerSet(timer_ch, 1, LOOP_TIME, apISR_1ms, NULL);
			swtimerStart(timer_ch);
		}
		else
		{
			LOG_PRINT("[NG] 1ms swtimerGetHandle()");
		}

		timer_ch = swtimerGetHandle();
		if (timer_ch >= 0)
		{
			swtimerSet(timer_ch, 10, LOOP_TIME, apISR_10ms, NULL);
			swtimerStart(timer_ch);
		}
		else
		{
			LOG_PRINT("[NG] 10ms swtimerGetHandle()");
		}
	}
	// end of swtimer

#ifdef _USE_HW_CLI
	cliOpen(HW_CLI_CH, 115200);
#endif




}




void apMain(void)
{
	uint32_t pre_time;
	pre_time = millis();
	while(1)
	{
		if (millis()-pre_time >= 1'000)
		{
			pre_time = millis();
		}

#ifdef _USE_HW_CLI
		cliMain();
#endif

	}
}



void updateLED()
{
  /**
   * @brief
   * status led
   */
  {
    static uint32_t pre_time_update_led;

    if (millis() - pre_time_update_led >= 500)
    {
      pre_time_update_led = millis();
      HAL_GPIO_TogglePin(status_GPIO_Port, status_Pin);
    }
  }
  // end of status led

}



void apISR_1ms(void *arg)
{
}

void apISR_10ms(void *arg)
{
  updateLED();
}





