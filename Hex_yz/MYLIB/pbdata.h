


#ifndef _pbdata_H
#define _pbdata_H


#include "stm32f4xx.h"
//#include "usart.h"
#include "delay.h"
#include "math.h"
#include "stm32f4xx.h"
#include "can1.h"
#include "sys.h"  
#include "string.h"

#include "kulun.h"
#include "myiic.h"
#include "RC.h"
#include "pstwo.h"
#include "time.h"
#include "Transfer.h"


#include "main.H"
#include "SCI.H"
#include "NVIC.H"

#define abs(x) ((x)>0? (x):(-(x)))


extern u8 TX_Data[];
extern CanRxMsg rx_message;
extern u8 message_ok;
extern float a[3],Angle[3];
extern flag RC;

extern short Real_Current_Value[6];
extern short Real_Velocity_Value[6];
extern long Real_Position_Value[6];





/***************调程序用的参数**********************/
extern u8 x;
extern  int L_position;		//12.5
extern int R_position;		//343.5


#endif



















