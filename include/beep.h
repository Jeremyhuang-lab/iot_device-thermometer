#ifndef _BEEP_H_
#define _BEEP_H_
/*********************************************************************************************************************/

//BZCON
#define BZD(N)		(N<<2)
#define BZH(N)		(N<<1)
#define BZE(N)		(N<<0)

#define BZDIV_V				(16000000/4000)			//buzzerƵ��Ϊ1KHZ
#define BZDUT_V				(BZDIV_V/2)					//ռ�ձ�Ϊ50%

void Beep_Init(void);

#endif 