#ifndef _MYSYSTEM_H_
#define _MYSYSTEM_H_

void MySystem_Init(void);
void Timer0_Init(void);
void MyGPIO_Init(void);
void Timer1_Init(void);

#define TIMER0_2S  200

/*****************************************************************************
�������� : get_count_value
�������� : ��ȡTimer0����ֵ
������� : ��
���ز��� : Timer_Value
ʹ��˵�� : ��
*****************************************************************************/
unsigned long get_count_value(void);

/*****************************************************************************
�������� : get_timer_250ms_value
�������� : ��ȡ250ms����ֵ
������� : ��
���ز��� : Timer_250ms_Value
ʹ��˵�� : ��
*****************************************************************************/
unsigned long get_timer_250ms_value(void);

void wifi_work_state_led(void);

#endif