#ifndef _OLED_H_
#define _OLED_H_
/*********************************************************************************************************************/

#define OLED_TEST   0
#define OLED_ADDR  0x78

#define Write_CMD    0x00  // Ð´¿ØÖÆbit
#define Read_CMD     0x01  // ¶Á¿ØÖÆbit

#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

#if OLED_TEST
void Fill_Picture(unsigned char Fill_Data);
void Picture(void);
#endif 

void OLED_Init(void);
void OLED_Clear(void);
void OLED_Fill(unsigned char fill_Data);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch, unsigned char TextSize);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char *ch, unsigned char TextSize);
unsigned long int OLED_Pow(unsigned char m,unsigned char n);
void OLED_ShowNum(unsigned char x, unsigned char y, unsigned long int num, unsigned char len, unsigned char TextSize);
void OLED_Show_Float_Number(unsigned char x,unsigned char y,float num,unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
void Write_IIC_Command(unsigned char Command);
void Write_IIC_Data(unsigned char WriteData);

void OLED_Temp_Humi_Display(float temp,float Humi);
	
#endif 