
#include "pbdata.h"
#include "RC.h"

//ң�ز�����־
flag RC;

#define BASE   					100				//�ٶȳ�ʼֵ
#define Stand_spd       300 		//վ���ٶ�
#define init_angle			78						//93



//init_angle �����ĽǶ�
//init_angle ���Ҳ�ĽǶ�
#define l_pos   				355  //360-x
#define r_pos    				35	 //30+x

#define angleOffSet     0.0     //�ŵػ�ƫת����
#define angleExtent   	0.0	
//�ŵػ���չ����

#define MAX_ACC					160

 int L_position = l_pos;		//12.5
 int R_position = r_pos;		//343.5

//ң�ز�����ʼ����ң���ٶȡ����ٶȡ������ʼ��
void para_init(void)
{
	//ң�صĳ�ʼ�ٶ�
	RC.base = BASE;
	//ң�صļ��ٶ�
	RC.acc = 0;
	
//	RC.cmd_angle = R_position + 360 - L_position;
	//ң�صĿ��ƽǶ�(С�����ܽǶ�?)
	RC.cmd_angle =  360 + R_position - L_position;
	//ң�صĿ��Ʒ���
	RC.cmd_direction = 0;
	//ң�صĿ����ٶ�
	RC.cmd_speed = RC.base;
}


//ң�ذ�������������
void KEY_SWITCH(int key)
{
//	int i=0;
	static bool key_flag = 0;
	switch(key)
	{
		case 0x00:
			key_flag = 0;
			break;
		case 0x01:				//ģʽѡ��
				break;
		case 0x02:
				break;
		case 0x03:
				break;
		case 0x04:				//
			break;
		case 0x05:				//��ǰ      ǰ��

			R_position = r_pos;		//12.5
			L_position = l_pos;		//343.5
		
		
			RC.cmd_angle = R_position + 360 - L_position;
		  RC.cmd_speed = RC.base + RC.acc;
		  RC.cmd_direction = 0;
		  x = 1;
				break;
		case 0x06:				//����
			
		  RC.cmd_direction = 10;			//RC.cmd_direction * 2 ����С����ǰ���ĽǶȣ������BUG
			x = 1;
				break;
		case 0x07:				//�������  ����
				break;
		case 0x08:				//����
			
			 RC.cmd_direction = -10;                  //                                                                                                                                                                                                                                                     ;
				 x = 1;
				break;
		case 0x09:				//����     ֹͣ
				x = 0;
				break;
		case 0X0A:				//����
				break;
		case 0X0B:					//����
				break;
		case 0X0C:					//����
				break;
		case 0X0D:						//��ǰ   ����ģʽ
		    if(key_flag == 0)     
				{
					//���ٶ�����10
					RC.acc += 10;   
					//�жϼ��ٶ��Ƿ񳬳���ֵ
					if(RC.acc >=MAX_ACC )
						 RC.acc = MAX_ACC;
					//������ٰ�����������������ٶ�
					RC.cmd_speed = RC.base + RC.acc;
					
					key_flag = 1;
				}
				break;
		case 0X0E:  					//����
				break;
		case 0X0F:					//�Һ�  
				if(key_flag == 0 )
				{
					RC.acc -= 10;  
					if(RC.acc <=-20 )
						 RC.acc = -20;
					RC.cmd_speed = RC.base + RC.acc;
					key_flag = 1;
			  }
				break;
		case 0X10:					//����
			 
				break;
	}
}



motor _Motor;
rob_state robState;
rob_substate robSubState;
u8 arrive[6];
motor Motor[6];

//#define L_position 				-15
//�����˳�ʼ����ң�ز�����ʼ����ң���ٶȡ����ٶȡ������ʼ����������ܽǶ�λ�����㣬��־λ��0��������״̬����Ϊվ����
void Robot_init(void)
{
	int i;
	//ң�ز�����ʼ����ң���ٶȡ����ٶȡ������ʼ��
	para_init();
	
	for (i=0;i<6;i++)
	{
	  Motor[i].sum_angle1 = 0;
	  Motor[i].sum_angle2	= 0;
		Motor[i].new_cmd=false;
		Motor[i].arrived=false;
		Motor[i].busy = false;
//		Motor[i].cmd_lock = false;
	}
	robState=stand;
	robSubState=init;
}

