#include "myiic.h"
#include "delay.h"






//初始化IIC
void IIC_Init(void)
{			
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟

  //GPIOB8,B9初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
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



//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
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
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
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
//不产生ACK应答		    
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
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
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
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}





u8 IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data)
{
  u8 count = 0;
	
	IIC_Start();
	IIC_Send_Byte(dev<<1);	   //发送写命令
	IIC_Wait_Ack();
	IIC_Send_Byte(reg);   //发送地址
  IIC_Wait_Ack();	  
	IIC_Start();
	IIC_Send_Byte((dev<<1)+1);  //进入接收模式	
	IIC_Wait_Ack();
	
    for(count=0;count<length;count++){
		 
		 if(count!=length-1)data[count]=IIC_Read_Byte(1);  //带ACK的读数据
		 	else  data[count]=IIC_Read_Byte(0);	 //最后一个字节NACK
	}
    IIC_Stop();//产生一个停止条件
    return count;
}

/**************************实现函数********************************************
*函数原型:		u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data)
*功　　能:	    将多个字节写入指定设备 指定寄存器
输入	dev  目标设备地址
		reg	  寄存器地址
		length 要写的字节数
		*data  将要写的数据的首地址
返回   返回是否成功
*******************************************************************************/ 
u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data){
  
 	u8 count = 0;
	IIC_Start();
	IIC_Send_Byte(dev<<1);	   //发送写命令
	IIC_Wait_Ack();
	IIC_Send_Byte(reg); 	  //发送地址
	IIC_Wait_Ack();	  
	for(count=0;count<length;count++){
		IIC_Send_Byte(data[count]); 
		IIC_Wait_Ack(); 
 }
	IIC_Stop();//产生一个停止条件

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
		a[0] = (float)CharToShort(&chrTemp[0])/32768*16;		//加速度
		a[1] = (float)CharToShort(&chrTemp[2])/32768*16;
		a[2] = (float)CharToShort(&chrTemp[4])/32768*16;
		w[0] = (float)CharToShort(&chrTemp[6])/32768*2000; //角速度
		w[1] = (float)CharToShort(&chrTemp[8])/32768*2000;
		w[2] = (float)CharToShort(&chrTemp[10])/32768*2000;
		h[0] = CharToShort(&chrTemp[12]);		//磁场输出
		h[1] = CharToShort(&chrTemp[14]);
		h[2] = CharToShort(&chrTemp[16]);
		Angle[0] = (float)CharToShort(&chrTemp[18])/32768*180;  //角度
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










