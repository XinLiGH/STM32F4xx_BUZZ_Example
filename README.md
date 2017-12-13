# STM32F4xx_BUZZ_Example

使用STM32F4的定时器TIM产生PWM，来实现无源蜂鸣器的驱动。适用于STM32F4全部芯片。

## 开发环境

* 固件库：STM32F4xx_DSP_StdPeriph_Lib_V1.8.0
* 编译器：ARMCC V5.06
* IDE：Keil uVision5
* 操作系统：Windows 10 专业版

## API

* void BUZZ_SetStatus(BUZZ_Status status)
* BUZZ_Status BUZZ_GetStatus(void)

## 注意

修改接口需要注意，蜂鸣器的驱动方式和使用的TIM。对应修改PWM输出电平和TIM时钟配置函数。
