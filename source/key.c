#ifndef _KEY_C_
#define _KEY_C_
/*********************************************************************************************************************/
#include "include/Public.h"
/*********************************************************************************************************************/
unsigned char xdata	gp_10ms_timer;  //10ms��ʱɨ��ʱ��
unsigned char xdata scan_long_key_timer; //������ʱ
unsigned int KeyMsg;                     //������Ϣ��־
unsigned char KEY_Mode=0;    //����ģʽ
extern unsigned char xdata led_color_index;  //RGB��ɫ


/***********************************************************************************
��������INT2_Init
����˵�����жϳ�ʼ��
���������None 
����ֵ��  None							
***********************************************************************************/
void INT2_Init(void)
{
	P30F = INPUT|PU_EN;									    //P30����Ϊ����ģʽ
	INDEX = 0;												//EPCONΪ�������ļĴ���������INDEX=0 ��ӦINT2
	EPCON = EPPL(1) | P30_INDEX;			                //����P30ΪINT2�ж�����
	INT2EN = 1; 											//�ⲿ�ж�2�ж�ʹ��
	EPIE |= 0x01;											//INT2�ж�ʹ��
}	


/***********************************************************************************
��������INT4_Init
����˵�����жϳ�ʼ��
���������None 
����ֵ��  None							
***********************************************************************************/
void INT4_Init(void)
{
	P17F = INPUT|PU_EN;									    //P17����Ϊ����ģʽ
	INDEX = 2;												//EPCONΪ�������ļĴ���������INDEX=2 ��ӦINT4
	EPCON = EPPL(1) | P17_INDEX;			                //����P17ΪINT2�ж�����
	INT4EN = 1; 											//�ⲿ�ж�4�ж�ʹ��
	EPIE |= 0x04;											//INT4�ж�ʹ��
}	

/***********************************************************************************
��������_scan_get_msg
����˵����״̬��ɨ�谴��
���������None
����ֵ��  Scan_msg							
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
	   mcu_reset_wifi();   //��λWIFI  //smart AP ���������л�
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
//	   mcu_reset_wifi();   //��λWIFI  //smart AP ���������л�	   
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