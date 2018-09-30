
#ifndef _kulun_H
#define _kulun_H

#include "pbdata.h"




typedef struct 
{
	u8 function;
	u8 data1;
	u8 data2;
	u8 data3;
	u8 address;
	u16 sum;
	u8 sum_check;
}function_message;


void kunlun_receive_function(void);
void kunlun_send_function(function_message message);
#endif 





