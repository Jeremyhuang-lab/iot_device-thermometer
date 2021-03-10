#ifndef _SHT30_C_
#define _SHT30_C_
/*********************************************************************************************************************/
#include "include/Public.h"
/*********************************************************************************************************************/
float   fTemperature;  //温度 -40至125℃    精度0.1℃ 
unsigned int ucHumidity;    //湿度 0%RH至100%RH  精度1%RH   

#define TIMER0_2S  200
extern unsigned char SHT30_Measure_Timeout;

void SHT30_Init(void)
{
	
	IIC_Start();
	IIC_Send_Byte(SHT30_ADDR | Write_CMD);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x30); //soft reset
	IIC_Wait_Ack();
	IIC_Send_Byte(0xA2);
	IIC_Wait_Ack();
	
	IIC_Start();
	IIC_Send_Byte(SHT30_ADDR | Write_CMD);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x27); //High repeat , mps = 10
	IIC_Wait_Ack();
	IIC_Send_Byte(0x37);
	IIC_Wait_Ack();
	IIC_Stop();
	
}
/*
	* @name   Measure_Period_Mode
	* @brief  周期测量模式
	* @param  None
	* @retval None      
*/
void Measure_Period_Mode(void)
{
    unsigned char   temp_array[6] = {0};
	unsigned int  temp_uint     = 0;
	float     temp_float    = 0;
	
//	SHT30_Measure_Timeout = 0;
//	if(SHT30_Measure_Timeout>=TIMER0_2S)
//	{
		IIC_Start();
		IIC_Send_Byte(SHT30_ADDR | Write_CMD);
		IIC_Wait_Ack();
		IIC_Send_Byte(0xE0);
		IIC_Wait_Ack();
		IIC_Send_Byte(0x00);
		IIC_Wait_Ack();
		
		IIC_Start();
		IIC_Send_Byte(SHT30_ADDR | Read_CMD); 
		IIC_Wait_Ack();
		temp_array[0] = IIC_Read_Byte(1);
		temp_array[1] = IIC_Read_Byte(1);
		temp_array[2] = IIC_Read_Byte(1);
		temp_array[3] = IIC_Read_Byte(1);
		temp_array[4] = IIC_Read_Byte(1);
		temp_array[5] = IIC_Read_Byte(0);
		IIC_Stop();

//		SHT30_Measure_Timeout = 0;
//	}	
	
	
	//////计算温度,精度0.1
	if(CRC_8(temp_array,2) == temp_array[2]) //CRC-8 校验
	{
//		Uart1_PutChar(0x11);
		temp_uint         = temp_array[0]*256+temp_array[1];
		temp_float        = -45+175*((float)temp_uint)/65535;
		fTemperature = temp_float;
//		uart_printf("Wendu = %.1f℃\r\n",fTemperature); 
    }
	
	//////计算湿度，精度1%RH
	if(CRC_8(&temp_array[3],2) == temp_array[5]) //CRC-8 校验
	{
//		Uart1_PutChar(0x12);
		temp_uint      = temp_array[3]*256+temp_array[4];
		temp_float     = ((float)temp_uint)*100/65535;
		temp_float     = temp_float;
		ucHumidity = temp_float;  
//		Uart1_PutChar(ucHumidity);
//		uart_printf("shidu = %.1f%%RH\r\n\r\n",temp_float);
    }
	mcu_dp_value_update(DPID_TEMP_CURRENT,fTemperature*10);     //VALUE型数据上报;
    mcu_dp_value_update(DPID_HUMIDITY_VALUE,ucHumidity); //VALUE型数据上报;

//	if(SHT30_Measure_Timeout>=100)
//	{
//		SHT30_Measure_Timeout = 0;
		OLED_Temp_Humi_Display(fTemperature,ucHumidity);
//	}	
}

/*
	* @name   CRC_8
	* @brief  CRC-8校验
	* @param  Crc_ptr -> 校验数据首地址
						LEN     -> 校验数据长度
	* @retval CRC_Value -> 校验值      
*/
unsigned char CRC_8(unsigned char *Crc_ptr,unsigned char LEN)
{
	unsigned char CRC_Value = 0xFF;
	unsigned char i = 0,j = 0;

	for(i=0;i<LEN;i++)
	{
		CRC_Value ^= *(Crc_ptr+i);
		for(j=0;j<8;j++)
		{
			if(CRC_Value & 0x80)
				CRC_Value = (CRC_Value << 1) ^ 0x31;
			else
				CRC_Value = (CRC_Value << 1);
		}
	}
	return CRC_Value;
}









#endif 