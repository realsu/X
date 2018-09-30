#ifndef _RC_H
#define _RC_H

#include "pbdata.h"
#include "stdbool.h"

//遥控器参数：速度指令，角度指令，方向指令，初始速度，加速度
typedef struct 
{
		int cmd_speed;
		int cmd_angle; 
		int cmd_direction;
	  int base;
	  int acc;
}flag;

//电机结构体
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
	//角度指令
	long cmd_angle; //cmd_angle
	
	int real_pos;
	int offset;
	
	//达到目标位置标志
	bool arrived; //if this motor has arrived to desired pos, for switching
  //目标速度
	float cmd_spd; //desired speed
	bool busy; //
	
	
	
	float Pos_Deviation;
	
	float NowTarPos ;

}motor;

//机器人状态：初始化，站立，半步，步态，停止
//Init=0,stand,half_step,gait,stop
typedef enum  
{
	Init=0,stand,half_step,gait,stop
}rob_state;

//机器人子状态：初始，步行
//init=0,step1=1
typedef enum
{
	init=0,step1=1
}rob_substate;

//******     电机编号     *******//
//*******************************//
//******  3  ********  6  *******//
//******  5  ********  4  *******//
//******  2  ********  1  *******//
//*******************************//


/*********左边电机编号***********/
#define		L1				3			
#define		L2				5
#define		L3				2
/**********右边电机编号**********/
#define		R1				6
#define		R2				4		
#define		R3				1

//轮子参数：pluse/degree
#define para_wheel 88.88889
//增量式编码器采用5v供电，ABZ电压输出方式(z相悬空)，编码器为500线，四倍频后一圈为2000
//减速比为16：1
//电机输出轴转一度有多少脉冲数(pluse/degree)：para_wheel=2000*16/360=88.888888889


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
