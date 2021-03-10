#ifndef _RGB_C_
#define _RGB_C_
/*********************************************************************************************************************/
#include "include/Public.h"
/*********************************************************************************************************************/

unsigned char xdata led_color_index;  //RGB��ɫ
unsigned char xdata led_breathing_index;  //RGB����
unsigned int xdata breathing_timer;       //RGB������ʱ��
unsigned char xdata gp_2_5ms_timer;       //2.5ms��ʱ��
unsigned int xdata flash_timer;           //��˸ʱ��
unsigned char xdata f_flash;              

unsigned int u16_gp_4ms_timer;
//unsigned int  working_timer;
//unsigned char working_flag;	
	
unsigned char xdata blue_duty=0,red_duty=0,green_duty=0;

unsigned char xdata rgb_pwm_div;  //RGB��Ƶ

void set_lamp_duty(unsigned char index);
void set_lamp_color(unsigned char index);
void RGB_Led_MainLoop(void);
void RGB_Led_Breathing(void);
/*********************************************************************************************************************/
//if ��Ҫ����Ч�� ���
/*
bit RGB_Flag = 0;
extern unsigned char RGB_Index;
extern unsigned int RGB_Count;
*/
/*********************************************************************************************************************/

/***********************************************************************************
��������lamp_init
����˵����RGB��ʼ��
���������None 
����ֵ��  None							
***********************************************************************************/
void lamp_init(void)
{   

	P10F  = PWM_SETTING;
	

	P11F  = PWM_SETTING;
	

	P12F  = PWM_SETTING;
	
 	rgb_pwm_div = 255;		  //PWM ����
    
	led_color_index = LED_COLOR_OFF;
	set_lamp_duty(led_color_index);
	set_lamp_color(led_color_index);	
}
/***********************************************************************************
�������� set_lamp_duty
����˵����RGBռ�ձ�����
��������� indedx
����ֵ��  None							
***********************************************************************************/
void set_lamp_duty(unsigned char index)
{
	switch(index)
	{
		case LED_COLOR_OFF:	
			red_duty  = 0;
			green_duty= 0;
			blue_duty = 0;
		    
			break;
   		case LED_COLOR_RED:
			red_duty  = 255;
			green_duty= 0;
			blue_duty = 0;
		
			break;
   		case LED_COLOR_GREEN:
			red_duty  = 0;
			green_duty= 255;
			blue_duty = 0;
		
			break;
		case LED_COLOR_BLUE:
			red_duty  = 0;
			green_duty= 0;
			blue_duty = 255;
	    	
			break;
   		case LED_COLOR_YELLOW:
			red_duty  = 255;
			green_duty= 255;
			blue_duty = 0;
		
			break;
		case LED_COLOR_PURPLE:
			red_duty  = 255;
			green_duty= 0;
			blue_duty = 255;
		    
			break;
   		case LED_COLOR_CYAN:
			red_duty  = 0;
			green_duty= 255;
			blue_duty = 255;
		    
			break;
		case LED_COLOR_WHITE:
			red_duty  = 255;
			green_duty= 255;
			blue_duty = 255;
		
		    break;
//   		case LED_COLOR_NONE:
//			red_duty  = 0;
//			green_duty= 0;
//			blue_duty = 0;
//		    RGB_Flag = 0;
//		    RGB_Count = 0;
//		    RGB_Index = 0;
			break;
		case LED_COLOR_BREATHING:
			break;
		default:
			break;
		
	}
}
/***********************************************************************************
��������  set_lamp_color
����˵����RGB������ɫ
���������index 
����ֵ��  None							
***********************************************************************************/
void set_lamp_color(unsigned char index)
{
	switch(index)
	{
		case LED_COLOR_OFF:
//			PWM_EnContrl(PWMEN & (~RGB_PWM_EN));		
//			break; 
		case LED_COLOR_RED:
		case LED_COLOR_GREEN:
		case LED_COLOR_BLUE:
		case LED_COLOR_YELLOW:
		case LED_COLOR_PURPLE:
		case LED_COLOR_CYAN:
		case LED_COLOR_WHITE:
//		case LED_COLOR_NONE:		

			INDEX = PWM_CH3;
			PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | MOD(0) ;
			PWMCFG = TOG(0) | 0;
			PWMDIVH	= 0;
			PWMDIVL	= rgb_pwm_div;
			PWMDUTH	= 0;
			PWMDUTL	= red_duty;
			PWMPS = PWM_P10_INDEX;
			P10F  = PWM_SETTING;
			
			INDEX = PWM_CH4;
			PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_IH ;		   
			PWMCFG = TOG(0) | 0;
			PWMDIVH	= 0;
			PWMDIVL	= rgb_pwm_div;
			PWMDUTH	= 0;
			PWMDUTL	= green_duty;
			PWMPS = PWM_P11_INDEX;
			P11F  = PWM_SETTING;
			
			INDEX = PWM_CH5;
			PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | MOD(0) ;
			PWMCFG = TOG(0) | 0;
			PWMDIVH	= 0;
			PWMDIVL	= rgb_pwm_div;
			PWMDUTH	= 0;
			PWMDUTL	= blue_duty;
			PWMPS = PWM_P12_INDEX;
			P12F  = PWM_SETTING;
          
			

			PWMUPD |= (1<<PWM_CH3)|(1<<PWM_CH4)|(1<<PWM_CH5);
			while(PWMUPD);
			PWMEN |= (1<<PWM_CH3)|(1<<PWM_CH4)|(1<<PWM_CH5);

			break;
		case LED_COLOR_BREATHING:
			led_breathing_index = 0;
			red_duty  = 0;
			green_duty= 0;
			blue_duty = 0;
			breathing_timer = u16_gp_4ms_timer;
			break;
		default:
			break;
	}
}
/***********************************************************************************
��������  RGB_Led_Breathing
����˵����RGB������ 
��������� None B-G-R
����ֵ��   None							
***********************************************************************************/
//void RGB_Led_Breathing(void)
//{
//	if(led_color_index != LED_COLOR_BREATHING) return;
//    
//	if(breathing_timer-u16_gp_4ms_timer>6)
//	{
//		breathing_timer=u16_gp_4ms_timer;	
//		if(led_breathing_index==0)	  		//r b
//		{
//			if(blue_duty<255)blue_duty++;
//			else led_breathing_index++;
//		}		
//		else if(led_breathing_index==1)  	//b
//		{
//			if(red_duty>0)red_duty--;
//			else led_breathing_index++;
//		}		 
//		else if(led_breathing_index==2)   	//b g 
//		{
//			if(green_duty<255)green_duty++;
//			else led_breathing_index++;
//		}
//		else if(led_breathing_index==3) 	//g
//		{
//			if(blue_duty>0)blue_duty--;
//			else led_breathing_index++;
//		}
//		else if(led_breathing_index==4)   	//g r
//		{
//			if(red_duty<255)red_duty++;
//			else led_breathing_index++;
//		}
//			else if(led_breathing_index==5)  //r
//		{
//			if(green_duty>0)green_duty--;
//			else led_breathing_index=0;
//		}	
//		PWM_CfgDivDuty(PWM_CH5, rgb_pwm_div, red_duty);
//		PWM_CfgDivDuty(PWM_CH4, rgb_pwm_div, green_duty);
//		PWM_CfgDivDuty(PWM_CH3, rgb_pwm_div, blue_duty);
//		
//		PWM_Update(PWMEN | RGB_PWM_EN);
//		WaitPWMUpdateComplete();
//		PWM_EnContrl(PWMEN | RGB_PWM_EN);
//	}                 
//}
/***********************************************************************************
��������  RGB_Led_Breathing
����˵����RGB��������� R-G-B 
��������� None
����ֵ��   None							
***********************************************************************************/
//void RGB_Led_Breathing(void)
//{
//	if(led_color_index != LED_COLOR_BREATHING) return;
//    
//	if(breathing_timer-u16_gp_4ms_timer>6)
//	{
//		breathing_timer=u16_gp_4ms_timer;	
//		if(led_breathing_index==0)	  		//b r
//		{
//			if(red_duty<255)red_duty++;
//			else led_breathing_index++;
//		}		
//		else if(led_breathing_index==1)  	//r
//		{
//			if(blue_duty>0)blue_duty--;
//			else led_breathing_index++;
//		}		 
//		else if(led_breathing_index==2)   	//r g 
//		{
//			if(green_duty<255)green_duty++;
//			else led_breathing_index++;
//		}
//		else if(led_breathing_index==3) 	//g
//		{
//			if(red_duty>0)red_duty--;
//			else led_breathing_index++;
//		}
//		else if(led_breathing_index==4)   	//g b
//		{
//			if(blue_duty<255)blue_duty++;
//			else led_breathing_index++;
//		}
//			else if(led_breathing_index==5)  //b
//		{
//			if(green_duty>0)green_duty--;
//			else led_breathing_index=0;
//		}	
//		PWM_CfgDivDuty(PWM_CH5, rgb_pwm_div, red_duty);
//		PWM_CfgDivDuty(PWM_CH4, rgb_pwm_div, green_duty);
//		PWM_CfgDivDuty(PWM_CH3, rgb_pwm_div, blue_duty);
//		
//		PWM_Update(PWMEN | RGB_PWM_EN);
//		WaitPWMUpdateComplete();
//		PWM_EnContrl(PWMEN | RGB_PWM_EN);
//	}                 
//}
/***********************************************************************************
��������  RGB_Led_Breathing
����˵����RGB��������� R-G-B 
��������� None
����ֵ��   None							
***********************************************************************************/
void RGB_Led_Breathing(void)
{
	if(led_color_index != LED_COLOR_BREATHING) return;
    
	if(breathing_timer-u16_gp_4ms_timer>16)
	{
		breathing_timer=u16_gp_4ms_timer;	
		if(led_breathing_index==0)	  		//r
		{
			if(red_duty<255)red_duty++;     //0~r
			else led_breathing_index++;				
		}		
		else if(led_breathing_index==1)  	//r-0 
		{
			if(red_duty>1)red_duty--;
			else
			{
				green_duty = 1;
				led_breathing_index++;
			}
		}		 
		else if(led_breathing_index==2)   	//0-g
		{
			if(green_duty<255)green_duty++;
			else 
			{
				led_breathing_index++;
			}
		}
		else if(led_breathing_index==3) 	//g-0
		{
			if(green_duty>1)green_duty--;
			else
			{	
//				red_duty=255; 
				blue_duty=1;
				led_breathing_index++;		
			}
		}
		else if(led_breathing_index==4)   	//0-b
		{
			if(blue_duty<255)blue_duty++;
			else led_breathing_index++;
		}
		else if(led_breathing_index==5)  //b-0
		{
			if(blue_duty>1)blue_duty--;
			else
			{
				red_duty = 1;
				green_duty = 1;
				led_breathing_index++;
			}
		}	
		else if(led_breathing_index==6)  //0-y
		{
			if((red_duty<255)&&(green_duty<255)){red_duty++;green_duty++;}
			else
			{
//				red_duty = 0;
//				green_duty = 0;
				led_breathing_index++;
			}
		}	
		else if(led_breathing_index==7)  //y-0
		{
			if((red_duty>1)&&(green_duty>1)){red_duty--;green_duty--;}
			else
			{
				red_duty = 1;
				blue_duty = 1;
				led_breathing_index++;
			}
		}	
		else if(led_breathing_index==8)  //0-p
		{
			if((red_duty<255)&&(blue_duty<255)){red_duty++;blue_duty++;}
			else
			{
//				red_duty = 0;
//				blue_duty = 0;
				led_breathing_index++;
			}
		}		
		else if(led_breathing_index==9)  //p-0
		{
			if((red_duty>1)&&(blue_duty>1)){red_duty--;blue_duty--;}
			else
			{
				green_duty = 1;
				blue_duty = 1;
				led_breathing_index++;
			}
		}		
		else if(led_breathing_index==10)  //0-c
		{
			if((green_duty<255)&&(blue_duty<255)){green_duty++;blue_duty++;}
			else
			{
//				green_duty = 0;
//				blue_duty = 0;
				led_breathing_index++;
			}
		}	
		else if(led_breathing_index==11)  //y-0
		{
			if((green_duty>1)&&(blue_duty>1)){green_duty--;blue_duty--;}
			else
			{
                red_duty = 1;
				led_breathing_index=0;
			}
		}			
		
        	INDEX = PWM_CH3;
			PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | MOD(0) ;
			PWMCFG = TOG(0) | 0;
			PWMDIVH	= 0;
			PWMDIVL	= rgb_pwm_div;
			PWMDUTH	= 0;
			PWMDUTL	= red_duty;
			PWMPS = PWM_P10_INDEX;
			P10F  = PWM_SETTING;
			
			INDEX = PWM_CH4;
			PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_IH ;		   
			PWMCFG = TOG(0) | 0;
			PWMDIVH	= 0;
			PWMDIVL	= rgb_pwm_div;
			PWMDUTH	= 0;
			PWMDUTL	= green_duty;
			PWMPS = PWM_P11_INDEX;
			P11F  = PWM_SETTING;
			
			INDEX = PWM_CH5;
			PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | MOD(0) ;
			PWMCFG = TOG(0) | 0;
			PWMDIVH	= 0;
			PWMDIVL	= rgb_pwm_div;
			PWMDUTH	= 0;
			PWMDUTL	= blue_duty;
			PWMPS = PWM_P12_INDEX;
			P12F  = PWM_SETTING; 	
			

			PWMUPD |= (1<<PWM_CH3)|(1<<PWM_CH4)|(1<<PWM_CH5);
			while(PWMUPD);
			PWMEN |= (1<<PWM_CH3)|(1<<PWM_CH4)|(1<<PWM_CH5);
	}                 
}


/*********************************************************************************************************************/
 
#endif
