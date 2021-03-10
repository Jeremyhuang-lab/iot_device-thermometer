#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/Public.h"
/*********************************************************************************************************************/
extern float   fTemperature;  //�¶� -40��125��    ����0.1�� 
extern unsigned int ucHumidity;    //ʪ�� 0%RH��100%RH  ����1%RH 

void main(void)
{
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);
#endif
	
#ifdef UART2_EN
	Uart2_Initial(UART2_BAUTRATE);
#endif
   
	EA = 1;													//��ȫ���ж�

    //���ϵͳ��ʼ��
	MySystem_Init();
//    P10F = OUTPUT;	
    while(1)
	{       
		wifi_uart_service();
		KEY_Scan();
		//wifi״ָ̬ʾ��
		wifi_work_state_led(); 
		RGB_Led_Breathing();
        
//      Fill_Picture(0xff);//全屏显示
//		Delay_ms(1000);
//		Fill_Picture(0xf0);//半屏熄灭；出现一条一条的亮线
//		Delay_ms(1000);
//		Picture();//显示一张图�?
//		Delay_ms(1000);
		Measure_Period_Mode();
	}
}
#endif
