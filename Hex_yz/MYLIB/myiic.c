#include "myiic.h"
#include "delay.h"






//��ʼ��IIC
void IIC_Init(void)
{			
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��

  //GPIOB8,B9��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	IIC_SCL=1;
	IIC_SDA=1;
}

void SDA_IN(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void SDA_OUT(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	 GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
}



//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
  for(i=0;i<8;i++ )
	{
		IIC_SCL=0; 
		delay_us(2);
		IIC_SCL=1;
		receive<<=1;
		if(READ_SDA)receive++;   
		delay_us(1); 
  }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}





u8 IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data)
{
  u8 count = 0;
	
	IIC_Start();
	IIC_Send_Byte(dev<<1);	   //����д����
	IIC_Wait_Ack();
	IIC_Send_Byte(reg);   //���͵�ַ
  IIC_Wait_Ack();	  
	IIC_Start();
	IIC_Send_Byte((dev<<1)+1);  //�������ģʽ	
	IIC_Wait_Ack();
	
    for(count=0;count<length;count++){
		 
		 if(count!=length-1)data[count]=IIC_Read_Byte(1);  //��ACK�Ķ�����
		 	else  data[count]=IIC_Read_Byte(0);	 //���һ���ֽ�NACK
	}
    IIC_Stop();//����һ��ֹͣ����
    return count;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data)
*��������:	    ������ֽ�д��ָ���豸 ָ���Ĵ���
����	dev  Ŀ���豸��ַ
		reg	  �Ĵ�����ַ
		length Ҫд���ֽ���
		*data  ��Ҫд�����ݵ��׵�ַ
����   �����Ƿ�ɹ�
*******************************************************************************/ 
u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data){
  
 	u8 count = 0;
	IIC_Start();
	IIC_Send_Byte(dev<<1);	   //����д����
	IIC_Wait_Ack();
	IIC_Send_Byte(reg); 	  //���͵�ַ
	IIC_Wait_Ack();	  
	for(count=0;count<length;count++){
		IIC_Send_Byte(data[count]); 
		IIC_Wait_Ack(); 
 }
	IIC_Stop();//����һ��ֹͣ����

    return 1; //status == 0;
	
}







int16_t Math_hz=0;
short i=0;
unsigned char chrTemp[30];
unsigned char str[100];
float a[3],w[3],h[3],Angle[3];

void ShortToChar(short sData,unsigned char cData[])
{
	cData[0]=sData&0xff;
	cData[1]=sData>>8;
}
short CharToShort(unsigned char cData[])
{
	return ((short)cData[1]<<8)|cData[0];
}



void GY_901_Get(void)
{
		IICreadBytes(0x50, AX, 24,&chrTemp[0]);
		a[0] = (float)CharToShort(&chrTemp[0])/32768*16;		//���ٶ�
		a[1] = (float)CharToShort(&chrTemp[2])/32768*16;
		a[2] = (float)CharToShort(&chrTemp[4])/32768*16;
		w[0] = (float)CharToShort(&chrTemp[6])/32768*2000; //���ٶ�
		w[1] = (float)CharToShort(&chrTemp[8])/32768*2000;
		w[2] = (float)CharToShort(&chrTemp[10])/32768*2000;
		h[0] = CharToShort(&chrTemp[12]);		//�ų����
		h[1] = CharToShort(&chrTemp[14]);
		h[2] = CharToShort(&chrTemp[16]);
		Angle[0] = (float)CharToShort(&chrTemp[18])/32768*180;  //�Ƕ�
		Angle[1] = (float)CharToShort(&chrTemp[20])/32768*180;
		Angle[2] = (float)CharToShort(&chrTemp[22])/32768*180;
}






unsigned char dd[30];
imu A_OFFSET,G_OFFSET;
u8 data[6][2];
short aa[5]={0X01,0X02,0X03};
u8 bb[5]={0XFF,0XAA,0X50};
u8 cc[5]={0XFF,0XAA,0X50};
u8 c=4;
#define number 30
void GY_901_Set_Offset(void)
{
	int i = 0;
	float asum[3];
	float wsum[3];
	float hsum[3];
	for(i=0;i<number;i++)
	{
		GY_901_Get();
		asum[0]+=a[0];
		asum[1]+=a[1];
		asum[2]+=a[2];
		wsum[0]+=w[0];
		wsum[1]+=w[1];
		wsum[2]+=w[2];
		delay_ms(50);
	}
	
		A_OFFSET.x = asum[0]/number;
		A_OFFSET.y = asum[1]/number;
		A_OFFSET.z = asum[2]/number;
	
		G_OFFSET.x = wsum[0]/number;
		G_OFFSET.y = wsum[1]/number;
		G_OFFSET.z = wsum[2]/number;
	
//		aa[0] = ((u8)A_OFFSET.x)&0xff;
//		aa[1] = (u8)A_OFFSET.x>>8&0xff;
	
//		IICwriteBytes(0x50,AXOFFSET,2,aa);
//		IICreadBytes(0x50, AXOFFSET, 24,&dd[0]);
	
//	  aa[3]=A_OFFSET.x;
//	  aa[4]=0;
//	  bb[3]=A_OFFSET.y;
//	  bb[4]=0;
//		cc[3]=A_OFFSET.z;
//		cc[4]=0;
//	
//		asum[i]=0;
//		wsum[i]=0;
//	  data[0][0]=(u8)(A_OFFSET.x);
//	  data[0][1]=(u8)(0xff&(A_OFFSET.x<<8));
//	
//	  data[1][0]=(u8)(A_OFFSET.y);
//	  data[1][1]=(u8)(0xff&(A_OFFSET.y<<8));
//	
//		data[2][0]=(u8)(A_OFFSET.z);
//	  data[2][1]=(u8)(0xff&(A_OFFSET.z<<8));
//	
//		data[3][0]=(u8)(0xff&G_OFFSET.x);
//	  data[3][1]=(u8)(0xff&(G_OFFSET.x<<8));
//	
//	  data[4][0]=(u8)(0xff&G_OFFSET.y);
//	  data[4][1]=(u8)(0xff&(G_OFFSET.y<<8));
//	
//		data[5][0]=(u8)(0xff&G_OFFSET.z);
//	  data[5][1]=(u8)(0xff&(G_OFFSET.z<<8));
//	

//		IICwriteBytes(0x50,AYOFFSET,5,bb);
//		IICwriteBytes(0x50,AZOFFSET,5,cc);
//		  IICwriteBytes( 0x50,0x05,1,&c);
//		  IICwriteBytes( 0x50,0x06,1,&c);
//		  IICwriteBytes( 0x50,0x07,1,&c);
//			IICreadBytes(0x50, AXOFFSET, 24,&dd[0]);
//		IICwriteBytes(0x50,GXOFFSET,1,data[3]);
//		IICwriteBytes(0x50,GYOFFSET,1,data[4]);
//		IICwriteBytes(0x50,GZOFFSET,1,data[5]);
}










