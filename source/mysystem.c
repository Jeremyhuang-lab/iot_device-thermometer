#ifndef _MYSYSTEM_C_
#define _MYSYSTEM_C_
/*********************************************************************************************************************/
#include "include/Public.h"
/*********************************************************************************************************************/

#define INT_TIME0			10000			//��ʱʱ�䣬��λΪus

#define	TH_VAL0				(unsigned char)((0x10000 - (INT_TIME0*(FOSC/1000))/12000)>>8)
#define	TL_VAL0				(unsigned char)(0x10000 - (INT_TIME0*(FOSC/1000))/12000)

extern unsigned int KeyMsg;                      //״̬����������
extern unsigned char xdata	gp_10ms_timer;       //10msɨ�趨ʱ��
extern unsigned char xdata scan_long_key_timer;  //��е����������ʱ


#define INT_TIME1			1000			//��ʱʱ�䣬��λΪus

#define	TH_VAL1				(unsigned char)((0x10000 - (INT_TIME1*(FOSC/1000))/12000)>>8)
#define	TL_VAL1				(unsigned char)(0x10000 - (INT_TIME1*(FOSC/1000))/12000)


extern unsigned char xdata led_color_index;  //RGB��ɫ
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
	//��ʼ��wifi
    wifi_protocol_init();
	OLED_Clear();
}

void MyGPIO_Init(void)
{
	
	

	

}

/*****************************************************************************
�������� : wifi_work_state_led
�������� : wifi״ָ̬ʾ�ƿ���
������� : ��
���ز��� : ��
ʹ��˵�� : ��
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
//			   //����ָʾ����
			led_color_index =  LED_COLOR_RED;
		    set_lamp_duty(led_color_index);
	        set_lamp_color(led_color_index);	
		}
		else
		{
//			   //����ָʾ����
			led_color_index =  LED_COLOR_OFF;
		    set_lamp_duty(led_color_index);
	        set_lamp_color(led_color_index);	
		}
		wifi_state_bak = SMART_CONFIG_STATE;
		break;
		
	case AP_STATE:
		if((get_timer_250ms_value() % 12) == 0)
		{
//			   //����ָʾ����
			led_color_index =  LED_COLOR_RED;
		    set_lamp_duty(led_color_index);
	        set_lamp_color(led_color_index);
		}
		else if((get_timer_250ms_value() % 12) == 6)
		{
//			   //����ָʾ����
			led_color_index =  LED_COLOR_OFF;
		    set_lamp_duty(led_color_index);
	        set_lamp_color(led_color_index);	
		}
		wifi_state_bak = AP_STATE;
		break;
		
	case WIFI_NOT_CONNECTED:
		if((wifi_state_bak == SMART_CONFIG_STATE) || (wifi_state_bak == AP_STATE))
		{
//			   //����ָʾ����
			led_color_index =  LED_COLOR_OFF;
		    set_lamp_duty(led_color_index);
	        set_lamp_color(led_color_index);	
		}  
		break;
		
	case WIFI_CONNECTED:
		if((wifi_state_bak == SMART_CONFIG_STATE) || (wifi_state_bak == AP_STATE))
		{		
//			   //����ָʾ����
			led_color_index =  LED_COLOR_RED;
		    set_lamp_duty(led_color_index);
	        set_lamp_color(led_color_index);
			wifi_state_bak = WIFI_CONNECTED;
		}
		break;
		
	default:
		if((wifi_state_bak == SMART_CONFIG_STATE) || (wifi_state_bak == AP_STATE))
		{
//			   //����ָʾ����
			led_color_index =  LED_COLOR_OFF;
		    set_lamp_duty(led_color_index);
	        set_lamp_color(led_color_index);
		}
		break;
	}
}

/***********************************************************************************
��������Timer0_init
����˵����Timer0��ʼ��
���������None 
����ֵ��  None							
***********************************************************************************/
void Timer0_Init(void)
{
	TMOD = (TMOD&0xFC)|0x01; //ģʽѡ��: ��ʱ��0��ģʽ1��
	TH0 = TH_VAL0;    					//��8λװ��ֵ
	TL0 = TL_VAL0;    					//��8λװ��ֵ
	
	TR0 = 1;       //��ʱ��0ʹ��    
	ET0 = 1;       //��ʱ��0�ж�ʹ��
	PT0 = 1;       //���ö�ʱ��0�ж����ȼ�Ϊ�����ȼ�
	
}

void Timer0_ISR(void)interrupt 1 //ÿ10ms�����ж�
{
	TH0 = TH_VAL0;    					//��8λװ��ֵ
	TL0 = TL_VAL0;    					//��8λװ��ֵ	
	gp_10ms_timer--;
	if(scan_long_key_timer)
	{
		scan_long_key_timer--;
	}	
	
	KeyMsg=_scan_get_msg();
	
}

/***********************************************************************************
��������Timer1_init
����˵����Timer1��ʼ��
���������None 
����ֵ��  None							
***********************************************************************************/
void Timer1_Init(void)
{
	TMOD = (TMOD&0xCF)|0x10; //ģʽѡ��: ��ʱ��1��ģʽ1��
	TH1 = TH_VAL1;    					//��8λװ��ֵ
	TL1 = TL_VAL1;    					//��8λװ��ֵ
	
	TR1 = 1;       						//��ʱ��1ʹ��  
	ET1 = 1;       						//��ʱ��1�ж�ʹ��
	PT1 = 0;       						//���ö�ʱ��1�ж����ȼ�Ϊ�����ȼ�
	
}

void Timer1_ISR(void)interrupt 3 //ÿ10ms�����ж�
{
	TH1 = TH_VAL1;    					//��8λװ��ֵ
	TL1 = TL_VAL1;    					//��8λװ��ֵ	
    	
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
�������� : get_count_value
�������� : ��ȡTimer0����ֵ
������� : ��
���ز��� : Timer_Value
ʹ��˵�� : ��
*****************************************************************************/
unsigned long get_count_value(void)
{
	return Timer_Value;
}
/*****************************************************************************
�������� : get_timer_250ms_value
�������� : ��ȡ250ms����ֵ
������� : ��
���ز��� : Timer_250ms_Value
ʹ��˵�� : ��
*****************************************************************************/
unsigned long get_timer_250ms_value(void)
{
	return Timer_250ms_Value;
}

#endif