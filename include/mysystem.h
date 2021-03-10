#ifndef _MYSYSTEM_H_
#define _MYSYSTEM_H_

void MySystem_Init(void);
void Timer0_Init(void);
void MyGPIO_Init(void);
void Timer1_Init(void);

#define TIMER0_2S  200

/*****************************************************************************
函数名称 : get_count_value
功能描述 : 获取Timer0计数值
输入参数 : 无
返回参数 : Timer_Value
使用说明 : 无
*****************************************************************************/
unsigned long get_count_value(void);

/*****************************************************************************
函数名称 : get_timer_250ms_value
功能描述 : 获取250ms计数值
输入参数 : 无
返回参数 : Timer_250ms_Value
使用说明 : 无
*****************************************************************************/
unsigned long get_timer_250ms_value(void);

void wifi_work_state_led(void);

#endif