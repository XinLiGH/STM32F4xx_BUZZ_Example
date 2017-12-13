/**
  ******************************************************************************
  * @file    BUZZ.h
  * @author  XinLi
  * @version v1.0
  * @date    24-October-2017
  * @brief   Header file for BUZZ.c module.
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

#ifndef __BUZZ_H
#define __BUZZ_H

#ifdef __cplusplus
extern "C" {
#endif

/* Header includes -----------------------------------------------------------*/
#include "stm32f4xx.h"

/* Macro definitions ---------------------------------------------------------*/
#define BUZZ_RCC_AHB1Periph_GPIO         RCC_AHB1Periph_GPIOB
#define BUZZ_GPIO                        GPIOB
#define BUZZ_GPIO_Pin                    GPIO_Pin_8

#define BUZZ_GPIO_PinSource              GPIO_PinSource8
#define BUZZ_GPIO_AF_TIM                 GPIO_AF_TIM4

#define BUZZ_RCC_APB1Periph_TIM          RCC_APB1Periph_TIM4
#define BUZZ_TIM                         TIM4

#define BUZZ_TIM_Prescaler               (83)  /*!< Clock divided to 1MHz. */
#define BUZZ_TIM_Period                  (249) /*!< 250us timer interrupt. */

#define BUZZ_TIM_OCPolarity              TIM_OCPolarity_High

#define BUZZ_TIM_OCInit                  TIM_OC3Init
#define BUZZ_TIM_OCPreloadConfig         TIM_OC3PreloadConfig

#define BUZZ_TIM_SetCompare              TIM_SetCompare3

#define BUZZ_TIM_IRQn                    TIM4_IRQn
#define BUZZ_TIM_IRQHandler              TIM4_IRQHandler
#define BUZZ_TIM_IRQ_PreemptionPriority  (0)
#define BUZZ_TIM_IRQ_SubPriority         (0)

/* Type definitions ----------------------------------------------------------*/
typedef enum
{
  BUZZ_Off     = 0,
  BUZZ_Ring    = 1,
  BUZZ_Drip    = 2,
  BUZZ_Warning = 3,
  BUZZ_Danger  = 4
}BUZZ_Status;

/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
void BUZZ_SetStatus(BUZZ_Status status);
BUZZ_Status BUZZ_GetStatus(void);

/* Function definitions ------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __BUZZ_H */
