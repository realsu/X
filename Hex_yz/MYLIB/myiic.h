#ifndef __MYIIC_H
#define __MYIIC_H

#include "REGSREG.h"
#include "pbdata.h"


typedef struct
{
	float x;
	float y;
	float z;
}imu;












//IO��������
//#define SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9����ģʽ
//#define SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9���ģʽ

void SDA_IN(void);
void SDA_OUT(void);

//IO��������	 
#define IIC_SCL    PAout(5) //SCL
#define IIC_SDA    PAout(6) //SDA	 
#define READ_SDA   PAin(6)  //����SDA 

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  


u8 IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data);
u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data);


void ShortToChar(short sData,unsigned char cData[]);
short CharToShort(unsigned char cData[]);
void GY_901_Get(void);
void GY_901_Set_Offset(void);




#endif
















