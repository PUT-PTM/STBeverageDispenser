#pragma once
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"

void GPIOD_Init();
void GPIOB_Init();
void TIM2_Init(int period, int prescaler);
void Init_Exti_Keyboard();
void TIM4_Init(int period, int prescaler);
void TIM5_Init(int period, int prescaler);
