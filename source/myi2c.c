#ifndef _MYI2C_C_
#define _MYI2C_C_
/*********************************************************************************************************************/
#include "include/Public.h"
#include "include/myi2c.h"
/*********************************************************************************************************************/
#define IIC_SDA_IN()  	 {P00F = INPUT; }   //设置SDA     SMT输入 
#define IIC_SDA_OUT()  	 {P00F = OUTPUT;}               //设置SDA    推挽输出
#define IIC_SCL_OUT()    {P01F = OUTPUT;}   //设置SCL    推挽输出 						
/***********************************************************************************
函数名：INT2_Init
功能说明：中断初始化
输入参数：None 
返回值：  None							
***********************************************************************************/

void IIC_GPIO_Init()           //IIC初始化子程序
{
	IIC_SCL_OUT();
	IIC_SDA_OUT(); 
	IIC_Stop();
}

void IIC_Start(void) //启动I2C总线
{
	IIC_SDA_OUT(); 
	IIC_SDA_H;	   //拉高SDA
	Delay_us(10); //延时
	IIC_SCL_H;	   //拉高SCL
	Delay_us(10); //延时
	IIC_SDA_L;	   //拉低SDA
	Delay_us(10); //延时
	IIC_SCL_L;	   //拉低SCL
	Delay_us(10); //延时
}

void IIC_Stop(void)  //停止I2C总线
{
	IIC_SDA_OUT(); 
	IIC_SDA_L;	   //拉低SDA
	IIC_SCL_H;	   //拉高SCL
	Delay_us(10); //延时
	IIC_SDA_H;	   //拉高SDA
	Delay_us(10); //延时
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
unsigned char IIC_Wait_Ack(void)
{
	unsigned char ucErrTime=0;
	IIC_SDA_IN();              //SDA设置为输入  
	IIC_SDA_H;	Delay_us(10); //延时	   
	IIC_SCL_H;	Delay_us(10); //延时	 
	while(IIC_SDA!=0)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_L;                //时钟输出0 	   
	return 0;  
} 

//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL_L;
	IIC_SDA_OUT();
	IIC_SDA_L;
	Delay_us(10);  //延时	 
	IIC_SCL_H;
	Delay_us(10);  //延时
	IIC_SCL_L;
}

//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL_L;
	IIC_SDA_OUT();
	IIC_SDA_H;
	Delay_us(10);  //延时
	IIC_SCL_H;
	Delay_us(10);  //延时
	IIC_SCL_L;
}

//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(unsigned char txd)
{                        
	unsigned char  t;   
	IIC_SDA_OUT();	    
	IIC_SCL_L;  //拉低时钟开始数据传输
	for(t=0;t<8;t++)
  {              
		if((txd&0x80)>>7)
        IIC_SDA_H;
		else
        IIC_SDA_L;
	  	txd<<=1; 	  
        Delay_us(10);  //延时
		IIC_SCL=1;
        Delay_us(10);  //延时
		IIC_SCL=0;	
        Delay_us(10);  //延时
    }	 
} 	

//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
unsigned char IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	IIC_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
		IIC_SCL_L; 
		Delay_us(10);  //延时
		IIC_SCL_H;
		receive<<=1;
		if(IIC_SDA!=0)receive++;   
		Delay_us(10);  //延时 
    }					 
    if(!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}


#endif 