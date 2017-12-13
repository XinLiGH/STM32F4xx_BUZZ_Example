/**
  ******************************************************************************
  * @file    BUZZ.c
  * @author  XinLi
  * @version v1.0
  * @date    24-October-2017
  * @brief   BUZZ module driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>Copyright &copy; 2017 XinLi</center></h2>
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <https://www.gnu.org/licenses/>.
  *
  ******************************************************************************
  */

/* Header includes -----------------------------------------------------------*/
#include "BUZZ.h"
#include <stdbool.h>

/* Macro definitions ---------------------------------------------------------*/
/* Type definitions ----------------------------------------------------------*/
/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
static __IO BUZZ_Status buzzStatus = BUZZ_Off;
static __IO int         buzzCount  = 0;

/* Function declarations -----------------------------------------------------*/
static void BUZZ_PwmInit(void);
static void BUZZ_NvicInit(void);
static void BUZZ_Init(void);

/* Function definitions ------------------------------------------------------*/

/**
  * @brief  Buzz pwm initializes.
  * @param  None.
  * @return None.
  */
static void BUZZ_PwmInit(void)
{
  GPIO_InitTypeDef        GPIO_InitStructure    = {0};
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = {0};
  TIM_OCInitTypeDef       TIM_OCInitStructure   = {0};
  
  RCC_AHB1PeriphClockCmd(BUZZ_RCC_AHB1Periph_GPIO, ENABLE);
  RCC_APB1PeriphClockCmd(BUZZ_RCC_APB1Periph_TIM, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin   = BUZZ_GPIO_Pin;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(BUZZ_GPIO, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(BUZZ_GPIO, BUZZ_GPIO_PinSource, BUZZ_GPIO_AF_TIM);
  
  TIM_TimeBaseStructure.TIM_Prescaler     = BUZZ_TIM_Prescaler;
  TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period        = BUZZ_TIM_Period;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(BUZZ_TIM, &TIM_TimeBaseStructure);
  
  TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse       = 0;
  TIM_OCInitStructure.TIM_OCPolarity  = BUZZ_TIM_OCPolarity;
  BUZZ_TIM_OCInit(BUZZ_TIM, &TIM_OCInitStructure);
  
  BUZZ_TIM_OCPreloadConfig(BUZZ_TIM, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(BUZZ_TIM, ENABLE);
  TIM_ITConfig(BUZZ_TIM, TIM_IT_Update, ENABLE);
  TIM_Cmd(BUZZ_TIM, ENABLE);
}

/**
  * @brief  Buzz nvic initializes.
  * @param  None.
  * @return None.
  */
static void BUZZ_NvicInit(void)
{
  NVIC_InitTypeDef NVIC_InitStructure = {0};
  
  NVIC_InitStructure.NVIC_IRQChannel                   = BUZZ_TIM_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = BUZZ_TIM_IRQ_PreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = BUZZ_TIM_IRQ_SubPriority;
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Buzz initializes.
  * @param  None.
  * @return None.
  */
static void BUZZ_Init(void)
{
  static bool init_flag = false;
  
  if(init_flag == false)
  {
    init_flag = true;
    
    BUZZ_PwmInit();
    BUZZ_NvicInit();
  }
}

/**
  * @brief  Set buzz status.
  * @param  [in] status: Buzz status.
  * @return None.
  */
void BUZZ_SetStatus(BUZZ_Status status)
{
  if(status != buzzStatus)
  {
    buzzStatus = status;
    buzzCount  = 0;
    BUZZ_Init();
  }
}

/**
  * @brief  Get buzz status.
  * @param  None.
  * @return Buzz status.
  */
BUZZ_Status BUZZ_GetStatus(void)
{
  return buzzStatus;
}

/**
  * @brief  This function handles TIM Handler.
  * @param  None.
  * @return None.
  */
void BUZZ_TIM_IRQHandler(void)
{
  if(TIM_GetITStatus(BUZZ_TIM, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(BUZZ_TIM, TIM_IT_Update);
    
    if(buzzStatus == BUZZ_Off)
    {
      buzzCount = 0;
      BUZZ_TIM_SetCompare(BUZZ_TIM, 0);
    }
    else if(buzzStatus == BUZZ_Ring)
    {
      buzzCount = 0;
      BUZZ_TIM_SetCompare(BUZZ_TIM, (BUZZ_TIM_Period + 1) / 2);
    }
    else if(buzzStatus == BUZZ_Drip)
    {
      if(buzzCount > 1999)
      {
        if(buzzCount > 3999)
        {
          buzzCount  = 0;
          buzzStatus = BUZZ_Off;
          BUZZ_TIM_SetCompare(BUZZ_TIM, 0);
        }
        else
        {
          buzzCount++;
          BUZZ_TIM_SetCompare(BUZZ_TIM, 0);
        }
      }
      else
      {
        buzzCount++;
        BUZZ_TIM_SetCompare(BUZZ_TIM, (BUZZ_TIM_Period + 1) / 2);
      }
    }
    else if(buzzStatus == BUZZ_Warning)
    {
      if(buzzCount > 1999)
      {
        if(buzzCount > 3999)
        {
          buzzCount = 0;
          BUZZ_TIM_SetCompare(BUZZ_TIM, (BUZZ_TIM_Period + 1) / 2);
        }
        else
        {
          buzzCount++;
          BUZZ_TIM_SetCompare(BUZZ_TIM, 0);
        }
      }
      else
      {
        buzzCount++;
        BUZZ_TIM_SetCompare(BUZZ_TIM, (BUZZ_TIM_Period + 1) / 2);
      }
    }
    else
    {
      if(buzzCount > 999)
      {
        if(buzzCount > 1999)
        {
          buzzCount = 0;
          BUZZ_TIM_SetCompare(BUZZ_TIM, (BUZZ_TIM_Period + 1) / 2);
        }
        else
        {
          buzzCount++;
          BUZZ_TIM_SetCompare(BUZZ_TIM, 0);
        }
      }
      else
      {
        buzzCount++;
        BUZZ_TIM_SetCompare(BUZZ_TIM, (BUZZ_TIM_Period + 1) / 2);
      }
    }
  }
}
