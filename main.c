#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"


int counter=0;
struct Display_Info
{
	int target;

	int Target[4];
	int Current[4] = { 0, 3, 6, 6};
}Temperature;


void UpdateTarget()
{
    Temperature.Target[0] = Temperature.target / 1000;
    Temperature.Target[1] = ( Temperature.target / 100) %10;
    Temperature.Target[2] = ( Temperature.target / 10) %10;
    Temperature.Target[3] = Temperature.target%10;
}

void Temperature_Increment()
{
    if(Temperature.target < 90)
        Temperature.target+= 10;
    UpdateTarget();
}

void Temperature_Decrement()
{
    if (Temperature.target > 20)
        Temperature.target -= 10;
    UpdateTarget();
}


void TIM2_IRQHandler(void)
	{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
      {

      }
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}

void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
	   {
		Temperature_Increment();
		TIM_Cmd(TIM2,ENABLE);
		while(!TIM_GetFlagStatus(TIM2,TIM_FLAG_Update))
			{
			}
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);
		TIM_Cmd(TIM2,DISABLE);
		TIM2->CNT=0;
	    EXTI_ClearITPendingBit(EXTI_Line4);
	   }
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)
		{
		Temperature_Decrement();
		TIM_Cmd(TIM2,ENABLE);
		while(!TIM_GetFlagStatus(TIM2,TIM_FLAG_Update))
			{
			}
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);
		TIM_Cmd(TIM2,DISABLE);
		TIM2->CNT=0;
		EXTI_ClearITPendingBit(EXTI_Line5);
		}
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
		{
		GPIO_ToggleBits(GPIOD,GPIO_Pin_14);
		TIM_Cmd(TIM2,ENABLE);
		while(!TIM_GetFlagStatus(TIM2,TIM_FLAG_Update))
			{
			}
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);
		TIM_Cmd(TIM2,DISABLE);
		TIM2->CNT=0;
		EXTI_ClearITPendingBit(EXTI_Line6);
		             }
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)
		{
		GPIO_ToggleBits(GPIOD,GPIO_Pin_15);
		TIM_Cmd(TIM2,ENABLE);
		while(!TIM_GetFlagStatus(TIM2,TIM_FLAG_Update))
			{
			}
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);
		TIM_Cmd(TIM2,DISABLE);
		TIM2->CNT=0;
		EXTI_ClearITPendingBit(EXTI_Line7);
		}
}

void Display_Number(int number)
{
	switch(number)
	{
	case 0:
		GPIO_ResetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7);
		GPIO_SetBits(GPIOD,GPIO_Pin_8|GPIO_Pin_9);
		break;
	case 1:
		GPIO_SetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);
		GPIO_ResetBits(GPIOD,GPIO_Pin_1|GPIO_Pin_2);
		break;
	case 2:
		GPIO_ResetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_8);
		GPIO_SetBits(GPIOD,GPIO_Pin_2|GPIO_Pin_7);
		break;
	case 3:
		GPIO_ResetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_8);
		GPIO_SetBits(GPIOD,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_9);
		break;
	case 4:
		GPIO_SetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_9);
		GPIO_ResetBits(GPIOD,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_7|GPIO_Pin_8);
		break;
	case 5:
		GPIO_ResetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_7|GPIO_Pin_8);
		GPIO_SetBits(GPIOD,GPIO_Pin_1|GPIO_Pin_6|GPIO_Pin_9);
		break;
	case 6:
		GPIO_ResetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
		GPIO_SetBits(GPIOD,GPIO_Pin_1|GPIO_Pin_9);
		break;
	case 7:
		GPIO_ResetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);
		GPIO_SetBits(GPIOD,GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);
		break;
	case 8:
		GPIO_ResetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
		GPIO_SetBits(GPIOD,GPIO_Pin_9);
		break;
	case 9:
		GPIO_ResetBits(GPIOD,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_7|GPIO_Pin_8);
		GPIO_SetBits(GPIOD,GPIO_Pin_6|GPIO_Pin_9);
		break;
	}
}

void TIM3_IRQHandler(void)
{
 	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
 	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_4);
		GPIO_SetBits(GPIOD,GPIO_Pin_9);



 		switch(counter)
 		{
 		case 0:
 			if(Temperature.Target[0] != 0)
 			{
 			Display_Number(Temperature.Target[0]);
 			GPIO_SetBits(GPIOB,GPIO_Pin_0);
 			}
 			break;
 		case 1:
 			Display_Number(Temperature.Target[1]);
 			GPIO_SetBits(GPIOB,GPIO_Pin_1);
 			break;
 		case 2:
 			Display_Number(Temperature.Target[2]);
 			GPIO_ResetBits(GPIOD,GPIO_Pin_9);
 			GPIO_SetBits(GPIOB,GPIO_Pin_2);
 			break;
 		case 3:
 			Display_Number(Temperature.Target[3]);
 			GPIO_SetBits(GPIOB,GPIO_Pin_4);
 			break;
 		}
 		counter++;
 		counter %=4;
 	}
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
 	}


void GPIOD_Init()
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

		GPIO_InitTypeDef  GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0
				| GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3
				| GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8
				| GPIO_Pin_9|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
	}

void GPIOE_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =
			  GPIO_Pin_0 | GPIO_Pin_1
			| GPIO_Pin_2 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void Init_Tim2_With_Interruption(int period,int prescaler)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure2;
	TIM_TimeBaseStructure2.TIM_Period = period;
	TIM_TimeBaseStructure2.TIM_Prescaler = prescaler;
	TIM_TimeBaseStructure2.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure2.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure2);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVIC_InitStructure9;
	NVIC_InitStructure9.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure9.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure9.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure9.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure9);
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}


void Init_Exti_Keyboard()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource5);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource6);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource7);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitTypeDef NVIC_InitStructure1;
	NVIC_InitStructure1.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure1.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure1.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure1);

	EXTI_InitTypeDef EXTI_InitStructure1;
	EXTI_InitStructure1.EXTI_Line = EXTI_Line5;
	EXTI_InitStructure1.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure1.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure1.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure1);



	NVIC_InitTypeDef NVIC_InitStructure2;
	NVIC_InitStructure2.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure2);

	EXTI_InitTypeDef EXTI_InitStructure2;
	EXTI_InitStructure2.EXTI_Line = EXTI_Line6;
	EXTI_InitStructure2.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure2.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure2.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure2);

	NVIC_InitTypeDef NVIC_InitStructure4;
	NVIC_InitStructure4.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure4.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure4.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure4.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure4);

	EXTI_InitTypeDef EXTI_InitStructure4;
	EXTI_InitStructure4.EXTI_Line = EXTI_Line7;
	EXTI_InitStructure4.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure4.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure4.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure4);

}

void TIM3_Interruption_Enable(int period, int prescaler)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_Cmd(TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = period;
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

int main(void)
{
	SystemInit();

	GPIOD_Init();
	GPIOE_Init();
	TIM3_Interruption_Enable(83,999);
	Init_Exti_Keyboard();
	Init_Tim2_With_Interruption(8399,499);
	Temperature.Target[0] = 1;
	Temperature.Target[1] = 2;
	Temperature.Target[2] = 3;
	Temperature.Target[3] = 4;

	for(;;)
	{

	}

}
