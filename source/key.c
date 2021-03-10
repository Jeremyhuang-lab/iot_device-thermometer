#ifndef _KEY_C_
#define _KEY_C_
/*********************************************************************************************************************/
#include "include/Public.h"
/*********************************************************************************************************************/
unsigned char xdata	gp_10ms_timer;  //10ms定时扫描时间
unsigned char xdata scan_long_key_timer; //长按计时
unsigned int KeyMsg;                     //按键信息标志
unsigned char KEY_Mode=0;    //按键模式
extern unsigned char xdata led_color_index;  //RGB配色


/***********************************************************************************
函数名：INT2_Init
功能说明：中断初始化
输入参数：None 
返回值：  None							
***********************************************************************************/
void INT2_Init(void)
{
	P30F = INPUT|PU_EN;									    //P30设置为输入模式
	INDEX = 0;												//EPCON为带索引的寄存器，设置INDEX=0 对应INT2
	EPCON = EPPL(1) | P30_INDEX;			                //设置P30为INT2中断引脚
	INT2EN = 1; 											//外部中断2中断使能
	EPIE |= 0x01;											//INT2中断使能
}	


/***********************************************************************************
函数名：INT4_Init
功能说明：中断初始化
输入参数：None 
返回值：  None							
***********************************************************************************/
void INT4_Init(void)
{
	P17F = INPUT|PU_EN;									    //P17设置为输入模式
	INDEX = 2;												//EPCON为带索引的寄存器，设置INDEX=2 对应INT4
	EPCON = EPPL(1) | P17_INDEX;			                //设置P17为INT2中断引脚
	INT4EN = 1; 											//外部中断4中断使能
	EPIE |= 0x04;											//INT4中断使能
}	

/***********************************************************************************
函数名：_scan_get_msg
功能说明：状态机扫描按键
输入参数：None
返回值：  Scan_msg							
***********************************************************************************/
unsigned int _scan_get_msg(void)
{
	static u8_t xdata read_scan_key_timer;
	static u16_t xdata last_scan_key=JXKEY_INVALID;
	static bit scan_monitor,f_scan_long=0;
	u16_t scan_key=JXKEY_INVALID;
	u16_t scan_msg=JXKEY_INVALID;
//	Uart0_PutChar(0XAA);
//	if(read_scan_key_timer-gp_10ms_timer>1)
	{	
		read_scan_key_timer=gp_10ms_timer;
		if(KEY1 == 0)
		{	
//			Uart1_PutChar(0XAA);			
			scan_key = 0x01;
		}
		else if(KEY2 == 0)
		{	
//			Uart1_PutChar(0XA2);			
			scan_key = 0x02;
		}
		else
		{	
			scan_key = JXKEY_INVALID;
		}
		if(!scan_monitor)
		{
			if(scan_key!=JXKEY_INVALID)
			{
				if(scan_key==last_scan_key)
				{
					scan_msg=last_scan_key;
					scan_long_key_timer=JXLONG_KEY_START_TIME;
					f_scan_long=0;
					scan_monitor=1;
				}
				else
				{
					last_scan_key=scan_key;
				}
			}
		}
		else
		{
			if(scan_key!=JXKEY_INVALID)
			{
				if(!scan_long_key_timer)
				{
					scan_long_key_timer=JXLONG_KEY_TIME;
					if(f_scan_long)
					{
						scan_msg=(u16_t)last_scan_key|JXKEY_LONG;
					}
					else
					{
						scan_msg=(u16_t)last_scan_key|JXKEY_LONG_START;
						f_scan_long=1;
					}
				}
			}
			else
			{
				if(f_scan_long)
				{
					scan_msg=(u16_t)last_scan_key|JXKEY_LONG_BREAK;
				}
				else
				{
					scan_msg=(u16_t)last_scan_key|JXKEY_BREAK;
				}
				last_scan_key=JXKEY_INVALID;
				scan_monitor=0;
			}
		}
	}
//   Uart0_PutChar(0x88);
//   Uart0_PutChar(scan_msg);
	return scan_msg;
	
}

void KEY_Scan(void)
{
	if(KeyMsg ==( K1|JXKEY_BREAK)) 
	{    	   
	   KeyMsg = 0;

	}	
	else if(KeyMsg == (K1|JXKEY_LONG_BREAK))
	{   
	   KeyMsg = 0;
//	   Uart1_PutChar(0xA2);
	   mcu_reset_wifi();   //复位WIFI  //smart AP 配网来回切换
//      Uart1_PutChar(mcu_get_wifimode_flag());	
	}  

	 if(KeyMsg ==( K2|JXKEY_BREAK)) 
	{    	   
	   KeyMsg = 0;
//       Uart1_PutChar(0x12);
       if(led_color_index++ >= MAX_LED_COLOR)
	   {
		   led_color_index = LED_COLOR_OFF;
	   }
	   set_lamp_duty(led_color_index);
	   set_lamp_color(led_color_index); 
	}	
	else if(KeyMsg == (K2|JXKEY_LONG_BREAK))
	{   
	   KeyMsg = 0;
//	   Uart1_PutChar(0x22);
//	   mcu_reset_wifi();   //复位WIFI  //smart AP 配网来回切换	   
	}  
}

void RGB_Run(void)
{
	
}
void INT2_ISR (void) interrupt 7
{
	if(EPIF & 0x01)
	{
		EPIF = 0x01;		
	}
}


void INT4_ISR (void) interrupt 9
{
	if(EPIF & 0x04)
	{
		EPIF = 0x04;
	}
}

#endif 