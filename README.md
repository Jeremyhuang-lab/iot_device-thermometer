# iot_device-thermometer
Smart thermometer and hygrometer based on Tuya &amp; Lichuang EDA

This project is developed using Tuya SDK, which enables you to quickly develop branded apps connecting and controlling smart scenarios of many devices.For more information, please check Tuya Developer Website.

1.Program name
==
Smart thermometer


2.Program overview
==
Short press the left button once to switch the RGB color, red-green-blue-yellow-purple-green-white-breathing gradient
Long press the right button to control Tuya WIFI module distribution network, real-time report temperature and humidity data
When the temperature reaches the threshold, the buzzer will alarm and the fan motor will be turned on.
Set the humidity threshold, turn on the ultrasonic atomizer when it is not reached, and turn it off when it reaches it.

3.Overview of components
==

The main control of this program chooses the domestic enhanced 8051 single-chip microcomputer CA51S003.
Temperature and humidity sensor selection SHT30 (completed)
Display module selection OLED12864 (completed)
. Atmosphere light chooses four 3528 packaged RGB lights, using single-chip 3-channel PWM configuration, (completed)
Buzzer selection passive buzzer driving frequency 2.7Khz (completed)
The motor chooses ordinary DC 5V motor (unfinished)
Ultrasonic atomizer chooses atomizing film, driving frequency 108Khz (unfinished)

4.Problems encountered in the development process
==
The PCB1.0 version was drawn one night before the end of my time a year ago, so I didn't check it carefully, which caused the serial port and WIFI module communication pins to be reversed, and the button direction was wrong.

PCB1.1 SHT30 reads the data, so I tested a program with DHT11 temperature and humidity sensor. The difference between the two humidity data is quite large. The judgment may be related to the breadboard and PCB.

When the program turns on the OLED display, the button lighting program fails, and it is judged that it may be the cause of the timer.

5.Conclusion
==
I am very grateful for this training camp opportunity for Lichuang EDA and Tuya Intelligence. As a newcomer who has just graduated, there are still many things that are unfamiliar and the project is not perfect. I hope I can continue to study hard.