//ִ��վ�������Ĵ��������ֻ����˵�ǰ���ڳ�ʼ����������������

void Stand(void)
{
	int i;
	int j;
	bool allarrived=true;
	switch (robSubState)
	{
		case init:
	    for (i=0;i<6;i++)
	    {		
				Motor[i].sum_angle1 += init_angle;
				Motor[i].cmd_angle=Motor[i].sum_angle1;
				Motor[i].new_cmd=true;
				Motor[i].arrived=false;
				Motor[i].cmd_spd=Stand_spd;
//				Motor[i].cmd_lock = true;
	    }
		  robSubState=step1;
		  break;
	  case step1:
	    for(i=0;i<6;i++)
	    {
        allarrived=allarrived && Motor[i].arrived;	
			}	
      if(allarrived)
			{
				for(j=0;j<6;j++)
				{
				  Motor[i].arrived = false;
					Motor[i].new_cmd = false;
					Motor[i].busy = false;
				}
				robState = half_step;
				robSubState=init;
			}
	     break;	
	 }
		for(i=0;i<6;i++)
			motor_control(Motor[i].cmd_angle,Motor[i].cmd_spd,i+1);
}


void Half_step(void)
{
	u8 i=0;
	u8 j=0;
	bool allarrived=true;
	switch (robSubState)
	{
		
	  case init:	
			
			Motor[L1-1].cmd_angle += R_position;
			Motor[L1-1].cmd_spd = RC.cmd_speed; 
			
			Motor[L3-1].cmd_angle += R_position;
			Motor[L3-1].cmd_spd = RC.cmd_speed;
			
			Motor[R2-1].cmd_angle += R_position;
			Motor[R2-1].cmd_spd = RC.cmd_speed;
		
			Motor[R1-1].cmd_angle += L_position;
			Motor[R1-1].cmd_spd = RC.cmd_speed * L_position/R_position;
			
		  Motor[L2-1].cmd_angle += L_position;
			Motor[L2-1].cmd_spd = RC.cmd_speed * L_position/R_position;
		
			Motor[R3-1].cmd_angle += L_position;
			Motor[R3-1].cmd_spd = RC.cmd_speed * L_position/R_position;
		
			for (i=0;i<6;i++)
			{
				Motor[i].new_cmd=true;
				Motor[i].busy=false;
				Motor[i].arrived=false;
			}
			robSubState=step1;
			break;
		
		case step1:
     for(i=0;i<6;i++)
	    {
        allarrived=allarrived && Motor[i].arrived;	
			}	
      if (allarrived)
			{
				for(j=0;j<6;j++)
				{
				  Motor[i].arrived = false;
					Motor[i].new_cmd = false;
					Motor[i].busy = false;
				}
				robState = gait;
				robSubState=init;
				Motor[i].NowTarPos = Motor[i].cmd_angle;			/********************����***************************/
			}
	    break;
  }
	for(i=0;i<6;i++)
			motor_control(Motor[i].cmd_angle,Motor[i].cmd_spd,i+1);
}

void motor_control(int tar_angle,int speet,int motor)
{
	int motor_error;
	int p = -25;
	int vector_out;

	if( motor == L1 || motor == L2 || motor == L3)
		tar_angle = -tar_angle;
	
	motor_error = Real_Position_Value[motor-1]/para_wheel - tar_angle;	
	vector_out = p * motor_error;

/*****************/
//	Motor[motor-1].real_pos = Real_Position_Value[motor-1]/para_wheel;
/*****************/
	
	if(vector_out > speet)
		vector_out = speet;
	if(vector_out <-speet)
		vector_out = -speet;

	 if(abs(motor_error)<2)
	 {
			 Motor[motor-1].arrived = true;
  		 arrive[motor-1] = 1;	 
	 } 
	CAN_RoboModule_DRV_Velocity_Mode(0,motor,1500,vector_out);
}

void motor_control_2(int tar_angle,int speet,int motor)
{
	 int motor_error;

		if(motor == L3 || motor == L1 || motor == L2)
		{
			motor_error = -Real_Position_Value[motor-1]/para_wheel - tar_angle;
			speet = -speet;
		}
		else 
			motor_error = Real_Position_Value[motor-1]/para_wheel - tar_angle;
	 
	 if(motor_error + 5 >0)
				arrive[motor-1] = 1;
	
	 CAN_RoboModule_DRV_Velocity_Mode(0,motor,4500,speet);
}


