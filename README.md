# STBeverageDispenser

## Overview
This project is the back-end code for our electric homemade teapot that's keeping your beverage at specified temperature. The teapot has an extra solenoid valve which allows to fill a cup with the button on STM.
## Description
The main functionality of this project is the ability to keep the best temperature for your beverage. All you have to do is choose the temperature. Desired temperature is maintained by a PI controller and can be adjusted with two buttons. Current temperature is always shown on the segment display. Third button is used to open the solenoid valve and pour your beverage into a cup. 
Project components:
- STM32 microcontroller
- Power module with two relays and optically isolated 5V input - RL02_ISO
- Temperature sensor - DS18B20
- Water heater - 1000W/230AC
- Solenoid valve DC 12V
- 4x8 segment display
- Waveshare 8 Push Buttons module  

Electrical diagram:  
![alt tag](https://i.imgur.com/zinWzyq.png)  

## Tools
- CoIDE v1.7.8
- Language C
## How to run
Initially, you need to connect all the components.  
Pin layout:

stm32 | 4x8 segment display
---|---
PD0	|	a
PD1	|	b
PD2	|	c
PD3	|	d
PD6	|	e
PD7	|	f
PD8	|	g
PD9	|	h
PB4	|	4
PB2	|	3
PB1	|	2
PB0	|	1
		
stm32 | RL02_ISO
---|---
PA1	|	Water heater circuit	
PB5 |	Solenoid valve circuit

stm32 | DS18B20
---|---
PA7	|	OneWire transmition

stm32 | Buttons module
---|---
PE4	|	K0
PE5	|	K1
PE6	|	K2
PE7	|	K3  

Then build the project and transfer to your STM32F4 device.
## How to compile
Build with CoIDE and GCC compiler. No extra actions required.
## Future improvements
We have plans on adding a cup holder with a force sensor. This way we could detect if the cup is empty and autofill it.
## Attributions
Used DS18B20, OneWire, GPIO and Delay libraries can be found [here](https://github.com/MaJerle/stm32f429).
## License
Code licensed under the The MIT License.

## Credits
- [Robert Kosakowski](https://github.com/Kosert)
- [Dawid Kuliński](https://github.com/DawidKulinski)

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.  
Supervisor: Tomasz Mańkowski
