#ifndef FOLLOWER_H
#define FOLLOWER_H

#include <Arduino.h>

// for future use
#define NO_FILTER	0
#define FILTER_2S	1
#define FILTER_4S	2
#define FILTER_8S	3

/* SensorArray
	Class for reading a 8 sensor array connected to PORTC
	useful data such as density or position are given for 
	line follower application
*/
class SensorArray
{
public:
	/* Contructor */
	SensorArray(uint8_t en);
	/* Returns the number of sensors on a black area*/
	uint8_t getDensity();
	/* Returns the position of the line relative to the 
	sensor array. When the line is in the center the value is 0 */
	int getPosition();
	/* Returns the value of a specific sensor in the array */
	uint8_t getBit(uint8_t bit);
	/* Take a pointer for filling it with the values */
	void getArray(uint8_t * values);
	/* Returns a byte with binary values of the array */
	uint8_t getRaw();
	/* Perform the measurements */
	void Update();
private:
	uint8_t _data; 				// binary data of the array
	int _position;				// the position of the line relative to the array
	uint8_t _bits[8];			// an array with the binary values
	uint8_t _density;			// the number of sensors over a black area
	
	/* Read the sensors and update members */
	void readSensors(uint8_t * values);
};

/* Motors
	Class for using a dual motor driver such as l298n, l293d...
	it takes 3 pins for each motors, 1 pin for PWM and 2 for direction
*/
class Motors
{
public:
	/* Constructor takes the pins of the driver */
	Motors(	uint8_t l_pwm, 				// EN or PWM pin for left motor
			uint8_t l_ctrl1, 			// IN1 pin for left motor
			uint8_t l_ctrl2, 			// IN2 pin for left motor
			uint8_t r_pwm, 				// EN or PWM pin for right motor
			uint8_t r_ctrl1, 			// IN1 pin for right motor
			uint8_t r_ctrl2);			// IN2 pin for right motor

	/* Drive both motors with given speed, max speed is 255 (resolution of PWM on arduino UNO, NANO, PRO MINI, etc) */
	void drive(int16_t speed);  
	/* Drive the motors with different speeds */
    void drive(int16_t l_speed, int16_t r_speed);
    /* Drive motors in opposite directios */
    void pivot(int16_t speed);
    /* Stop both motors*/
    void stop();
    /* Drive both motors following a differential drive model
    	this need to be refined with the model of the robot */
    void differentialDrive(int16_t linear, int16_t angular);
    
  private:
  	/* Helper functions for driving individual motors*/
  	/* Drive left motor forward */
    void leftForward(uint8_t speed);
    /* Drive left motor backwards */
    void leftBackward(uint8_t speed);
    /* Drive right motor forward */
    void rightForward(uint8_t speed);
    /* Drive right motor backwards */
    void rightBackward(uint8_t speed);

    // pin numbers for motor driver
    uint8_t l_pwm_pin;		
    uint8_t r_pwm_pin;
  	uint8_t l_ctrl1_pin;
  	uint8_t l_ctrl2_pin;
  	uint8_t r_ctrl1_pin;
  	uint8_t r_ctrl2_pin;
};


class pid
{
public:
	pid(float * input, float * output, float * setpoint,
		float inKp, float inKi, float inKd);
	int16_t Compute();
	void SetLimits(float nMin, float nMax);
	void SetParameters(float nKp, float nKi, float nKd);
	void SetDirection(uint16_t dir);
	void SetSampleTime(uint16_t time);

	float getKp();
	float getKi();
	float getKd();

private:
	void Init();

	float * userInput;
	float * userOutput;
	float * userSetpoint;
	
	float kp;
	float ki;
	float kd;

	float ITerm;
	float lastInput;

	uint16_t sampleTime;
	float max_out;
	float min_out;
	uint16_t max_out_int;
	uint16_t min_out_int;
};
#endif
 					