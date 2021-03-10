#ifndef _MYI2C_C_
#define _MYI2C_C_
/*********************************************************************************************************************/
#include "include/Public.h"
#include "include/myi2c.h"
/*********************************************************************************************************************/
#define IIC_SDA_IN()  	 {P00F = INPUT; }   //����SDA     SMT���� 
#define IIC_SDA_OUT()  	 {P00F = OUTPUT;}               //����SDA    �������
#define IIC_SCL_OUT()    {P01F = OUTPUT;}   //����SCL    ������� 						
/***********************************************************************************
��������INT2_Init
����˵�����жϳ�ʼ��
���������None 
����ֵ��  None							
***********************************************************************************/

void IIC_GPIO_Init()           //IIC��ʼ���ӳ���
{
	IIC_SCL_OUT();
	IIC_SDA_OUT(); 
	IIC_Stop();
}

void IIC_Start(void) //����I2C����
{
	IIC_SDA_OUT(); 
	IIC_SDA_H;	   //����SDA
	Delay_us(10); //��ʱ
	IIC_SCL_H;	   //����SCL
	Delay_us(10); //��ʱ
	IIC_SDA_L;	   //����SDA
	Delay_us(10); //��ʱ
	IIC_SCL_L;	   //����SCL
	Delay_us(10); //��ʱ
}

void IIC_Stop(void)  //ֹͣI2C����
{
	IIC_SDA_OUT(); 
	IIC_SDA_L;	   //����SDA
	IIC_SCL_H;	   //����SCL
	Delay_us(10); //��ʱ
	IIC_SDA_H;	   //����SDA
	Delay_us(10); //��ʱ
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
unsigned char IIC_Wait_Ack(void)
{
	unsigned char ucErrTime=0;
	IIC_SDA_IN();              //SDA����Ϊ����  
	IIC_SDA_H;	Delay_us(10); //��ʱ	   
	IIC_SCL_H;	Delay_us(10); //��ʱ	 
	while(IIC_SDA!=0)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_L;                //ʱ�����0 	   
	return 0;  
} 

//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL_L;
	IIC_SDA_OUT();
	IIC_SDA_L;
	Delay_us(10);  //��ʱ	 
	IIC_SCL_H;
	Delay_us(10);  //��ʱ
	IIC_SCL_L;
}

//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL_L;
	IIC_SDA_OUT();
	IIC_SDA_H;
	Delay_us(10);  //��ʱ
	IIC_SCL_H;
	Delay_us(10);  //��ʱ
	IIC_SCL_L;
}

//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(unsigned char txd)
{                        
	unsigned char  t;   
	IIC_SDA_OUT();	    
	IIC_SCL_L;  //����ʱ�ӿ�ʼ���ݴ���
	for(t=0;t<8;t++)
  {              
		if((txd&0x80)>>7)
        IIC_SDA_H;
		else
        IIC_SDA_L;
	  	txd<<=1; 	  
        Delay_us(10);  //��ʱ
		IIC_SCL=1;
        Delay_us(10);  //��ʱ
		IIC_SCL=0;	
        Delay_us(10);  //��ʱ
    }	 
} 	

//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
unsigned char IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	IIC_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
		IIC_SCL_L; 
		Delay_us(10);  //��ʱ
		IIC_SCL_H;
		receive<<=1;
		if(IIC_SDA!=0)receive++;   
		Delay_us(10);  //��ʱ 
    }					 
    if(!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}


#endif 