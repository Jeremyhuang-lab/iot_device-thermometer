#ifndef _BEEP_C_
#define _BEEP_C_
/*********************************************************************************************************************/
#include "include/Public.h"
/*********************************************************************************************************************/
void Beep_Init(void)
{
	P05F = P05_BEEP_SETTING;

	BZDIVH	= BZDIV_V>>8;
	BZDIVL	= BZDIV_V;
	BZDUTH 	= BZDUT_V>>8;
	BZDUTL 	= BZDUT_V;


	BZCON = BZD(0)|BZH(0)|BZE(0);	
}



#endif 