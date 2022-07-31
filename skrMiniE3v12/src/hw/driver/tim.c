/*
 * tim.c
 *
 *  Created on: 2022. 7. 31.
 *      Author: gns2l
 */




#include "tim.h"

#ifdef _USE_HW_TIM

TIM_HandleTypeDef htim2,htim3,htim4, htim5;

static TIM_HandleTypeDef *p_tim_handle[TIM_MAX_CH] =
		{
				&htim2,&htim3,&htim4,&htim5
		};




tim_tbl_t  tim_tbl[TIM_MAX_CH];


bool timInit(void)
{
	for (int i=0; i<TIM_MAX_CH; i++)
	{
		tim_tbl[i].pHandle = NULL;
		tim_tbl[i].func_callback = NULL;
		tim_tbl[i].act_ch_bit = 0x00;
		tim_tbl[i].is_start = false;
		tim_tbl[i].sConfig.OCFastMode = 0;
		tim_tbl[i].sConfig.OCIdleState = 0;
		tim_tbl[i].sConfig.OCMode = 0;
		tim_tbl[i].sConfig.OCNIdleState = 0;
		tim_tbl[i].sConfig.OCNPolarity = 0;
		tim_tbl[i].sConfig.Pulse = 0;
		tim_tbl[i].channel[0] = TIM_CHANNEL_1;
		tim_tbl[i].channel[1] = TIM_CHANNEL_2;
		tim_tbl[i].channel[2] = TIM_CHANNEL_3;
		tim_tbl[i].channel[3] = TIM_CHANNEL_4;

	}

	return true;
}


tim_tbl_t	* timGetData(uint8_t ch)
{
	return &tim_tbl[ch];
}


