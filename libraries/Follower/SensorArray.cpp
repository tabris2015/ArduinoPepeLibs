#include "Follower.h"

SensorArray::SensorArray(uint8_t en = 3)
{
	DDRC = 0x00; // all port as input;
	en_pin = en;
	pinMode(en_pin, OUTPUT);
}
uint8_t SensorArray::getDensity()
{
	return _density;
}
int SensorArray::getPosition()
{
	return _position;
}
uint8_t SensorArray::getBit(uint8_t bit)
{
	return _bits[bit];
}
void SensorArray::getArray(uint8_t * values)
{
	for(int i = 0; i < 8; i++)
	{
		*(values + i) = _bits[i];
	}
}
void SensorArray::Update()
{
	readSensors(_bits);
}

uint8_t SensorArray::getRaw()
{
	return _data;
}

void SensorArray::readSensors(uint8_t * values)
{
	// only turn on leds once we need it to save energy
	digitalWrite(en_pin, 1);
	int accum = 0;

	_data = PINC;
	// pins 6 and 7 of PORT C only have analog function
	_data |= (analogRead(A6) > 512) << 6;		// we have to hardcode an analog read
	_data |= (analogRead(A7) > 512) << 7;
	digitalWrite(en_pin, 0);
	_density = 0;
	uint8_t i;
	for(i = 0; i < 8; i++)
	{
		if(((_data >> i) & 0x01) == 1)
		{
			_density++;
			accum += 32 * (i + 1);
		}

		*(values + i) = (_data >> i) && 0x01;
	}

	if (_density > 0)
	{
		_position = accum / _density - 144;
	}
}
