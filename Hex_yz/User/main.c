


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
	  CAN_RoboModule_DRV_Reset(0,0);                      //��0���������������и�λ 
    delay_ms(500);                                      //���͸�λָ������ʱ����Ҫ�У��ȴ��������ٴγ�ʼ�����
    CAN_RoboModule_DRV_Config(0,1,50,0);               //1������������Ϊ100ms����һ�ε����ٶ�λ������
    delay_us(200);                                      //�˴���ʱΪ�˲��ô�������ʱ��4����һ��
    CAN_RoboModule_DRV_Config(0,2,50,0);               //2������������Ϊ100ms����һ�ε����ٶ�λ������
    delay_us(200);                                      //�˴���ʱΪ�˲��ô�������ʱ��4����һ��
    CAN_RoboModule_DRV_Config(0,3,50,0);               //3������������Ϊ100ms����һ�ε����ٶ�λ������
    delay_us(200);                                      //�˴���ʱΪ�˲��ô�������ʱ��4����һ��
    CAN_RoboModule_DRV_Config(0,4,50,0);               //4������������Ϊ100ms����һ�ε����ٶ�λ������
		delay_us(200); 
	  CAN_RoboModule_DRV_Config(0,5,50,0);               //3������������Ϊ100ms����һ�ε����ٶ�λ������
    delay_us(200);                                      //�˴���ʱΪ�˲��ô�������ʱ��4����һ��
    CAN_RoboModule_DRV_Config(0,6,50,0); 
	
    CAN_RoboModule_DRV_Mode_Choice(0,0,Velocity_Mode);  //0������������� �����뿪��ģʽ
    delay_ms(500);                                      //����ģʽѡ��ָ���Ҫ�ȴ�����������ģʽ������������ʱҲ������ȥ����		
		TIM3_Int_Init(100,8399);
#if debug == 1		
	////�����˳�ʼ����ң�ز�����ʼ����ң���ٶȡ����ٶȡ������ʼ����������ܽǶ�λ�����㣬��־λ��0��������״̬����Ϊվ������״̬Ϊ��ʼ��
    Robot_init();
		
#endif

		while(1)
		{
			RC.cmd_direction = 0;
			KEY = key_get();    //��ȡ��ֵ
			KEY_SWITCH(KEY);		//���ݰ���ȷ��ÿ�εĿ���ָ���ʼֵ�����ƽǶȡ������ٶȵȣ�
			
			/****************************/
//			for(i=0;i<6;i++)
//				Motor[i].real_pos = Real_Position_Value[i]/para_wheel;
			
#if debug  == 1				/***************������*******************/
			switch(robState)
			{
				case stand:
					////ִ��վ�������Ĵ��������ֻ����˵�ǰ���ڳ�ʼ����������������
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













