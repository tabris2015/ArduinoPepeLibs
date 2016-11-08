#include "Follower.h"

pid::pid(float * input, float * output, float * setpoint,
	float inKp, float inKi, float inKd)
{
	userInput = input;
	userOutput = output;
	userSetpoint = setpoint;
	SetLimits(-255, 255);
	sampleTime = 100;
	SetParameters(inKp, inKi, inKd);
	Init();
}
int16_t pid::Compute()
{
	float input = *userInput;
	float error = *userSetpoint - input;
	ITerm  += (ki * error);
	if(ITerm > max_out) ITerm = max_out;
	else if(ITerm < min_out) ITerm = min_out;
	float dInput = (input - lastInput);

	float output = kp * error + ITerm - kd * dInput;
	if(output > max_out) output = max_out;
	else if(output < min_out) output = min_out;
	*userOutput = output;
	lastInput = input;
	return (int16_t)output;
}
void pid::SetLimits(float nMin, float nMax)
{
	min_out = nMin;
	max_out = nMax;
}
void pid::SetParameters(float nKp, float nKi, float nKd)
{
	kp = nKp;
	ki = nKi * (sampleTime / 1000.0);
	kd = nKd / (sampleTime / 1000.0);
}

void pid::SetSampleTime(uint16_t ntime)
{
	if(ntime == 0) return;
	float ratio = (float)ntime / (float)sampleTime;
	ki *= ratio;
	kd /= ratio;
	sampleTime = ntime;
}

void pid::Init()
{
	ITerm = *userOutput;
	lastInput = *userInput;
}
