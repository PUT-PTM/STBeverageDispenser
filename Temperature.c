#include "Temperature.h"

void UpdateTarget()
{
    Temperature.Target[0] = Temperature.target / 1000;
    Temperature.Target[1] = ( Temperature.target / 100) %10;
    Temperature.Target[2] = ( Temperature.target / 10) %10;
    Temperature.Target[3] = Temperature.target%10;
}

void UpdateCurrent()
{
    Temperature.Current[0] = Temperature.current / 1000;
    Temperature.Current[1] = ( Temperature.current / 100) %10;
    Temperature.Current[2] = ( Temperature.current / 10) %10;
    Temperature.Current[3] = Temperature.current%10;
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
