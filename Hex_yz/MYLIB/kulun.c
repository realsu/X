

#include "pbdata.h"
#include "kulun.h"


u8 kulun_Number;
int kulun_receive[19];

void kunlun_receive_function(void)
{
	switch(kulun_receive[0])
	{
		case 0x10://��ѹ����
			
			break;
		case 0x09://��ѹ�����Ŵ�100��
			
			break;
		case 0x11://��������

  		break;
		case 0x12://����У��
	
  		break;
		case 0x13://��ѹУ��
			
			break;
		case 0x14://ʣ������ٷֱ�
			
			break;
		case 0x15://�����
			
			break;
		case 0x16://ʣ���������ֵ
			
			break;
		case 0x17://���Ƿѹֵ
			
			break;
		case 0x18://�������ѹֵ
			
			break;
		case 0x19://�����ʹ��ѭ������
			
			break;
		case 0x1A://������������������
			
			break;
		case 0x1B://����ģʽ
			
			break;
		case 0x1C://ģ���ַ����
			
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






