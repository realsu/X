#ifndef _RC_H
#define _RC_H

#include "pbdata.h"
#include "stdbool.h"

//ң�����������ٶ�ָ��Ƕ�ָ�����ָ���ʼ�ٶȣ����ٶ�
typedef struct 
{
		int cmd_speed;
		int cmd_angle; 
		int cmd_direction;
	  int base;
	  int acc;
}flag;

//����ṹ��
typedef struct 
{
	
	int Wheel1;
	float w_wheel1;
	
	int Wheel2;
	float w_wheel2;
	
	long sum_angle1;
	long sum_angle2; 
	
	int import_ang;
	int import_spd;
	int dir_import;
	

	bool new_cmd; //if a new command arrived
	//�Ƕ�ָ��
	long cmd_angle; //cmd_angle
	
	int real_pos;
	int offset;
	
	//�ﵽĿ��λ�ñ�־
	bool arrived; //if this motor has arrived to desired pos, for switching
  //Ŀ���ٶ�
	float cmd_spd; //desired speed
	bool busy; //
	
	
	
	float Pos_Deviation;
	
	float NowTarPos ;

}motor;

//������״̬����ʼ����վ�����벽����̬��ֹͣ
//Init=0,stand,half_step,gait,stop
typedef enum  
{
	Init=0,stand,half_step,gait,stop
}rob_state;

//��������״̬����ʼ������
//init=0,step1=1
typedef enum
{
	init=0,step1=1
}rob_substate;

//******     ������     *******//
//*******************************//
//******  3  ********  6  *******//
//******  5  ********  4  *******//
//******  2  ********  1  *******//
//*******************************//


/*********��ߵ�����***********/
#define		L1				3			
#define		L2				5
#define		L3				2
/**********�ұߵ�����**********/
#define		R1				6
#define		R2				4		
#define		R3				1

//���Ӳ�����pluse/degree
#define para_wheel 88.88889
//����ʽ����������5v���磬ABZ��ѹ�����ʽ(z������)��������Ϊ500�ߣ��ı�Ƶ��һȦΪ2000
//���ٱ�Ϊ16��1
//��������תһ���ж���������(pluse/degree)��para_wheel=2000*16/360=88.888888889


extern rob_state robState;
extern motor Motor[6];

void para_init(void);
void motor_control_2(int tar_angle,int speet,int motor);

void motor_para(motor *Motor);
void robot_control(int angle,int speed);
void robot_control_1(int angle,int speed);
void motor_control(int tar_angle,int speet,int motor);
void Stand(void);
void Robot_init(void);

void KEY_SWITCH(int key);

/********************************/

void Half_step(void);
void motor_control_3(int tar_angle,int speet,int motor);
void robot_control_3(int angle,int speed);
void robot_control_4(int angle,int speed,int direction);
void robot_control_5(int A_L,int A_R ,int speed,int direction);
void robot_control_6(int Tar_L,int Tar_R,int speed,int direction);
/**********************************/
#endif
