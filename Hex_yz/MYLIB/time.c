




#include "pbdata.h"
#include "time.h"



void Time_init(void)
{
	  TIM_TimeBaseInitTypeDef time;
		NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	  time.TIM_ClockDivision = TIM_CKD_DIV1;
		time.TIM_CounterMode = TIM_CounterMode_Up;
		time.TIM_Period = 499;
	  time.TIM_Prescaler = 8399; 
		TIM_TimeBaseInit(TIM2,&time);

		TIM_Cmd(TIM2,ENABLE);
		TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); 
	
		NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //定时器3中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; //抢占优先级1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; //子优先级3
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
int Msg_cnt=0;
int ddddddddd=0;
//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
			Msg_cnt++;
		  if(Msg_cnt>6)
			{
				Msg_cnt=0;
				message_transfer();
			}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}



void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
	{
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
}

void test(void)
{
}






