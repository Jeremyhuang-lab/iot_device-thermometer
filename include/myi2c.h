#ifndef _MYI2C_H_
#define _MYI2C_H_
/*********************************************************************************************************************/
#include "include/Public.h"


#define IIC_SDA  P00     //ģ��IIC������ 
#define IIC_SCL  P01	  //ģ��IICʱ����

#define IIC_WR	0	      // д����bit
#define IIC_RD	1	      // ������bit 
					    
#define IIC_SDA_L         IIC_SDA  = 0    //SDA����     
#define IIC_SDA_H         IIC_SDA  = 1    //SDA���� CH1 
  
#define IIC_SCL_L         IIC_SCL = 0	//SCL���� CH2
#define IIC_SCL_H         IIC_SCL = 1    //SCL����


void IIC_GPIO_Init(void);  //IIC GPIO��ʼ��
void IIC_Start(void);   //����I2C����
void IIC_Stop(void);    //ֹͣI2C����
void Delay_IIC(unsigned int m);//IIC��ʱ
void IIC_Send_Byte(unsigned char txd);			//IIC����һ���ֽ�
unsigned char IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
unsigned char IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�


#endif 