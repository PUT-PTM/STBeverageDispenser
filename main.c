#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_onewire.h"
#include "tm_stm32f4_ds18b20.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "init.h"
#include "IRQHandlers.h"
#include "Temperature.h"

uint8_t byte;

#define K1 50
#define K2 1

uint8_t devices, i, j, count, alarm_count;
uint8_t device[8];
uint8_t alarm_device[8];
float temps;

int wynik;
int main(void)
{
	int integral = 0;
	SystemInit();

	GPIOD_Init();
	GPIOB_Init();

	Init_Exti_Keyboard();
	TIM2_Init(8399,499);
	TIM4_Init(83,999);
	TIM5_Init_PWM(999,83999);
	Temperature.Target[0] = 0;
	Temperature.Target[1] = 3;
	Temperature.Target[2] = 0;
	Temperature.Target[3] = 0;

    TM_OneWire_t OneWire1;


    TM_DELAY_Init();

    TM_OneWire_Init(&OneWire1, GPIOA, GPIO_Pin_7);


    devices = TM_OneWire_First(&OneWire1);
        TM_OneWire_GetFullROM(&OneWire1, device);


        TM_DS18B20_SetResolution(&OneWire1, device, TM_DS18B20_Resolution_12bits);

        TM_DS18B20_SetAlarmHighTemperature(&OneWire1, device, 100);

            TM_DS18B20_DisableAlarmTemperature(&OneWire1, device);
            Temperature.target = 900;

int sum;

while(1){


		        TM_DS18B20_StartAll(&OneWire1);

		        while (!TM_DS18B20_AllDone(&OneWire1));

		        TM_DS18B20_Read(&OneWire1, device, &temps);

		        Temperature.current = (int)(temps*10);
		        UpdateCurrent();
		        sum = Temperature.target - Temperature.current;
		        if(integral < 2000 && sum>0)
		        	integral += sum;
		        else if(sum<=0)
		        {
		        	integral += sum;
		        }
		        wynik = (K1*(sum) + K2*integral);
		        if (wynik < 4000 && wynik >= 0)
		        {
		        	wynik = wynik/10;
			        TIM5->CCR2 =wynik;
		        }
		        else if (wynik < 0){
		        	TIM5->CCR2 = 0;
		        }
		        else{
		        	 TIM5-> CCR2 = 400;
		        }
		        Delayms(1000);
}
 }
