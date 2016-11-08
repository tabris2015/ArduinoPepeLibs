#include <Follower.h>
#include "defines.h"
SensorArray sensors;
Motors robot(L_PWM, L_CTRL1, L_CTRL1, R_PWM, L_CTRL1, L_CTRL1);

const float kp = 2.0;
const float ki = 0.56;
const float kd = 1.0;

uint16_t ts = 10;
unsigned long lastTime;
float setpoint = 0;
float input;
float output;

pid headingController(&input, &output, &setpoint, kp, ki, kd);

void setup() {
  Serial.begin(38400);
  
  #ifdef DEBUG
  Serial.println("seguidor de linea con pid");
  #endif
  headingController.SetSampleTime(ts);
  lastTime = millis();
}
void loop() {
  
  if((millis() - lastTime) > ts)
  {
    lastTime = millis();

    unsigned long cTime = micros();
    sensors.Update();
    input = (float)sensors.getPosition();
    int16_t heading = headingController.Compute();
    robot.differentialDrive(100, heading);
    cTime = micros() - cTime;
    Serial.println(sensors.getPosition());
    
    #ifdef DEBUG
      Serial.print("port: ");
      Serial.print(PINC, BIN);
      Serial.print(" raw: ");
      Serial.print(sensors.getRaw(), BIN);
      Serial.print(" density: ");
      Serial.print(sensors.getDensity());
      Serial.print(" position: ");
      Serial.print(sensors.getPosition());
      Serial.print(" output: ");
      Serial.print(heading);
      Serial.print(" time: ");
      Serial.println(cTime);
    #endif
  }
  
}
