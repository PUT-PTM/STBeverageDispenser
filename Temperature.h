#pragma once
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"

struct Display_Info
{
	int target;
	int current;
	int Target[4];
	int Current[4];
}Temperature;

void UpdateTarget();
void UpdateCurrent();
void Temperature_Increment();
void Temperature_Decrement();
void Display_Number();
