#include "IRQHandlers.h"

int counter = 0;
int set_temperature = 0;

void TIM2_IRQHandler(void)
	{
		if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
			{
			}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}

void TIM5_IRQHandler(void)
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
			{
				GPIO_ToggleBits(GPIOD,GPIO_Pin_14);
			}
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}

void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
	   {
			set_temperature = 1;
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
			set_temperature = 1;
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
			set_temperature = 0;
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

void TIM4_IRQHandler(void)
{
 	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
 	{
 		if(set_temperature == 1)
 		{
 			Temperature.current = Temperature.target;
 			UpdateCurrent();
 		}
		GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_4);
		GPIO_SetBits(GPIOD,GPIO_Pin_9);

 		switch(counter)
 		{
 		case 0:
 			if(Temperature.Current[0] != 0)
 				{
 					Display_Number(Temperature.Current[0]);
 					GPIO_SetBits(GPIOB,GPIO_Pin_0);
 				}
 			break;
 		case 1:
 			Display_Number(Temperature.Current[1]);
 			GPIO_SetBits(GPIOB,GPIO_Pin_1);
 			break;
 		case 2:
 			Display_Number(Temperature.Current[2]);
 			GPIO_ResetBits(GPIOD,GPIO_Pin_9);
 			GPIO_SetBits(GPIOB,GPIO_Pin_2);
 			break;
 		case 3:
 			Display_Number(Temperature.Current[3]);
 			GPIO_SetBits(GPIOB,GPIO_Pin_4);
 			break;
 		}
 		counter++;
 		counter %=4;
 	}
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
 }
