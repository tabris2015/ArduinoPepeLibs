#include <Follower.h>
SensorArray sensors;

void setup() {
  Serial.begin(38400);  
}
void loop() {
  sensors.Update();
  
    Serial.print("port: ");
    Serial.print(PINC, BIN);
    Serial.print(" raw: ");
    Serial.print(sensors.getRaw(), BIN);
    Serial.print(" density: ");
    Serial.print(sensors.getDensity());
    Serial.print(" position: ");
    Serial.println(sensors.getPosition());
  
  delay(500);
}
