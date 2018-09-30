

#include "pbdata.h"
#include "kulun.h"


u8 kulun_Number;
int kulun_receive[19];

void kunlun_receive_function(void)
{
	switch(kulun_receive[0])
	{
		case 0x10://电压电流
			
			break;
		case 0x09://电压电流放大100倍
			
			break;
		case 0x11://电流调零

  		break;
		case 0x12://电流校正
	
  		break;
		case 0x13://电压校正
			
			break;
		case 0x14://剩余电量百分比
			
			break;
		case 0x15://额定容量
			
			break;
		case 0x16://剩余电量报警值
			
			break;
		case 0x17://电池欠压值
			
			break;
		case 0x18://电池满电压值
			
			break;
		case 0x19://电池已使用循环次数
			
			break;
		case 0x1A://电流分流器量程设置
			
			break;
		case 0x1B://背光模式
			
			break;
		case 0x1C://模块地址设置
			
			break;
						
		default: 
			break ;
	}
}

u8 send[8]={0x5A,0XA5};

void kunlun_send_function(function_message message)
{
	  int i=0;
		send[2] = message.function;
		send[3] = message.data1;
		send[4] = message.data2;
		send[5] = message.data3;
		send[6] = message.address;
		message.sum = 0x5A+0XA5+send[2]+send[3]+send[4]+send[5]+send[6];
		send[7] = (u8)(message.sum&0XFF);
		for(i=0;i<8;i++)
			USART_SendData(USART2,send[i]);
}






