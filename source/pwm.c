#ifndef _PWM_C_
#define _PWM_C_
/*********************************************************************************************************************/
#include "include/Public.h"
/*********************************************************************************************************************/

void PWM_Init(unsigned int PWMDIV_V,unsigned int PWMDUT_V)
{
	CKCON |= IHCKE;					//打开IRCH时钟
// 	CKCON |= ILCKE;				//打开IRCL时钟
	INDEX = PWM_CH0;												//设置INDEX值对应PWM0
	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_SYS ;		  //设置PWM时钟源为IRCH  
// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_IL ;		  //设置PWM时钟源为IRCL
// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_XH ;		  //设置PWM时钟源为XOSCH

	PWMCFG = TOG(0) | 0;				
	PWMPS = PWM_P01_INDEX;				//设置P01为PWM0输出引脚
	P01F  = PWM_SETTING;	
	
	//设置PWMDIV、PWMDUT
	PWMDIVH	= (unsigned char)(PWMDIV_V>>8);			
	PWMDIVL	= (unsigned char)(PWMDIV_V);			
	PWMDUTH	=	(unsigned char)(PWMDUT_V>>8);		
	PWMDUTL	= (unsigned char)(PWMDUT_V);	

 	PWMUPD = (1<<PWM_CH0);									//PWMDIV、PWMDUT更新使能
	while(PWMUPD);													//等待更新完成
// 	PWMEN = (1<<PWM_CH0);										//PWM0使能
	
}	




/*
void PWM0_Switch(unsigned char mode)
{
	if(mode == 0)
	{		
		CKCON |= IHCKE;					//打开IRCH时钟
	// 	CKCON |= ILCKE;				//打开IRCL时钟
		INDEX = PWM_CH0;												      //设置INDEX值对应PWM0
		PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_SYS ;		  //设置PWM时钟源为IRCH  
	// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_IL ;		  //设置PWM时钟源为IRCL
	// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_XH ;		  //设置PWM时钟源为XOSCH

		PWMCFG = TOG(0) | 0;				
		PWMPS = PWM_P01_INDEX;				//设置P01为PWM0输出引脚
		P01F  = PWM_SETTING;	
		
		//设置PWMDIV、PWMDUT
		PWMDIVH	= (unsigned char)(PWMDIV_V>>8);			
		PWMDIVL	= (unsigned char)(PWMDIV_V);			
		PWMDUTH	= (unsigned char)(PWMDUT_V>>8);		
		PWMDUTL	= (unsigned char)(PWMDUT_V);	

		PWMUPD = (1<<PWM_CH0);									//PWMDIV、PWMDUT更新使能
		while(PWMUPD);													//等待更新完成
	 	PWMEN = (1<<PWM_CH0);										//PWM0使能
		
	}
	else if(mode == 1)
	{
		CKCON |= IHCKE;					//打开IRCH时钟
	// 	CKCON |= ILCKE;				//打开IRCL时钟
		INDEX = PWM_CH0;												      //设置INDEX值对应PWM0
		PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_SYS ;		  //设置PWM时钟源为IRCH  
	// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_IL ;		  //设置PWM时钟源为IRCL
	// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_XH ;		  //设置PWM时钟源为XOSCH

		PWMCFG = TOG(0) | 0;				
		PWMPS = PWM_P01_INDEX;				//设置P01为PWM0输出引脚
		P01F  = PWM_SETTING;	
		
		//设置PWMDIV、PWMDUT
		PWMDIVH	= (unsigned char)(PWMDIV_V>>8);			
		PWMDIVL	= (unsigned char)(PWMDIV_V);			
		PWMDUTH	= (unsigned char)(PWMDUT_V>>8);		
		PWMDUTL	= (unsigned char)(PWMDUT_V);	

		PWMUPD = (1<<PWM_CH0);									//PWMDIV、PWMDUT更新使能
		while(PWMUPD);													//等待更新完成
	 	PWMEN = (0<<PWM_CH0);										//PWM0使能
		
		
	}
	
}
*/










#endif 