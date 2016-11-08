/*
  Elemental.h - Library that contains useful classes for
  examples and projects for the Robotics course of Elemental
*/
#ifndef Elemental_h
#define Elemental_h

#include "Arduino.h"

// pines para los motores
#define    L_CTRL_1   2
#define    L_CTRL_2   4
#define    PWM_L      5

#define    R_CTRL_1   7
#define    R_CTRL_2   8
#define    PWM_R      6

class ElementalMotors
{
	public:
    ElementalMotors();          // Constructor, usado para configurar pines
    void conducir(int speed);  // Conducir ambos motores con la misma velocidad
    void conducir(int speed, int duration);  // conducir con un delay
    void pivotar(int speed);  // Conduce motores en direcciones opuestas
    void pivotar(int speed, int duration);  // pivotar con delay

    void motorDerecho(int speed); // mueve el motor derecho solamente
	void motorIzquierdo(int speed); 

    void motorDerecho(int speed, int duration); 
    void motorIzquierdo(int speed, int duration);  

    void detener();            // Detiene ambos motores
    void frenar();           // Frenado de ambos motores

    void detenerDerecho();       
    void detenerIzquierdo();

    void frenarDerecho(); 
    void frenarIzquierdo();
  private:
    void izqAd(byte speed); 	// funciones primitivas para mover los motores
    void izqAt(byte speed); 	
    void derAd(byte speed);
    void derAt(byte speed);
};

#endif