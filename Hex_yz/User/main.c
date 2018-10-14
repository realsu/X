


#include "pbdata.h"

#define debug 1



int KEY=0;
u8 x=1;

int main(void)
{
		int i;
		delay_init(168);
		NVIC_Configuration();
	USART_Configuration();
//	usart_init();
		CAN1_Configuration();
		IIC_Init();
	  PS2_Init();
		delay_ms(500);
	  CAN_RoboModule_DRV_Reset(0,0);                      //对0组所有驱动器进行复位 
    delay_ms(500);                                      //发送复位指令后的延时必须要有，等待驱动器再次初始化完成
    CAN_RoboModule_DRV_Config(0,1,50,0);               //1号驱动器配置为100ms传回一次电流速度位置数据
    delay_us(200);                                      //此处延时为了不让传回数据时候4个不一起传
    CAN_RoboModule_DRV_Config(0,2,50,0);               //2号驱动器配置为100ms传回一次电流速度位置数据
    delay_us(200);                                      //此处延时为了不让传回数据时候4个不一起传
    CAN_RoboModule_DRV_Config(0,3,50,0);               //3号驱动器配置为100ms传回一次电流速度位置数据
    delay_us(200);                                      //此处延时为了不让传回数据时候4个不一起传
    CAN_RoboModule_DRV_Config(0,4,50,0);               //4号驱动器配置为100ms传回一次电流速度位置数据
		delay_us(200); 
	  CAN_RoboModule_DRV_Config(0,5,50,0);               //3号驱动器配置为100ms传回一次电流速度位置数据
    delay_us(200);                                      //此处延时为了不让传回数据时候4个不一起传
    CAN_RoboModule_DRV_Config(0,6,50,0); 
	
    CAN_RoboModule_DRV_Mode_Choice(0,0,Velocity_Mode);  //0组的所有驱动器 都进入开环模式
    delay_ms(500);                                      //发送模式选择指令后，要等待驱动器进入模式就绪。所以延时也不可以去掉。		
		TIM3_Int_Init(100,8399);
#if debug == 1		
	////机器人初始化：遥控参数初始化【遥控速度、加速度、方向初始化】，电机总角度位移清零，标志位置0，机器人状态设置为站立，子状态为初始化
    Robot_init();
		
#endif

		while(1)
		{
			RC.cmd_direction = 0;
			KEY = key_get();    //获取键值
			KEY_SWITCH(KEY);		//根据按键确定每次的控制指令初始值（控制角度、控制速度等）
			
			/****************************/
//			for(i=0;i<6;i++)
//				Motor[i].real_pos = Real_Position_Value[i]/para_wheel;
			
#if debug  == 1				/***************调试中*******************/
			switch(robState)
			{
				case stand:
					////执行站立动作的处理函数：分机器人当前处于初始情况和正常步行情况
					Stand();
					break;
				case half_step:
					Half_step();
					break;
				case gait:
					robot_control_5(L_position,R_position,RC.cmd_speed,RC.cmd_direction);
					break;
				default:
					break;
			}
			
//			message_transfer();
			
			
			
		
//			for (i=0;i<6;i++)
//			{
////	  	if there are new cmd to exec for each motor
//				 if(Motor[i].new_cmd == true)
//				 {
//					 motor_control_3(Motor[i].cmd_angle,Motor[i].cmd_spd,i+1);	 					 
//					 Motor[i].new_cmd=false;
//					 Motor[i].busy=true;
//				 }
//			}
//			//read feedback
//			for (i=0;i<6;i++)
//			{
//					if(Motor[i].busy == true)
//					{
//							 if(i == 1 || i == 2 || i == 4 )	
//								 Motor[i].real_pos = - Real_Position_Value[i]/para_wheel;
//							 else 
//								 Motor[i].real_pos = Real_Position_Value[i]/para_wheel;
//				
//							 if(Motor[i].real_pos > Motor[i].cmd_angle)
//							 {
//										Motor[i].arrived = true;
//										Motor[i].busy = false;
//										motor_control_3(Motor[i].cmd_angle,0,i+1);
//							 }
//					}
//			}
#else 
//			CAN_RoboModule_DRV_Velocity_Mode(0,1,4500,300);
			CAN_RoboModule_DRV_Velocity_Mode(0,2,4500,300);
//			CAN_RoboModule_DRV_Velocity_Mode(0,3,4500,300);
//			CAN_RoboModule_DRV_Velocity_Mode(0,4,4500,300);
//			CAN_RoboModule_DRV_Velocity_Mode(0,5,4500,300);
//			CAN_RoboModule_DRV_Velocity_Mode(0,6,4500,300);
#endif			
			
		}
}













