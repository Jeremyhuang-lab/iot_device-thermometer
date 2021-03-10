#ifndef _MYSYSTEM_C_
#define _MYSYSTEM_C_
/*********************************************************************************************************************/
#include "include/Public.h"
/*********************************************************************************************************************/

#define INT_TIME0			10000			//定时时间，单位为us

#define	TH_VAL0				(unsigned char)((0x10000 - (INT_TIME0*(FOSC/1000))/12000)>>8)
#define	TL_VAL0				(unsigned char)(0x10000 - (INT_TIME0*(FOSC/1000))/12000)

extern unsigned int KeyMsg;                      //状态机按键按下
extern unsigned char xdata	gp_10ms_timer;       //10ms扫描定时器
extern unsigned char xdata scan_long_key_timer;  //机械按键长按计时


#define INT_TIME1			1000			//定时时间，单位为us

#define	TH_VAL1				(unsigned char)((0x10000 - (INT_TIME1*(FOSC/1000))/12000)>>8)
#define	TL_VAL1				(unsigned char)(0x10000 - (INT_TIME1*(FOSC/1000))/12000)


extern unsigned char xdata led_color_index;  //RGB配色
bit Day_Flag = 0;
bit Night_Flag = 0;

unsigned char Cnt_msD = 0;
unsigned char Cnt_1sD = 0;
unsigned char Cnt_1mD = 0;

bit Day_Time_Flag = 0;
bit Night_Time_Flag = 0;

unsigned char Cnt_msN = 0;
unsigned char Cnt_1sN = 0;
unsigned char Cnt_1mN = 0;

static unsigned long Timer_Value = 0;
static unsigned long Timer_250ms_Value = 0;
static unsigned long Timer_Sec_Value = 0;


extern unsigned int u16_gp_4ms_timer;

unsigned char SHT30_Measure_Timeout = 0;
void MySystem_Init(void)
{
	MyGPIO_Init();
    INT2_Init();
	INT4_Init();
	Timer0_Init();
	Timer1_Init();
	lamp_init();
	Beep_Init();
	IIC_GPIO_Init(); 
    SHT30_Init();
	OLED_Init();
	//初始化wifi
    wifi_protocol_init();
	OLED_Clear();
}

void MyGPIO_Init(void)
{
	
	

	

}

/*****************************************************************************
函数名称 : wifi_work_state_led
功能描述 : wifi状态指示灯控制
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void wifi_work_state_led(void)
{
  unsigned char wifi_state = mcu_get_wifi_work_state();
  static unsigned char wifi_state_bak = WIFI_SATE_UNKNOW;
	
	switch(wifi_state)
	{
	case SMART_CONFIG_STATE:
		if(get_timer_250ms_value() % 2 == 0)
		{
//			   //错误指示灯亮
			led_color_index =  LED_COLOR_RED;
		    set_lamp_duty(led_color_index);
	        set_lamp_color(led_color_index);	
		}
		else
		{
//			   //错误指示灯灭
			led_color_index =  LED_COLOR_OFF;
		    set_lamp_duty(led_color_index);
	        set_lamp_color(led_color_index);	
		}
		wifi_state_bak = SMART_CONFIG_STATE;
		break;
		
	case AP_STATE:
		if((get_timer_250ms_value() % 12) == 0)
		{
//			   //错误指示灯亮
			led_color_index =  LED_COLOR_RED;
		    set_lamp_duty(led_color_index);
	        set_lamp_color(led_color_index);
		}
		else if((get_timer_250ms_value() % 12) == 6)
		{
//			   //错误指示灯灭
			led_color_index =  LED_COLOR_OFF;
		    set_lamp_duty(led_color_index);
	        set_lamp_color(led_color_index);	
		}
		wifi_state_bak = AP_STATE;
		break;
		
	case WIFI_NOT_CONNECTED:
		if((wifi_state_bak == SMART_CONFIG_STATE) || (wifi_state_bak == AP_STATE))
		{
//			   //错误指示灯灭
			led_color_index =  LED_COLOR_OFF;
		    set_lamp_duty(led_color_index);
	        set_lamp_color(led_color_index);	
		}  
		break;
		
	case WIFI_CONNECTED:
		if((wifi_state_bak == SMART_CONFIG_STATE) || (wifi_state_bak == AP_STATE))
		{		
//			   //错误指示灯亮
			led_color_index =  LED_COLOR_RED;
		    set_lamp_duty(led_color_index);
	        set_lamp_color(led_color_index);
			wifi_state_bak = WIFI_CONNECTED;
		}
		break;
		
	default:
		if((wifi_state_bak == SMART_CONFIG_STATE) || (wifi_state_bak == AP_STATE))
		{
//			   //错误指示灯灭
			led_color_index =  LED_COLOR_OFF;
		    set_lamp_duty(led_color_index);
	        set_lamp_color(led_color_index);
		}
		break;
	}
}

/***********************************************************************************
函数名：Timer0_init
功能说明：Timer0初始化
输入参数：None 
返回值：  None							
***********************************************************************************/
void Timer0_Init(void)
{
	TMOD = (TMOD&0xFC)|0x01; //模式选择: 定时器0，模式1。
	TH0 = TH_VAL0;    					//高8位装初值
	TL0 = TL_VAL0;    					//低8位装初值
	
	TR0 = 1;       //定时器0使能    
	ET0 = 1;       //定时器0中断使能
	PT0 = 1;       //设置定时器0中断优先级为低优先级
	
}

void Timer0_ISR(void)interrupt 1 //每10ms产生中断
{
	TH0 = TH_VAL0;    					//高8位装初值
	TL0 = TL_VAL0;    					//低8位装初值	
	gp_10ms_timer--;
	if(scan_long_key_timer)
	{
		scan_long_key_timer--;
	}	
	
	KeyMsg=_scan_get_msg();
	
}

/***********************************************************************************
函数名：Timer1_init
功能说明：Timer1初始化
输入参数：None 
返回值：  None							
***********************************************************************************/
void Timer1_Init(void)
{
	TMOD = (TMOD&0xCF)|0x10; //模式选择: 定时器1，模式1。
	TH1 = TH_VAL1;    					//高8位装初值
	TL1 = TL_VAL1;    					//低8位装初值
	
	TR1 = 1;       						//定时器1使能  
	ET1 = 1;       						//定时器1中断使能
	PT1 = 0;       						//设置定时器1中断优先级为低优先级
	
}

void Timer1_ISR(void)interrupt 3 //每10ms产生中断
{
	TH1 = TH_VAL1;    					//高8位装初值
	TL1 = TL_VAL1;    					//低8位装初值	
    	
	Timer_Value ++;
	if((Timer_Value % 250) == 0)
	{
		Timer_250ms_Value ++;
		if(Timer_250ms_Value % 40 == 0)
		{
			Timer_Sec_Value ++;
		}
		if(Timer_Sec_Value >= 600)
		{
			Timer_Sec_Value = 0;		
		}		
	}
	u16_gp_4ms_timer--;
	SHT30_Measure_Timeout++;
	
}	

/*****************************************************************************
函数名称 : get_count_value
功能描述 : 获取Timer0计数值
输入参数 : 无
返回参数 : Timer_Value
使用说明 : 无
*****************************************************************************/
unsigned long get_count_value(void)
{
	return Timer_Value;
}
/*****************************************************************************
函数名称 : get_timer_250ms_value
功能描述 : 获取250ms计数值
输入参数 : 无
返回参数 : Timer_250ms_Value
使用说明 : 无
*****************************************************************************/
unsigned long get_timer_250ms_value(void)
{
	return Timer_250ms_Value;
}

#endif