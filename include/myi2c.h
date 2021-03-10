#ifndef _MYI2C_H_
#define _MYI2C_H_
/*********************************************************************************************************************/
#include "include/Public.h"


#define IIC_SDA  P00     //模拟IIC数据线 
#define IIC_SCL  P01	  //模拟IIC时钟线

#define IIC_WR	0	      // 写控制bit
#define IIC_RD	1	      // 读控制bit 
					    
#define IIC_SDA_L         IIC_SDA  = 0    //SDA拉低     
#define IIC_SDA_H         IIC_SDA  = 1    //SDA拉高 CH1 
  
#define IIC_SCL_L         IIC_SCL = 0	//SCL拉低 CH2
#define IIC_SCL_H         IIC_SCL = 1    //SCL拉高


void IIC_GPIO_Init(void);  //IIC GPIO初始化
void IIC_Start(void);   //启动I2C总线
void IIC_Stop(void);    //停止I2C总线
void Delay_IIC(unsigned int m);//IIC延时
void IIC_Send_Byte(unsigned char txd);			//IIC发送一个字节
unsigned char IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
unsigned char IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号


#endif 