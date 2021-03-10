#ifndef _Delay_C_
#define _Delay_C_
/*********************************************************************************************************************/
#include <intrins.h>
void Delay_50us(unsigned int n)	   
{
	unsigned char i;

	while(n--)
	{
		for(i=0;i<71;i++);
	}
}
void Delay_ms(unsigned int delay_nms)
{
	while(delay_nms--)
	{
		Delay_50us(20);
	}
}
void Delay_us(unsigned int n)	   ////n=1 2.54us 4 5.27us 8 9.06us 
{
	while(n--)
	{
		_nop_();  
	}
}
void Delay_5us()	   
{
//	unsigned char n=7;

//	while(n--)
//	{
//		
//	}
}
/*********************************************************************************************************************/
#endif