bool timStart(uint8_t ch)
{
	bool ret = true;
	tim_tbl_t *p_tim;

	p_tim 					= &tim_tbl[ch];
	p_tim->pHandle 	= p_tim_handle[ch];

	TIM_MasterConfigTypeDef sMasterConfig = {0};

	switch (ch)
	{
		case _DEF_TIM1:
       /* timer clock interval 1us, initial event time 1ms  */
			p_tim->pHandle->Instance 								= TIM2;
			p_tim->pHandle->Init.Prescaler 					= (uint32_t)(SystemCoreClock/10000000)-1;
			p_tim->pHandle->Init.CounterMode 				= TIM_COUNTERMODE_UP;
			p_tim->pHandle->Init.Period 						= (10000-1);
			p_tim->pHandle->Init.ClockDivision 			= TIM_CLOCKDIVISION_DIV1;
			p_tim->pHandle->Init.AutoReloadPreload 	= TIM_AUTORELOAD_PRELOAD_ENABLE;
			if (HAL_TIM_Base_Init(p_tim->pHandle) != HAL_OK)
			{
			  ret = false;
			}

			sMasterConfig.MasterOutputTrigger       = TIM_TRGO_RESET;
			sMasterConfig.MasterSlaveMode           = TIM_MASTERSLAVEMODE_DISABLE;
			if (HAL_TIMEx_MasterConfigSynchronization(p_tim->pHandle, &sMasterConfig) != HAL_OK)
			{
			  ret = false;
			}

			break;

		case _DEF_TIM2:
		  /* timer clock interval 1us, initial event time 1ms  */
		  p_tim->pHandle->Instance                = TIM3;
		  p_tim->pHandle->Init.Prescaler          = (uint32_t)(SystemCoreClock/10000000)-1;
		  p_tim->pHandle->Init.CounterMode        = TIM_COUNTERMODE_UP;
		  p_tim->pHandle->Init.Period             = (10000-1);
		  p_tim->pHandle->Init.ClockDivision      = TIM_CLOCKDIVISION_DIV1;
		  p_tim->pHandle->Init.AutoReloadPreload  = TIM_AUTORELOAD_PRELOAD_ENABLE;
		  if (HAL_TIM_Base_Init(p_tim->pHandle) != HAL_OK)
		  {
		    ret = false;
		  }

		  sMasterConfig.MasterOutputTrigger       = TIM_TRGO_RESET;
		  sMasterConfig.MasterSlaveMode           = TIM_MASTERSLAVEMODE_DISABLE;
		  if (HAL_TIMEx_MasterConfigSynchronization(p_tim->pHandle, &sMasterConfig) != HAL_OK)
		  {
		    ret = false;
		  }

		  break;

		case _DEF_TIM3:
		  /* timer clock interval 1us, initial event time 1ms  */
		  p_tim->pHandle->Instance                = TIM4;
		  p_tim->pHandle->Init.Prescaler          = (uint32_t)(SystemCoreClock/10000000)-1;
		  p_tim->pHandle->Init.CounterMode        = TIM_COUNTERMODE_UP;
		  p_tim->pHandle->Init.Period             = (10000-1);
		  p_tim->pHandle->Init.ClockDivision      = TIM_CLOCKDIVISION_DIV1;
		  p_tim->pHandle->Init.AutoReloadPreload  = TIM_AUTORELOAD_PRELOAD_ENABLE;
		  if (HAL_TIM_Base_Init(p_tim->pHandle) != HAL_OK)
		  {
		    ret = false;
		  }

		  sMasterConfig.MasterOutputTrigger       = TIM_TRGO_RESET;
		  sMasterConfig.MasterSlaveMode           = TIM_MASTERSLAVEMODE_DISABLE;
		  if (HAL_TIMEx_MasterConfigSynchronization(p_tim->pHandle, &sMasterConfig) != HAL_OK)
		  {
		    ret = false;
		  }

		  break;

		case _DEF_TIM4:
		  /* timer clock interval 1us, initial event time 1ms  */
		  p_tim->pHandle->Instance                = TIM5;
		  p_tim->pHandle->Init.Prescaler          = (uint32_t)(SystemCoreClock/10000000)-1;
		  p_tim->pHandle->Init.CounterMode        = TIM_COUNTERMODE_UP;
		  p_tim->pHandle->Init.Period             = (10000-1);
		  p_tim->pHandle->Init.ClockDivision      = TIM_CLOCKDIVISION_DIV1;
		  p_tim->pHandle->Init.AutoReloadPreload  = TIM_AUTORELOAD_PRELOAD_ENABLE;
		  if (HAL_TIM_Base_Init(p_tim->pHandle) != HAL_OK)
		  {
		    ret = false;
		  }

		  sMasterConfig.MasterOutputTrigger       = TIM_TRGO_RESET;
		  sMasterConfig.MasterSlaveMode           = TIM_MASTERSLAVEMODE_DISABLE;
		  if (HAL_TIMEx_MasterConfigSynchronization(p_tim->pHandle, &sMasterConfig) != HAL_OK)
		  {
		    ret = false;
		  }

		  break;

	}


	p_tim->is_start = true;
	return ret;
}


void timAttachCallBackFunc(uint8_t ch, void (*func)())
{
  tim_tbl[ch].func_callback = func;
}

void timEnableISR(uint8_t ch)
{
  switch (ch)
  {
    case _DEF_TIM1:
      if (HAL_TIM_Base_Start_IT(&htim2) != HAL_OK)
      {
        /* Error */
      }
      break;
    case _DEF_TIM2:
      if (HAL_TIM_Base_Start_IT(&htim3) != HAL_OK)
      {
        /* Error */
      }
      break;
    case _DEF_TIM3:
      if (HAL_TIM_Base_Start_IT(&htim4) != HAL_OK)
      {
        /* Error */
      }
      break;
    case _DEF_TIM4:
      if (HAL_TIM_Base_Start_IT(&htim5) != HAL_OK)
      {
        /* Error */
      }
      break;
  }
}

void timDisableISR(uint8_t ch)
{
  switch (ch)
  {
    case _DEF_TIM1:
      if (HAL_TIM_Base_Stop_IT(&htim2) != HAL_OK)
      {
        /* Error */
      }
      break;
    case _DEF_TIM2:
      if (HAL_TIM_Base_Stop_IT(&htim3) != HAL_OK)
      {
        /* Error */
      }
      break;
    case _DEF_TIM3:
      if (HAL_TIM_Base_Stop_IT(&htim4) != HAL_OK)
      {
        /* Error */
      }
      break;
    case _DEF_TIM4:
      if (HAL_TIM_Base_Stop_IT(&htim5) != HAL_OK)
      {
        /* Error */
      }
      break;
  }
}


