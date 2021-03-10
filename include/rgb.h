#ifndef _RGB_H_
#define _RGB_H_
/**************************************************************************************************************/

enum
{
	LED_COLOR_OFF = 0,	
	LED_COLOR_RED,
	LED_COLOR_GREEN,
	LED_COLOR_BLUE,				
	LED_COLOR_YELLOW,
	LED_COLOR_PURPLE,
	LED_COLOR_CYAN,
	LED_COLOR_WHITE,
	LED_COLOR_BREATHING,
//	LED_COLOR_NONE,
	MAX_LED_COLOR = LED_COLOR_BREATHING,
};



 
#define RGB_MIN_DUTY      20

#define PWM_CLK_DIV            10    //PWM ±÷”∑÷∆µ



void set_lamp_duty(unsigned char index);
void set_lamp_color(unsigned char index);
void RGB_Led_Breathing(void);
void lamp_init(void);
void RGB_Jump(unsigned char index);
/*********************************************************************************************************************/
#endif	