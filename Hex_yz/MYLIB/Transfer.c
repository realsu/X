#include "Transfer.h"
#include "pbdata.h"
#include "SCI.h"



u8 TX_Data[51]={0X5A,0XA5,0X33};
int aaaaa=0;

void message_merge(void)
{
		switch(rx_message.StdId&0xF0)
		{
			case 0x10: 
				memcpy(&TX_Data[3],rx_message.Data,8);
				break;
			case 0x20:
				memcpy(&TX_Data[11],rx_message.Data,8);
				break;
			case 0x30:
				memcpy(&TX_Data[19],rx_message.Data,8);
				break;
			case 0x40:
				memcpy(&TX_Data[27],rx_message.Data,8);
				break;
			case 0x50:
				memcpy(&TX_Data[35],rx_message.Data,8);
				break;
			case 0x60:
				memcpy(&TX_Data[43],rx_message.Data,8);
				break;
		}
}




void message_transfer(void)
{
	int tx_N=0;
	for(tx_N=0;tx_N<51;tx_N++)
	{
		 USART_SendData(USART3,TX_Data[tx_N]);
		while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	}
}


