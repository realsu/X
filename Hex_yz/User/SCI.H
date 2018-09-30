#ifndef  _SCI_H_
#define  _SCI_H_

#include "pbdata.h"

#define RS232_REC_BUFF_SIZE				100
#define RS232_END_FLAG1	'#'			//RS232一桢数据结束标志1 
#define RS232_END_FLAG2	'*'			//RS232一桢数据结束标志2 


extern volatile unsigned char RS232_REC_Flag ;
extern volatile unsigned char RS232_buff[RS232_REC_BUFF_SIZE] ;//用于接收数据
extern volatile unsigned int RS232_rec_counter ;//用于RS232接收计数

void RS232_Send_Data(unsigned char *send_buff,unsigned int length);
void USART_Configuration(void);
void UART1SendByte(unsigned char SendData);
void usart_init(void);


#endif
