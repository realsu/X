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
/***************  配置LED用到的I/O口 *******************/
/*void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/// Enable the GPIO_LED Clock 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	//初始化完后，关闭3个LED
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
}
*/
int main(void)
{     
	
	  u8 PS2_KEY = 0; 
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    CAN1_Configuration();                               //CAN1初始化
    
		LED_GPIO_Config();
		PS2_Init();	
		LED1_ON;LED2_ON;LED3_ON;
		delay_ms(500);  		   //延时300ms
		LED1_OFF;LED2_OFF;LED3_OFF;				    // 灭
	
	
    delay_ms(500);                                      //刚开始要有足够的延时，确保驱动器已经初始化完成 
    CAN_RoboModule_DRV_Reset(0,0);                      //对0组所有驱动器进行复位 
    delay_ms(500); 

    CAN_RoboModule_DRV_Config(0,1,100,0);               //1号驱动器配置为100ms传回一次电流速度位置数据
    delay_us(200);                                      //此处延时为了不让传回数据时候4个不一起传
	
    CAN_RoboModule_DRV_Config(0,2,100,0);               //2号驱动器配置为100ms传回一次电流速度位置数据
    delay_us(200);                                      //此处延时为了不让传回数据时候4个不一起传	
		
    CAN_RoboModule_DRV_Config(0,3,100,0);               //3号驱动器配置为100ms传回一次电流速度位置数据
    delay_us(200);                                      //此处延时为了不让传回数据时候4个不一起传

    CAN_RoboModule_DRV_Config(0,4,100,0);               //4号驱动器配置为100ms传回一次电流速度位置数据
    delay_us(200);                                      //此处延时为了不让传回数据时候4个不一起传

		CAN_RoboModule_DRV_Config(0,5,100,0);               //5号驱动器配置为100ms传回一次电流速度位置数据
    delay_us(200);                                      //此处延时为了不让传回数据时候4个不一起传

    CAN_RoboModule_DRV_Config(0,6,100,0);               //6号驱动器配置为100ms传回一次电流速度位置数据
    delay_us(200);                                      //此处延时为了不让传回数据时候4个不一起传
		
    
    CAN_RoboModule_DRV_Mode_Choice(0,0,OpenLoop_Mode);  //0组的所有驱动器 都进入开环模式
    delay_ms(500);                                      //发送模式选择指令后，要等待驱动器进入模式就绪。所以延时也不可以去掉。
    temp_pwm = 0;
    while(1) //测试加速 No.1
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
    while(1) //测试减速 No.1
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
		    while(1) //测试加速 No.2
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
    while(1) //测试减速 No.2
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
		while(1) //测试加速 No.3
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
    while(1) //测试减速 No.3
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
		while(1) //测试加速 No.4
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
    while(1) //测试减速 No.4
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
		while(1) //测试加速 No.5
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
    while(1) //测试减速 No.5
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
		while(1) //测试加速 No.6
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
    while(1) //测试减速 No.6
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
												while(1) //测试加速 No.1
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
												while(1) //测试减速 No.1
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
												while(1) //测试加速 No.2
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
												while(1) //测试减速 No.2
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
												while(1) //测试加速 No.3
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
												while(1) //测试减速 No.3
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
												while(1) //测试加速 No.4
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
												while(1) //测试减速 No.4
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
										while(1) //测试加速 No.5
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
										while(1) //测试减速 No.5
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
												while(1) //测试加速 No.6
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
												while(1) //测试减速 No.6
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
1.电脑需要提前安装好keil MDK。推荐版本V4.74。
2.本程序适用芯片为STM32F405RGT6，使用25MHz晶振，主频168MHz。
3.如果需要测试CAN的通信，用户所用开发板或者主控板，必须含有CAN收发器，本例程使用的CAN引脚为PA11 PA12。
4.主控芯片如有不同，请自行在工程上修改，CAN引脚如有不同，请自行在can.c文件上修改。
*/
