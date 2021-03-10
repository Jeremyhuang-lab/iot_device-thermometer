#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/Public.h"
/*********************************************************************************************************************/
extern float   fTemperature;  //温度 -40至125℃    精度0.1℃ 
extern unsigned int ucHumidity;    //湿度 0%RH至100%RH  精度1%RH 

void main(void)
{
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);
#endif
	
#ifdef UART2_EN
	Uart2_Initial(UART2_BAUTRATE);
#endif
   
	EA = 1;													//开全局中断

    //相关系统初始化
	MySystem_Init();
//    P10F = OUTPUT;	
    while(1)
	{       
		wifi_uart_service();
		KEY_Scan();
		//wifi状态指示灯
		wifi_work_state_led(); 
		RGB_Led_Breathing();
        
//      Fill_Picture(0xff);//鍏ㄥ睆鏄剧ず
//		Delay_ms(1000);
//		Fill_Picture(0xf0);//鍗婂睆鐔勭伃锛涘嚭鐜颁竴鏉′竴鏉＄殑浜嚎
//		Delay_ms(1000);
//		Picture();//鏄剧ず涓�寮犲浘鐗?
//		Delay_ms(1000);
		Measure_Period_Mode();
	}
}
#endif
