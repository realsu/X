#include "ps2.h"
#include "sys.h"
#include "delay.h"



u16 Handkey;
u8 Comd[2]={0x01,0x42};	//��ʼ�����������
u8 scan[9]={0x01,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//{0x01,0x42,0x00,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A};	// ���Ͷ�ȡ

u8 Data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //���ݴ洢����
u16 MASK[]={
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
	};	//����ֵ�밴����


void PS2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	/*����GPIOD������ʱ��*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;	 //DO CS CLK
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      /*��������ģʽΪͨ���������*/
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	//DI
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
	//GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	DO_H;
	CLC_H;
	CS_H;

}

//��ȡ�ֱ�����
u8 PS2_ReadData(u8 command)
{

	u8 i,j=1;
	u8 res=0; 
    for(i=0; i<=7; i++)          
    {
		if(command&0x01)
			DO_H;
		else
			DO_L;
		command = command >> 1;
		delay_us(10);
		CLC_L;
		delay_us(10);
		if(DI) 
			res = res + j;
		j = j << 1; 
		CLC_H;
		delay_us(10);	 
    }
    DO_H;
	delay_us(50);
    return res;	
}

//�Զ������� PS2 �����ݽ��д���
//����Ϊ 0�� δ����Ϊ 1
unsigned char PS2_DataKey()
{
	u8 index = 0, i = 0;

	PS2_ClearData();
	CS_L;
	for(i=0;i<9;i++)	//����ɨ�谴��
	{
		Data[i] = PS2_ReadData(scan[i]);	
	} 
	CS_H;
	

	Handkey=(Data[4]<<8)|Data[3];     //����16������  ����Ϊ0�� δ����Ϊ1
	for(index=0;index<16;index++)
	{	    
		if((Handkey&(1<<(MASK[index]-1)))==0)
			return index+1;
	}
	return 0;          //û���κΰ�������
}

//�õ�һ��ҡ�˵�ģ����	 ��Χ0~256
u8 PS2_AnologData(u8 button)
{
	return Data[button];
}

//������ݻ�����
void PS2_ClearData()
{
	u8 a;
	for(a=0;a<9;a++)
		Data[a]=0x00;
}
