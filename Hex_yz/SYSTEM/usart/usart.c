#include "sys.h"
#include "usart.h"	
#include "pbdata.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.


//#if SYSTEM_SUPPORT_OS
//#include "includes.h"					//ucos ʹ��	  
//#endif







//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
//#if 1
//#pragma import(__use_no_semihosting)             
////��׼����Ҫ��֧�ֺ���                 
//struct __FILE 
//{ 
//	int handle; 
//}; 

//FILE __stdout;       
////����_sys_exit()�Ա���ʹ�ð�����ģʽ    
//_sys_exit(int x) 
//{ 
//	x = x; 
//} 
//�ض���fputc���� 
//int fputc(int ch, FILE *f)
//{ 	
//	while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
//	USART3->DR = (u8) ch;      
//	return ch;
//}
//#endif
 
#if EN_USART2_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	

//��ʼ��IO ����1 
//bound:������
void uart_init(u32 bound){

}


void USART_Configuration(void)
{ 
	NVIC_InitTypeDef   NVIC_InitStructure;

	GPIO_InitTypeDef GPIO_InitStructure;

	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	
	USART_DeInit(USART3);
	
	USART_StructInit(&USART_InitStructure);
	USART_ClockStructInit(&USART_ClockInitStruct);	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    //����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3);        //�ܽ�PA9����ΪUSART1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;        
	GPIO_Init(GPIOD, &GPIO_InitStructure);                                                                                                                 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3);
	
	USART_ClockInit(USART3,&USART_ClockInitStruct);


	USART_InitStructure.USART_BaudRate = 115200; //���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No; //��У��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3,&USART_InitStructure); 

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);        ///////�����ж�ʹ��
	USART_ClearITPendingBit(USART3, USART_IT_TC);//����ж�TCλ
	USART_Cmd(USART3,ENABLE);//���ʹ�ܴ���
	
	/* Set the Vector Table base location at 0x08000000 */
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
	
	/* 2 bit for pre-emption priority, 2 bits for subpriority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
											
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}






static u32 sum=0xA5 + 0X5A;
int check(u8 res)
{
		sum += res;
		return (sum-res)&0xff;
}



extern u8 kulun_Number ;
extern int kulun_receive[19];
int state=0;
int cnts;


void USART2_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������
		
		if(state == 0x5A && state == 0) 
			state = 1;
		else if(state == 0xA5 && state == 1)
		{
			state = 2;
			return;
		}
		if(state == 2)
		{
#if method == 1
			
			kulun_receive[cnts] = Res;
			if( check(Res)==Res && (cnts==(8-2-1) || cnts==(19-2-1) || cnts==(15-2-1) ) )
			{	
				kulun_Number = cnts;
				state = 0;
				cnts = 0;
				sum = 0XA5 + 0X5A;
			}
			cnts++;
			
#else
			
#endif
			
		}
		if((USART_RX_STA&0x8000)==0)//����δ���
		{
			if(USART_RX_STA&0x4000)//���յ���0x0d
			{
				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else USART_RX_STA|=0x8000;	//��������� 
			}
			else //��û�յ�0X0D
			{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
  } 
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
#endif	

u8 res;

void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
			res = USART_ReceiveData(USART3);
	}
	USART_ClearFlag(USART3,USART_FLAG_RXNE);
}






