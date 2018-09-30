#ifndef __PSTWO_H
#define __PSTWO_H



#include "stm32f4xx.h"
int key_get(void);
/*
接收器
1号引脚		DI/DAT-->PD15
2号引脚		DO/CMD-->PD13
4号引脚		GND-->GND
5号引脚		VDD-->3.3V
6号引脚		CS/SEL-->PD14
7号引脚		CLK-->PD12

*/
#define DI   PDin(15)           //PB15  输入

#define DO_H PDout(13)=1        //命令位高
#define DO_L PDout(13)=0        //命令位低

#define CS_H PDout(14)=1       //CS拉高
#define CS_L PDout(14)=0       //CS拉低

#define CLC_H PDout(12)=1      //时钟拉高
#define CLC_L PDout(12)=0      //时钟拉低



//These are our button constants
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2          9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16
#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      16



//These are stick values
#define PSS_RX 5                //右摇杆X轴数据
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8



extern u8 Data[9];
extern u16 MASK[16];
extern u16 Handkey;

void PS2_Init(void);
u8 PS2_DataKey(void);		  //键值读取
u8 PS2_AnologData(u8 button); //得到一个摇杆的模拟量
void PS2_ClearData(void);	  //清除数据缓冲区







#endif





