#include "main.h"

short temp_pwm = 0;

#define LED1 		GPIOE , GPIO_Pin_13
#define LED2 		GPIOE , GPIO_Pin_14
#define LED3 		GPIOE , GPIO_Pin_15
/*
#define LED1_ON 		GPIO_ResetBits(GPIOE , GPIO_Pin_13)
#define LED2_ON 		GPIO_ResetBits(GPIOE , GPIO_Pin_14)
#define LED3_ON 		GPIO_ResetBits(GPIOE , GPIO_Pin_15)

#define LED1_OFF 		GPIO_SetBits(GPIOE , GPIO_Pin_13)
#define LED2_OFF 		GPIO_SetBits(GPIOE , GPIO_Pin_14)
#define LED3_OFF 		GPIO_SetBits(GPIOE , GPIO_Pin_15)
*/
/***************  ����LED�õ���I/O�� *******************/
/*void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/// Enable the GPIO_LED Clock 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	//��ʼ����󣬹ر�3��LED
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
}
*/
int main(void)
{     
	
	  u8 PS2_KEY = 0; 
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    CAN1_Configuration();                               //CAN1��ʼ��
    
		LED_GPIO_Config();
		PS2_Init();	
		LED1_ON;LED2_ON;LED3_ON;
		delay_ms(500);  		   //��ʱ300ms
		LED1_OFF;LED2_OFF;LED3_OFF;				    // ��
	
	
    delay_ms(500);                                      //�տ�ʼҪ���㹻����ʱ��ȷ���������Ѿ���ʼ����� 
    CAN_RoboModule_DRV_Reset(0,0);                      //��0���������������и�λ 
    delay_ms(500); 

    CAN_RoboModule_DRV_Config(0,1,100,0);               //1������������Ϊ100ms����һ�ε����ٶ�λ������
    delay_us(200);                                      //�˴���ʱΪ�˲��ô�������ʱ��4����һ��
	
    CAN_RoboModule_DRV_Config(0,2,100,0);               //2������������Ϊ100ms����һ�ε����ٶ�λ������
    delay_us(200);                                      //�˴���ʱΪ�˲��ô�������ʱ��4����һ��	
		
    CAN_RoboModule_DRV_Config(0,3,100,0);               //3������������Ϊ100ms����һ�ε����ٶ�λ������
    delay_us(200);                                      //�˴���ʱΪ�˲��ô�������ʱ��4����һ��

    CAN_RoboModule_DRV_Config(0,4,100,0);               //4������������Ϊ100ms����һ�ε����ٶ�λ������
    delay_us(200);                                      //�˴���ʱΪ�˲��ô�������ʱ��4����һ��

		CAN_RoboModule_DRV_Config(0,5,100,0);               //5������������Ϊ100ms����һ�ε����ٶ�λ������
    delay_us(200);                                      //�˴���ʱΪ�˲��ô�������ʱ��4����һ��

    CAN_RoboModule_DRV_Config(0,6,100,0);               //6������������Ϊ100ms����һ�ε����ٶ�λ������
    delay_us(200);                                      //�˴���ʱΪ�˲��ô�������ʱ��4����һ��
		
    
    CAN_RoboModule_DRV_Mode_Choice(0,0,OpenLoop_Mode);  //0������������� �����뿪��ģʽ
    delay_ms(500);                                      //����ģʽѡ��ָ���Ҫ�ȴ�����������ģʽ������������ʱҲ������ȥ����
    temp_pwm = 0;
    while(1) //���Լ��� No.1
    {
        delay_ms(100);
        LED1_ON;
        CAN_RoboModule_DRV_OpenLoop_Mode(0,1,temp_pwm);
        temp_pwm += 500;
        if(temp_pwm > 3000)
        {
            break;
        }
    }
    temp_pwm = 3000;
    while(1) //���Լ��� No.1
    {
        delay_ms(100);
        LED1_OFF;
        CAN_RoboModule_DRV_OpenLoop_Mode(0,1,temp_pwm);
        temp_pwm -= 500;
        if(temp_pwm < 0)
        {
            break;
        }
    }
    temp_pwm = 0;
		    while(1) //���Լ��� No.2
    {
        delay_ms(100);
        LED2_ON;
        CAN_RoboModule_DRV_OpenLoop_Mode(0,2,temp_pwm);
        temp_pwm += 500;
        if(temp_pwm > 3000)
        {
            break;
        }
    }
    temp_pwm = 3000;
    while(1) //���Լ��� No.2
    {
        delay_ms(100);
        LED2_OFF;
        CAN_RoboModule_DRV_OpenLoop_Mode(0,2,temp_pwm);
        temp_pwm -= 500;
        if(temp_pwm < 0)
        {
            break;
        }
    }
		temp_pwm = 0;
		while(1) //���Լ��� No.3
    {
        delay_ms(100);
        LED3_ON;
        CAN_RoboModule_DRV_OpenLoop_Mode(0,3,temp_pwm);
        temp_pwm += 500;
        if(temp_pwm > 3000)
        {
            break;
        }
    }
    temp_pwm = 3000;
    while(1) //���Լ��� No.3
    {
        delay_ms(100);
        LED3_OFF;
        CAN_RoboModule_DRV_OpenLoop_Mode(0,3,temp_pwm);
        temp_pwm -= 500;
        if(temp_pwm < 0)
        {
            break;
        }
    }
				temp_pwm = 0;
		while(1) //���Լ��� No.4
    {
        delay_ms(100);
        LED1_ON;LED2_ON;
			
        CAN_RoboModule_DRV_OpenLoop_Mode(0,4,temp_pwm);
        temp_pwm += 500;
        if(temp_pwm > 3000)
        {
            break;
        }
    }
    temp_pwm = 3000;
    while(1) //���Լ��� No.4
    {
        delay_ms(100);
        LED1_OFF;LED2_OFF;
        CAN_RoboModule_DRV_OpenLoop_Mode(0,4,temp_pwm);
        temp_pwm -= 500;
        if(temp_pwm < 0)
        {
            break;
        }
    }

		temp_pwm = 0;
		while(1) //���Լ��� No.5
    {
        delay_ms(100);
        LED2_ON;LED3_ON;
        CAN_RoboModule_DRV_OpenLoop_Mode(0,5,temp_pwm);
        temp_pwm += 500;
        if(temp_pwm > 3000)
        {
            break;
        }
    }
    temp_pwm = 3000;
    while(1) //���Լ��� No.5
    {
        delay_ms(100);
        LED2_OFF;LED3_OFF;
        CAN_RoboModule_DRV_OpenLoop_Mode(0,5,temp_pwm);
        temp_pwm -= 500;
        if(temp_pwm < 0)
        {
            break;
        }
    }		
		
		temp_pwm = 0;
		while(1) //���Լ��� No.6
    {
        delay_ms(100);
        LED1_ON;LED3_ON;
        CAN_RoboModule_DRV_OpenLoop_Mode(0,6,temp_pwm);
        temp_pwm += 500;
        if(temp_pwm > 3000)
        {
            break;
        }
    }
    temp_pwm = 3000;
    while(1) //���Լ��� No.6
    {
        delay_ms(100);
        LED1_OFF;LED3_OFF;
        CAN_RoboModule_DRV_OpenLoop_Mode(0,6,temp_pwm);
        temp_pwm -= 500;
        if(temp_pwm < 0)
        {
            break;
        }
    }		
    temp_pwm = 0;
    
    CAN_RoboModule_DRV_OpenLoop_Mode(0,0,temp_pwm);
		
	while(1)
	{
	
		PS2_KEY=PS2_DataKey();
		delay_ms(10);
		PS2_KEY = 0;
		PS2_KEY=PS2_DataKey();
		switch(PS2_KEY)
			{		
				
				//case PSB_SELECT: 	LED1_OFF;	 break;
				//case PSB_L3:     	LED1_OFF;	  break;  
				//case PSB_R3:     	PrintChar("PSB_R3 \n");  break;  
				//case PSB_START:  	LED1_ON;   break;  
				case PSB_PAD_UP: 	
												temp_pwm = 0;
												while(1) //���Լ��� No.1
												{
														delay_ms(100);
														LED1_ON;
														CAN_RoboModule_DRV_OpenLoop_Mode(0,1,temp_pwm);
														temp_pwm += 500;
														if(temp_pwm > 3000)
														{
																break;
														}
												}
												temp_pwm = 3000;
												while(1) //���Լ��� No.1
												{
														delay_ms(100);
														LED1_OFF;
														CAN_RoboModule_DRV_OpenLoop_Mode(0,1,temp_pwm);
														temp_pwm -= 500;
														if(temp_pwm < 0)
														{
																break;
														}
												}

				break;  
				case PSB_PAD_RIGHT:	
												temp_pwm = 0;
												while(1) //���Լ��� No.2
												{
														delay_ms(100);
														LED2_ON;
														CAN_RoboModule_DRV_OpenLoop_Mode(0,2,temp_pwm);
														temp_pwm += 500;
														if(temp_pwm > 3000)
														{
																break;
														}
												}
												temp_pwm = 3000;
												while(1) //���Լ��� No.2
												{
														delay_ms(100);
														LED2_OFF;
														CAN_RoboModule_DRV_OpenLoop_Mode(0,2,temp_pwm);
														temp_pwm -= 500;
														if(temp_pwm < 0)
														{
																break;
														}
												}

				break;
				case PSB_PAD_DOWN:	
												temp_pwm = 0;
												while(1) //���Լ��� No.3
												{
														delay_ms(100);
														LED3_ON;
														CAN_RoboModule_DRV_OpenLoop_Mode(0,3,temp_pwm);
														temp_pwm += 500;
														if(temp_pwm > 3000)
														{
																break;
														}
												}
												temp_pwm = 3000;
												while(1) //���Լ��� No.3
												{
														delay_ms(100);
														LED3_OFF;
														CAN_RoboModule_DRV_OpenLoop_Mode(0,3,temp_pwm);
														temp_pwm -= 500;
														if(temp_pwm < 0)
														{
																break;
														}
												}

				break; 
				case PSB_PAD_LEFT:	
												temp_pwm = 0;
												while(1) //���Լ��� No.4
												{
														delay_ms(100);
														LED1_ON;LED2_ON;
													
														CAN_RoboModule_DRV_OpenLoop_Mode(0,4,temp_pwm);
														temp_pwm += 500;
														if(temp_pwm > 3000)
														{
																break;
														}
												}
												temp_pwm = 3000;
												while(1) //���Լ��� No.4
												{
														delay_ms(100);
														LED1_OFF;LED2_OFF;
														CAN_RoboModule_DRV_OpenLoop_Mode(0,4,temp_pwm);
														temp_pwm -= 500;
														if(temp_pwm < 0)
														{
																break;
														}
												}

				break; 
				
				case PSB_TRIANGLE:      	
										temp_pwm = 0;
										while(1) //���Լ��� No.5
										{
												delay_ms(100);
												LED2_ON;LED3_ON;
												CAN_RoboModule_DRV_OpenLoop_Mode(0,5,temp_pwm);
												temp_pwm += 500;
												if(temp_pwm > 3000)
												{
														break;
												}
										}
										temp_pwm = 3000;
										while(1) //���Լ��� No.5
										{
												delay_ms(100);
												LED2_OFF;LED3_OFF;
												CAN_RoboModule_DRV_OpenLoop_Mode(0,5,temp_pwm);
												temp_pwm -= 500;
												if(temp_pwm < 0)
												{
														break;
												}
										}		

				break; 
				case PSB_CIRCLE:  
										temp_pwm = 0;
												while(1) //���Լ��� No.6
												{
														delay_ms(100);
														LED1_ON;LED3_ON;
														CAN_RoboModule_DRV_OpenLoop_Mode(0,6,temp_pwm);
														temp_pwm += 500;
														if(temp_pwm > 3000)
														{
																break;
														}
												}
												temp_pwm = 3000;
												while(1) //���Լ��� No.6
												{
														delay_ms(100);
														LED1_OFF;LED3_OFF;
														CAN_RoboModule_DRV_OpenLoop_Mode(0,6,temp_pwm);
														temp_pwm -= 500;
														if(temp_pwm < 0)
														{
																break;
														}
												}

				break; 
				//case PSB_L1:      	PrintChar("PSB_L1 \n");  break; 
				//case PSB_R1:      	PrintChar("PSB_R1 \n");  break;     
				case 	PSB_L2:
				//temp_pwm = 0;
    
				//CAN_RoboModule_DRV_OpenLoop_Mode(0,0,temp_pwm);
				break; 
				case 	PSB_R2: LED3_OFF;  break; 
				case PSB_CROSS:   	LED2_OFF;   break; 
				case PSB_SQUARE:  	LED3_ON;  break;
				
				default:  break; 
			}

	}
	
}


/*
1.������Ҫ��ǰ��װ��keil MDK���Ƽ��汾V4.74��
2.����������оƬΪSTM32F405RGT6��ʹ��25MHz������Ƶ168MHz��
3.�����Ҫ����CAN��ͨ�ţ��û����ÿ�����������ذ壬���뺬��CAN�շ�����������ʹ�õ�CAN����ΪPA11 PA12��
4.����оƬ���в�ͬ���������ڹ������޸ģ�CAN�������в�ͬ����������can.c�ļ����޸ġ�
*/