void timResetCnt(uint8_t ch)
{

  switch (ch)
  {
    case _DEF_TIM1:
      htim2.Instance->CR1 |= 1;
      htim2.Instance->CNT = 0;
      break;
    case _DEF_TIM2:
      htim3.Instance->CR1 |= 1;
      htim3.Instance->CNT = 0;
      break;
    case _DEF_TIM3:
      htim4.Instance->CR1 |= 1;
      htim4.Instance->CNT = 0;
      break;
    case _DEF_TIM4:
      htim5.Instance->CR1 |= 1;
      htim5.Instance->CNT = 0;
      break;
  }
}


bool timChangePrescale(uint8_t ch,uint32_t psc)
{
  switch (ch)
  {
    case _DEF_TIM1:
      timDisableISR(_DEF_TIM1);
      htim2.Instance->PSC = psc;
      timEnableISR(_DEF_TIM1);
      break;
    case _DEF_TIM2:
      timDisableISR(_DEF_TIM2);
      htim3.Instance->PSC = psc;
      timEnableISR(_DEF_TIM2);
      break;
    case _DEF_TIM3:
      timDisableISR(_DEF_TIM3);
      htim4.Instance->PSC = psc;
      timEnableISR(_DEF_TIM3);
      break;
    case _DEF_TIM4:
      timDisableISR(_DEF_TIM4);
      htim5.Instance->PSC = psc;
      timEnableISR(_DEF_TIM4);
      break;
  }

  return true;
}




/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
}


void TIM3_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim3);
}


void TIM4_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim4);
}


void TIM5_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim5);
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

#ifdef _USE_HW_RTOS
	HAL_IncTick();
#endif

  if(htim->Instance==TIM2)
  {
    if (tim_tbl[_DEF_TIM1].func_callback != NULL )
    {
      (*tim_tbl[_DEF_TIM1].func_callback)();
    }
  }
  else if(htim->Instance==TIM3)
  {
    if (tim_tbl[_DEF_TIM2].func_callback != NULL )
    {
      (*tim_tbl[_DEF_TIM2].func_callback)();
    }
  }
  else if(htim->Instance==TIM4)
  {
    if (tim_tbl[_DEF_TIM3].func_callback != NULL )
    {
      (*tim_tbl[_DEF_TIM3].func_callback)();
    }
  }
  else if(htim->Instance==TIM5)
  {
    if (tim_tbl[_DEF_TIM4].func_callback != NULL )
    {
      (*tim_tbl[_DEF_TIM4].func_callback)();
    }
  }

}



void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    /* TIM2 interrupt Init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  }
  else if(tim_baseHandle->Instance==TIM3)
  {
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

    /* TIM3 interrupt Init */
    HAL_NVIC_SetPriority(TIM3_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  }
  else if(tim_baseHandle->Instance==TIM4)
  {
    /* TIM4 clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();

    /* TIM4 interrupt Init */
    HAL_NVIC_SetPriority(TIM4_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
  }
  else if(tim_baseHandle->Instance==TIM5)
  {
    /* TIM5 clock enable */
    __HAL_RCC_TIM5_CLK_ENABLE();

    /* TIM5 interrupt Init */
    HAL_NVIC_SetPriority(TIM5_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(TIM5_IRQn);
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /* TIM2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM2_IRQn);
  }
  else if(tim_baseHandle->Instance==TIM3)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

    /* TIM3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
  }
  else if(tim_baseHandle->Instance==TIM4)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM4_CLK_DISABLE();

    /* TIM4 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM4_IRQn);
  }
  else if(tim_baseHandle->Instance==TIM5)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM5_CLK_DISABLE();

    /* TIM5 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM5_IRQn);
  }
}


#endif /*_USE_HW_TIM*/

