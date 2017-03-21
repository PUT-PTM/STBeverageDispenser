# STBeverageDispenser

## Overview
This project is the back-end code for our electric homemade teapot. The teapot has an extra solenoid valve which allows to fill a cup with the button on STM.
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
//TODO
## How to compile
//TODO
## Future improvements
//TODO
## Attributions
//TODO
## License
Code licensed under the The MIT License.

## Credits
- [Robert Kosakowski](https://github.com/Kosert)
- [Dawid Kuliński](https://github.com/DawidKulinski)

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.
Supervisor: Tomasz Mańkowski
