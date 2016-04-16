#ifndef _PID_H
#define _PID_H
float Pid_Cal(float);
void Pid_Init(void);
typedef struct 
{
	float SetV;
	float ObjtV;
	float Err;
	float Err_last;
	float Kp,Ki,Kd;
	float OutV;
	float I;	
}	TypePid;
#endif 