/********************************************************/

bool step=1;
void robot_control(int angle,int speed)
{
	if(arrive[0]==1 && arrive[1]==1 && arrive[2]==1 &&arrive[3]==1 && arrive[4]==1 && arrive[5]==1)
	{
			step = !step;
			if(step)
			{
				_Motor.Wheel1 = angle;
				_Motor.w_wheel1 = speed;
				_Motor.Wheel2 = 360 - _Motor.Wheel1;
				_Motor.w_wheel2 = _Motor.w_wheel1 * _Motor.Wheel2 / _Motor.Wheel1;
			}
			else 
			{
				_Motor.Wheel2 = angle;
				_Motor.Wheel1 = 360 - _Motor.Wheel2;
				_Motor.w_wheel2 = speed;
				_Motor.w_wheel1 = _Motor.w_wheel2 * _Motor.Wheel1 / _Motor.Wheel2;
			}		
		
			_Motor.sum_angle1 += _Motor.Wheel1;
			_Motor.sum_angle2 += _Motor.Wheel2;
			
			arrive[0] = 0;
			arrive[1] = 0;
			arrive[2] = 0;
			arrive[3] = 0;
			arrive[4] = 0;
			arrive[5] = 0;
	}
		  motor_control(_Motor.sum_angle2,_Motor.w_wheel2,L3);
			motor_control(_Motor.sum_angle2,_Motor.w_wheel2,L1);
			motor_control(_Motor.sum_angle2,_Motor.w_wheel2,R2);
	
			motor_control(_Motor.sum_angle1,_Motor.w_wheel1,R3);
			motor_control(_Motor.sum_angle1,_Motor.w_wheel1,L2);
			motor_control(_Motor.sum_angle1,_Motor.w_wheel1,R1);
}



void robot_control_1(int angle,int speed)
{
	if(arrive[0]==1 && arrive[1]==1 && arrive[2]==1 &&arrive[3]==1 && arrive[4]==1 && arrive[5]==1)
	{
			step = !step;
			if(step)
			{
				_Motor.Wheel1 = angle;
				_Motor.w_wheel1 = speed;
				_Motor.Wheel2 = 360 - _Motor.Wheel1;
				_Motor.w_wheel2 = _Motor.w_wheel1 * _Motor.Wheel2 / _Motor.Wheel1;
			}
			else 
			{
				_Motor.Wheel2 = angle;
				_Motor.Wheel1 = 360 - _Motor.Wheel2;
				_Motor.w_wheel2 = speed;
				_Motor.w_wheel1 = _Motor.w_wheel2 * _Motor.Wheel1 / _Motor.Wheel2;
			}		
		
			_Motor.sum_angle1 += _Motor.Wheel1;
			_Motor.sum_angle2 += _Motor.Wheel2;
			
			arrive[0] = 0;
			arrive[1] = 0;
			arrive[2] = 0;
			arrive[3] = 0;
			arrive[4] = 0;
			arrive[5] = 0;
	}
	    motor_control_2(_Motor.sum_angle2,_Motor.w_wheel2,L3);
			motor_control_2(_Motor.sum_angle2,_Motor.w_wheel2,L1);
			motor_control_2(_Motor.sum_angle2,_Motor.w_wheel2,R2);
	
			motor_control_2(_Motor.sum_angle1,_Motor.w_wheel1,R3);
			motor_control_2(_Motor.sum_angle1,_Motor.w_wheel1,L2);
			motor_control_2(_Motor.sum_angle1,_Motor.w_wheel1,R1);
}


/************������****************/
static bool STEP[6]={0,1,1,1,0,0};


