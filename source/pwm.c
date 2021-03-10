#ifndef _PWM_C_
#define _PWM_C_
/*********************************************************************************************************************/
#include "include/Public.h"
/*********************************************************************************************************************/

void PWM_Init(unsigned int PWMDIV_V,unsigned int PWMDUT_V)
{
	CKCON |= IHCKE;					//��IRCHʱ��
// 	CKCON |= ILCKE;				//��IRCLʱ��
	INDEX = PWM_CH0;												//����INDEXֵ��ӦPWM0
	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_SYS ;		  //����PWMʱ��ԴΪIRCH  
// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_IL ;		  //����PWMʱ��ԴΪIRCL
// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_XH ;		  //����PWMʱ��ԴΪXOSCH

	PWMCFG = TOG(0) | 0;				
	PWMPS = PWM_P01_INDEX;				//����P01ΪPWM0�������
	P01F  = PWM_SETTING;	
	
	//����PWMDIV��PWMDUT
	PWMDIVH	= (unsigned char)(PWMDIV_V>>8);			
	PWMDIVL	= (unsigned char)(PWMDIV_V);			
	PWMDUTH	=	(unsigned char)(PWMDUT_V>>8);		
	PWMDUTL	= (unsigned char)(PWMDUT_V);	

 	PWMUPD = (1<<PWM_CH0);									//PWMDIV��PWMDUT����ʹ��
	while(PWMUPD);													//�ȴ��������
// 	PWMEN = (1<<PWM_CH0);										//PWM0ʹ��
	
}	




/*
void PWM0_Switch(unsigned char mode)
{
	if(mode == 0)
	{		
		CKCON |= IHCKE;					//��IRCHʱ��
	// 	CKCON |= ILCKE;				//��IRCLʱ��
		INDEX = PWM_CH0;												      //����INDEXֵ��ӦPWM0
		PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_SYS ;		  //����PWMʱ��ԴΪIRCH  
	// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_IL ;		  //����PWMʱ��ԴΪIRCL
	// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_XH ;		  //����PWMʱ��ԴΪXOSCH

		PWMCFG = TOG(0) | 0;				
		PWMPS = PWM_P01_INDEX;				//����P01ΪPWM0�������
		P01F  = PWM_SETTING;	
		
		//����PWMDIV��PWMDUT
		PWMDIVH	= (unsigned char)(PWMDIV_V>>8);			
		PWMDIVL	= (unsigned char)(PWMDIV_V);			
		PWMDUTH	= (unsigned char)(PWMDUT_V>>8);		
		PWMDUTL	= (unsigned char)(PWMDUT_V);	

		PWMUPD = (1<<PWM_CH0);									//PWMDIV��PWMDUT����ʹ��
		while(PWMUPD);													//�ȴ��������
	 	PWMEN = (1<<PWM_CH0);										//PWM0ʹ��
		
	}
	else if(mode == 1)
	{
		CKCON |= IHCKE;					//��IRCHʱ��
	// 	CKCON |= ILCKE;				//��IRCLʱ��
		INDEX = PWM_CH0;												      //����INDEXֵ��ӦPWM0
		PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_SYS ;		  //����PWMʱ��ԴΪIRCH  
	// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_IL ;		  //����PWMʱ��ԴΪIRCL
	// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_XH ;		  //����PWMʱ��ԴΪXOSCH

		PWMCFG = TOG(0) | 0;				
		PWMPS = PWM_P01_INDEX;				//����P01ΪPWM0�������
		P01F  = PWM_SETTING;	
		
		//����PWMDIV��PWMDUT
		PWMDIVH	= (unsigned char)(PWMDIV_V>>8);			
		PWMDIVL	= (unsigned char)(PWMDIV_V);			
		PWMDUTH	= (unsigned char)(PWMDUT_V>>8);		
		PWMDUTL	= (unsigned char)(PWMDUT_V);	

		PWMUPD = (1<<PWM_CH0);									//PWMDIV��PWMDUT����ʹ��
		while(PWMUPD);													//�ȴ��������
	 	PWMEN = (0<<PWM_CH0);										//PWM0ʹ��
		
		
	}
	
}
*/










#endif 