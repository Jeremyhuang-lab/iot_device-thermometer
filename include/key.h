#ifndef _KEY_H_
#define _KEY_H_

enum 
{
	P00_INDEX = 0,
	P01_INDEX = 1,
	P02_INDEX = 2,
	P03_INDEX = 3,
	P04_INDEX = 4,
	P05_INDEX = 5,
	P06_INDEX = 6,
	P07_INDEX = 7,
	P10_INDEX = 8,
	P11_INDEX = 9,
	P12_INDEX = 10,
	P13_INDEX = 11,
	P14_INDEX = 12,
	P15_INDEX = 13,
	P16_INDEX = 14,
	P17_INDEX = 15,
	P20_INDEX = 16,
	P30_INDEX = 17,

};
typedef unsigned 	char 				u8_t;
typedef signed 		char 				s8_t;
typedef unsigned 	int 				u16_t;
typedef signed 		int 				s16_t;
typedef unsigned 	long int 		u32_t;
typedef signed 		long int 		s32_t;

#define KEY1    P30
#define KEY2    P17

//EPCON寄存器定义
#define EPPL(N)	(N<<7)



#define K1					0x0001
#define K2					0x0002

#define JXLONG_KEY_START_TIME				80
#define JXLONG_KEY_TIME					15

#define		JXKEY_INVALID		0 
#define 	JXKEY_BREAK					0x1000     	//短按抬起
#define 	JXKEY_LONG					0x2000     	//长按
#define 	JXKEY_LONG_BREAK		0x3000			//长按抬起
#define 	JXKEY_LONG_START		0x4000			//长按开始  


void INT2_Init(void);
void INT4_Init(void);
void KEY_Scan(void);
unsigned int _scan_get_msg(void);
#endif 