#include "Valve.h"
#include "gpio-sysfs.h"

Valve::Valve(){
	vccPin = 27;
	wiringPiSetup();
	pinMode(vccPin, OUTPUT);
}

void Valve::turnOn() {
	digitalWrite(this->vccPin, LOW);
}

void Valve::turnOff() {
	digitalWrite(this->vccPin, HIGH);
}

Valve::~Valve()
{
	if (instance != NULL)
	{
		delete instance;
		
		instance = NULL;
	}
}

