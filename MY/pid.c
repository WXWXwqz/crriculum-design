#include "pid.h"
extern double V_Value;

TypePid PID;
void Pid_Init()
{
	PID.Err=0;
	PID.Err_last=0;
	PID.I=0;
	PID.Kd=0.000;
	PID.Ki=0.00002;
	PID.Kp=0.02;
	PID.ObjtV=0;
	PID.OutV=0;
	PID.SetV=0;
}

float Pid_Cal(float V)
{
	PID.SetV=V;
	PID.ObjtV=V_Value;
	PID.Err=PID.SetV-PID.ObjtV;
	PID.I+=PID.Err;
	PID.Err_last=PID.Err;
	PID.OutV=PID.Kp*PID.Err+PID.Ki*PID.I+PID.Kd*(PID.Err-PID.Err_last);
	return PID.OutV;
}



