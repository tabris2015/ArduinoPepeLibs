#include "Follower.h"

Motors::Motors(uint8_t l_pwm, uint8_t l_ctrl1, uint8_t l_ctrl2, uint8_t r_pwm, uint8_t r_ctrl1, uint8_t r_ctrl2)
{
	pinMode(l_ctrl1, OUTPUT);
	pinMode(l_ctrl2, OUTPUT);
	pinMode(r_ctrl1, OUTPUT);
	pinMode(r_ctrl2, OUTPUT);
	l_pwm_pin = l_pwm;
	r_pwm_pin = r_pwm;
	l_ctrl1_pin = l_ctrl1;
	l_ctrl2_pin = l_ctrl2;
	r_ctrl1_pin = r_ctrl1;
	r_ctrl2_pin = r_ctrl2;
}
void Motors::drive(int16_t speed)
{
	if(speed > 0)
	{
		leftForward((uint8_t)abs(speed));
		rightForward((uint8_t)abs(speed));
	}
	else
	{
		leftBackward((uint8_t)abs(speed));
		rightBackward((uint8_t)abs(speed));	
	}
}

void Motors::drive(int16_t l_speed, int16_t r_speed)
{
	if(l_speed > 0)
	{
		leftForward((uint8_t)abs(l_speed));
	}
	else
	{
		leftBackward((uint8_t)abs(l_speed));	
	}

	if(r_speed > 0)
	{
		rightForward((uint8_t)abs(r_speed));
	}
	else
	{
		rightBackward((uint8_t)abs(r_speed));	
	}	
}

void Motors::differentialDrive(int16_t linear, int16_t angular)
{
    float v_right = (float)linear - 0.7 * (float)angular;
    float v_left = (float)linear + 0.7 * (float)angular;
    float mult = 0.5;
    #ifdef DEBUG
    Serial.print("l: ");
    Serial.print(v_left);
    Serial.print(" r: ");
    Serial.println(v_right);	
    #endif
    drive((int16_t)(v_left * mult), (int16_t)(v_right * mult));

}

void Motors::pivot(int16_t speed)
{
	if(speed > 0)
	{
		leftBackward((uint8_t)abs(speed));
		rightForward((uint8_t)abs(speed));
	}
	else
	{
		leftForward((uint8_t)abs(speed));
		rightBackward((uint8_t)abs(speed));	
	}	
}
void Motors::stop()
{
	analogWrite(l_pwm_pin, 0);
	analogWrite(r_pwm_pin, 0);
}
void Motors::leftForward(uint8_t speed)
{
	digitalWrite(l_ctrl1_pin, 0);
	digitalWrite(l_ctrl2_pin, 1);
	analogWrite(l_pwm_pin, speed);
}
void Motors::leftBackward(uint8_t speed)
{
	digitalWrite(l_ctrl1_pin, 1);
	digitalWrite(l_ctrl2_pin, 0);
	analogWrite(l_pwm_pin, speed);
}
void Motors::rightForward(uint8_t speed)
{
	digitalWrite(r_ctrl1_pin, 0);
	digitalWrite(r_ctrl2_pin, 1);
	analogWrite(r_pwm_pin, speed);
}
void Motors::rightBackward(uint8_t speed)
{
	digitalWrite(r_ctrl1_pin, 1);
	digitalWrite(r_ctrl2_pin, 0);
	analogWrite(r_pwm_pin, speed);
}