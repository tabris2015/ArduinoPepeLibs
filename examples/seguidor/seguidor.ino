#include <Elemental.h>
#define ES_NEGRO(x) (x > 500)
#define ES_BLANCO(x) (x <= 500)
int pin_izq = A0;
int pin_der = A1;

int sensor_izq;
int sensor_der;
ElementalMotors robot;

int distancia;
void setup() {
  Serial.begin(9600);
}
void loop() {
  sensor_izq = analogRead(A0);
  sensor_der = analogRead(A1);
  Serial.print(sensor_izq);
  Serial.print("--");
  Serial.println(sensor_der);

  if(ES_BLANCO(sensor_izq) && ES_BLANCO(sensor_der))
  {
    robot.conducir(100);
  }
  else if(ES_BLANCO(sensor_izq) && ES_NEGRO(sensor_der))
  {
    robot.pivotar(-180);
  }
  else if(ES_NEGRO(sensor_izq) && ES_BLANCO(sensor_der))
  {
    robot.pivotar(180);
  }
  else if(ES_NEGRO(sensor_izq) && ES_NEGRO(sensor_der))
  {
    robot.detener();
  }

}






