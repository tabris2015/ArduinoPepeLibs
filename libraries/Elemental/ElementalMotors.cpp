/*
	Programa principal para la clase ElementalMotors
*/


#include "Elemental.h"
#include <Arduino.h>

ElementalMotors::ElementalMotors()
{
  // La interfaz con el driver usa 3 pines por motor: 2 para direccion y uno para PWM
  pinMode(R_CTRL_1, OUTPUT);
  pinMode(R_CTRL_2, OUTPUT);
  pinMode(L_CTRL_1, OUTPUT);
  pinMode(L_CTRL_2, OUTPUT);
}

void ElementalMotors::detener()
{
	detenerDerecho();
	detenerIzquierdo();
}

void ElementalMotors::frenar()
{
	frenarDerecho();
	frenarIzquierdo();
}

void ElementalMotors::conducir(int vel)
{
	if(vel > 0)
	{
		derAd((byte)(abs(vel)));
		izqAd((byte)(abs(vel)));	
	}
	else
	{
		derAt((byte)(abs(vel)));
		izqAt((byte)(abs(vel)));
	}
}

void ElementalMotors::conducir(int vel, int duracion)
{
	if(vel > 0)
	{
		derAd((byte)(abs(vel)));
		izqAd((byte)(abs(vel)));	
	}
	else
	{
		derAt((byte)(abs(vel)));
		izqAt((byte)(abs(vel)));
	}
	delay(duracion);
	detenerDerecho();
	detenerIzquierdo();
}

void ElementalMotors::pivotar(int vel)
{
	if(vel > 0)
	{
		derAd((byte)(abs(vel)));
		izqAt((byte)(abs(vel)));	
	}
	else
	{
		derAt((byte)(abs(vel)));
		izqAd((byte)(abs(vel)));
	}
}
void ElementalMotors::pivotar(int vel, int duracion)
{
	if(vel > 0)
	{
		derAd((byte)(abs(vel)));
		izqAt((byte)(abs(vel)));	
	}
	else
	{
		derAt((byte)(abs(vel)));
		izqAd((byte)(abs(vel)));
	}
	delay(duracion);
	detenerDerecho();
	detenerIzquierdo();
}

void ElementalMotors::motorDerecho(int vel)
{
    if (vel > 0)
    {
    	derAd((byte)(abs(vel)));
    }
    else
    {
   		derAt((byte)(abs(vel)));
    }
}

void ElementalMotors::motorDerecho(int vel, int duracion)
{
    if (vel > 0)
    {
    	derAd((byte)(abs(vel)));
    }
    else
    {
   		derAt((byte)(abs(vel)));
    }
    delay(duracion);
    detenerDerecho();
}

void ElementalMotors::motorIzquierdo(int vel)
{
    if (vel > 0)
    {
    	izqAd((byte)(abs(vel)));
    }
    else
    {
   		izqAt((byte)(abs(vel)));
    }
}

void ElementalMotors::motorIzquierdo(int vel, int duracion)
{
    if (vel > 0)
    {
    	izqAd((byte)(abs(vel)));
    }
    else
    {
   		izqAt((byte)(abs(vel)));
    }
    delay(duracion);
    detenerIzquierdo();
}

void ElementalMotors::detenerDerecho()
{
	digitalWrite(R_CTRL_1, LOW);
	digitalWrite(R_CTRL_2, LOW);	
	analogWrite(PWM_R, 0);
}
void ElementalMotors::detenerIzquierdo()
{
	digitalWrite(L_CTRL_1, LOW);
	digitalWrite(L_CTRL_2, LOW);	
	analogWrite(PWM_L, 0);
}

void ElementalMotors::frenarDerecho()
{
	digitalWrite(R_CTRL_1, HIGH);
	digitalWrite(R_CTRL_2, HIGH);	
	analogWrite(PWM_R, 0);
}
void ElementalMotors::frenarIzquierdo()
{
	digitalWrite(L_CTRL_1, HIGH);
	digitalWrite(L_CTRL_2, HIGH);	
	analogWrite(PWM_L, 0);
}

/*
	funciones privadas
*/

void ElementalMotors::derAd(byte vel)
{
	digitalWrite(R_CTRL_1, HIGH);
	digitalWrite(R_CTRL_2, LOW);
	analogWrite(PWM_R, vel);
}

void ElementalMotors::derAt(byte vel)
{
	digitalWrite(R_CTRL_1, LOW);
	digitalWrite(R_CTRL_2, HIGH);
	analogWrite(PWM_R, vel);
}

void ElementalMotors::izqAd(byte vel)
{
	digitalWrite(L_CTRL_1, HIGH);
	digitalWrite(L_CTRL_2, LOW);
	analogWrite(PWM_L, vel);
}

void ElementalMotors::izqAt(byte vel)
{
	digitalWrite(L_CTRL_1, LOW);
	digitalWrite(L_CTRL_2, HIGH);
	analogWrite(PWM_L, vel);
}