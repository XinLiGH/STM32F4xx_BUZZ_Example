/**
  ******************************************************************************
  * @file    main.c
  * @author  XinLi
  * @version v1.0
  * @date    24-October-2017
  * @brief   Main program body.
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
#include "main.h"
#include "Delay.h"
#include "BUZZ.h"

/* Macro definitions ---------------------------------------------------------*/
/* Type definitions ----------------------------------------------------------*/
/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
/* Function definitions ------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None.
  * @return None.
  */
int main(void)
{
  for(;;)
  {
    Delay_s(5);
    BUZZ_SetStatus(BUZZ_Drip);
    Delay_s(5);
    BUZZ_SetStatus(BUZZ_Ring);
    Delay_s(5);
    BUZZ_SetStatus(BUZZ_Warning);
    Delay_s(5);
    BUZZ_SetStatus(BUZZ_Danger);
    Delay_s(5);
    BUZZ_SetStatus(BUZZ_Off);
  }
}