//��������Ŀ���
//**��������
//**Ŀ��Ƕȣ�Ŀ���ٶȣ�������
void motor_control_3(int tar_angle,int speet,int motor)
{
		//����������
		int motor_error;
		
	  //�������ȣ��������������� 
		//
		if(motor == 2 || motor == 3 || motor == 5)
		{
			//�������=�������ʵλ��/pluse/rad-Ŀ��Ƕȣ���ֵ����0�򵽴�Ŀ��λ�ã���ֵС��0��δ����Ŀ��λ��
			motor_error = -Real_Position_Value[motor-1]/para_wheel - tar_angle;
			speet = -speet;
		}
		else 
			motor_error = Real_Position_Value[motor-1]/para_wheel - tar_angle;
	 //�������������0����ʾ����Ŀ��λ�ã��ٶ�Ϊ0�������־λ��1��true��
	 if(motor_error >0)
	 {
		   speet = 0;
			 Motor[motor-1].arrived = true;
	 }
	
	 CAN_RoboModule_DRV_Velocity_Mode(0,motor,4500,speet);
}


void robot_control_3(int angle,int speed)
{
	  int i,j;
	  bool allarrived=true;
	  switch(robSubState)
		{
			case init:	  
			  for (i=0;i<6;i++)
			  {
					STEP[i] = !STEP[i];
					if(STEP[i])
					{
							Motor[i].Wheel1 = angle;
							Motor[i].w_wheel1 = speed;
							Motor[i].Wheel2 = 360 - Motor[i].Wheel1;
							Motor[i].w_wheel2 = Motor[i].w_wheel1 * Motor[i].Wheel2 / Motor[i].Wheel1;			      
					}
					else 
					{
							Motor[i].Wheel2 = angle;
							Motor[i].Wheel1 = 360 - Motor[i].Wheel2;
							Motor[i].w_wheel2 = speed;
							Motor[i].w_wheel1 = Motor[i].w_wheel2 * Motor[i].Wheel1 / Motor[i].Wheel2;
					}
					
							Motor[i].cmd_angle += Motor[i].Wheel1;
					  	Motor[i].cmd_spd = Motor[i].w_wheel1;
						  Motor[i].arrived = false;
						  Motor[i].new_cmd = true;
						  Motor[i].busy=false;
				}
			   robSubState=step1;
			 break;
			case step1:
         for(i=0;i<6;i++)
	       {
             allarrived=allarrived && Motor[i].arrived;	
			   }	
         if (allarrived)
			   {
				    for(j=0;j<6;j++)
				    {
				      Motor[i].arrived = false;
					    Motor[i].new_cmd = false;
					    Motor[i].busy = false;
				    }
//						if(x == 1)
						{
							robSubState=init;
							x = 0; 
						}	   
				 }
	       break;			 
	}
}

/**************************************************/


void robot_control_4(int angle,int speed,int direction)
{
	  int i,j;
	  bool allarrived=true;
	
	  float spd_rate[2];
		spd_rate[0] = (float)(angle + direction)/angle;
	  spd_rate[1] = (float)(angle - direction)/angle;
	
	  switch(robSubState)
		{
			case init:	 
			  for (i=0;i<6;i++)
			  {
					/******************����ת��****************/
					 if(i == L1-1 || i == L2-1 || i == L3-1)
					 {
							Motor[i].import_ang = angle + direction;
							Motor[i].import_spd = speed * spd_rate[0];
					 }
					 else 
					 {
						 Motor[i].import_ang = angle - direction;
						 Motor[i].import_spd = speed * spd_rate[1];
					 }
					 /******************************************/
					STEP[i] = !STEP[i];
					if(STEP[i])			//С���ȶ�
					{
//							if(direction == 0)			//ת��������Ҫ�����Ƕ�
//									Motor[i].offset = R_position - ( Motor[i].cmd_angle%360 + Motor[i].import_ang - init_angle);
//						  else 
//								  Motor[i].offset = 0;
							
							Motor[i].Wheel1 = Motor[i].import_ang;  		/********/
							Motor[i].w_wheel1 =Motor[i].import_spd;
							Motor[i].Wheel2 = 360 - Motor[i].Wheel1;
							Motor[i].w_wheel2 = Motor[i].w_wheel1 * Motor[i].Wheel2 / Motor[i].Wheel1;			      
					}
					else  //�󻡶ȶ�
					{
//						 if(direction == 0)
//									Motor[i].offset = L_position - ( Motor[i].cmd_angle%360 + (360-Motor[i].import_ang)- init_angle);
//						 else 
//								  Motor[i].offset = 0;
						 
							Motor[i].Wheel2 = Motor[i].import_ang ;		/********/
							Motor[i].Wheel1 = 360 - Motor[i].Wheel2;
							Motor[i].w_wheel2 = Motor[i].import_spd;
							Motor[i].w_wheel1 = (Motor[i].w_wheel2 * Motor[i].Wheel1 / Motor[i].Wheel2)*2;
					}
					
						  Motor[i].cmd_angle += Motor[i].Wheel1;					
					
							Motor[i].cmd_spd = Motor[i].w_wheel1;
						  Motor[i].arrived = false;
						  Motor[i].new_cmd = true;
						  Motor[i].busy=false;
				}
			   robSubState=step1;
			 break;
			case step1:
         for(i=0;i<6;i++)
	       {
             allarrived=allarrived && Motor[i].arrived;	
			   }	
         if (allarrived)
			   {
				    for(j=0;j<6;j++)
				    {
				      Motor[i].arrived = false;
					    Motor[i].new_cmd = false;
					    Motor[i].busy = false;
				    }
					if(x == 1)
						robSubState=init;
				 }
	       break;			 
	}
}
/********/
/*********************

����1��ǰ��ʱ�� init_angle �����ĽǶ�
����2��ǰ��ʱ�� init_angle ���Ҳ�ĽǶ�
����3��ǰ�����ٶ�
����4������ת�Ǵ�С

*********************/
float kp = 0.7;

void robot_control_5(int Tar_L,int Tar_R ,int speed,int direction)
{	
	  int i;
		//���е������Ŀ��λ�ñ�־λ
	  bool allarrived = true;
	  float regulation = (speed-RC.base) * angleOffSet;			//����ʱ������1��2��Ӧ�ĽǶ�����ǰ�ƶ�����ֹ����ʱ��ˤ��
	  float spd_rate[2];
  	float angle_regulation = (speed-RC.base)* angleExtent;		//����ʱ�ʵ��ļӴ�ǰ���ĽǶȣ���ֹԭ��̤��
	 
  	int angle = Tar_R - Tar_L +360;							//ǰ���Ĳ�����С��������ת��ʱ����ٶȱ���
	  spd_rate[0] = (float)(angle + direction)/angle;				//ת��ʱ����ٶȱ���	
	  spd_rate[1] = (float)(angle - direction)/angle;
	
	  if(angle_regulation<0)
			angle_regulation = 0;

	  if(regulation<0)  
			regulation=0;
		
    for(i=0;i<6;i++)
	  {
         allarrived = allarrived && Motor[i].arrived;	
	  }	
	  if(allarrived == true  && x == 1) 			//x��ң�����ı��  
	  {
			for (i=0;i<6;i++)
			{	
				/******************����ת��****************/
					 if(i == L1-1 || i == L2-1 || i == L3-1)
					 {
						  Motor[i].dir_import = direction;
							Motor[i].import_spd = speed * spd_rate[0];
					 }
					 else 
					 {
						Motor[i].dir_import = -direction;
						 Motor[i].import_spd = speed * spd_rate[1];
					 }
				/******************************************/
					 //STEP�������ȵ����ֱ�ʶ0/1��ÿ�ε���Ŀ����л���С������󻡶Ƚ������
					STEP[i] = !STEP[i];
					if(STEP[i])			//С���ȶ�
					{
						  
						  Motor[i].Wheel1 = Tar_R + angle_regulation - regulation + init_angle - Motor[i].cmd_angle%360 + Motor[i].dir_import;		
							Motor[i].w_wheel1 = Motor[i].import_spd;
					}
					else  //�󻡶ȶ�
					{

							Motor[i].Wheel1 = Tar_L - angle_regulation - regulation + init_angle - Motor[i].cmd_angle%360 - Motor[i].dir_import;
							Motor[i].w_wheel1 = Motor[i].import_spd * ((float)Motor[i].Wheel1)/(float)(360-Motor[i].Wheel1);
					}	
					Motor[i].cmd_angle += Motor[i].Wheel1;
					Motor[i].cmd_spd = Motor[i].w_wheel1;
					Motor[i].arrived = false;
			}
		}
		for(i=0;i<6;i++)
		{	
			motor_control_3(Motor[i].cmd_angle,Motor[i].cmd_spd,i+1);
		}
}
/*************************************************************************/


void robot_control_6(int Tar_L,int Tar_R,int speed,int direction)
{
	 
}




