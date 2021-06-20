#include <stdio.h>
#include "Sensors.h"
#include "gpio-sysfs.h"

#define SYSFS_GPIO_DIR "/sys/class/gpio"

SoilSensor::SoilSensor(){
       	vccPin = 17;
	gpio_export(this->vccPin);
}

bool SoilSensor::isReady(int val) {
	int ret = (this->minVal < val) * (this->maxVal > val);
	printf("Value of the soil moisture sensor: %d\n", val);
	if (ret)
		printf("The value is in the working range: [%d, %d]\n", this->minVal, this->maxVal);
	else
		printf("The value is not in the working range: [%d, %d]\n", this->minVal, this->maxVal);
	return ret;
}

bool SoilSensor::isOn() {

	unsigned int rez;

	gpio_set_dir(this->vccPin, 0);

	gpio_get_value(this->vccPin, &rez);

	return rez;
}

void SoilSensor::turnOn() {
	while (!SoilSensor::getInstance()->isOn()) {
		gpio_set_dir(this->vccPin, 1);
		gpio_set_value(this->vccPin, 1);
	}
}

void SoilSensor::turnOff() {
	while (SoilSensor::getInstance()->isOn()) {
		gpio_set_dir(this->vccPin, 1);
		gpio_set_value(this->vccPin, 0);
	}
}

void SoilSensor::SetRange() {

	FILE* fp = fopen("/var/www/html/Soilparameters.conf", "r");

	int minVal;

	int maxVal;

	fscanf(fp, "%d", &minVal);

	fscanf(fp, "%d", &maxVal);

	if (maxVal < minVal)
	{
		maxVal = maxVal + minVal;

		minVal = maxVal - minVal;

		maxVal = maxVal - minVal;
	}

	this->minVal = minVal;

	this->maxVal = maxVal;

	fclose(fp);
}

SoilSensor::~SoilSensor()
{
	if (instance != NULL)
	{
		delete instance;
		
		instance = NULL;
	}
}

TemperatureSensor::TemperatureSensor(){
       	vccPin = 27;
	gpio_export(this->vccPin);
}

bool TemperatureSensor::isReady(int val) {	
	int ret = (this->minVal < val) * (this->maxVal > val);
	printf("Value of temperature sensor: %d\n", val);
	if (ret)
		printf("The value is in the working range: [%d, %d]\n", this->minVal, this->maxVal);
	else
		printf("The value is not in the working range: [%d, %d]\n", this->minVal, this->maxVal);
	return ret;
}

bool TemperatureSensor::isOn() {	

	unsigned int rez;

	gpio_set_dir(this->vccPin, 0);

	gpio_get_value(this->vccPin, &rez);

	return rez;
}

void TemperatureSensor::turnOn() {
	while (!TemperatureSensor::getInstance()->isOn()) {
		gpio_set_dir(this->vccPin, 1);
		gpio_set_value(this->vccPin, 1);
	}
}

void TemperatureSensor::turnOff() {
	while (TemperatureSensor::getInstance()->isOn()) {
		gpio_set_dir(this->vccPin, 1);
		gpio_set_value(this->vccPin, 0);
	}
}

void TemperatureSensor::SetRange() {

	FILE* fp = fopen("/var/www/html/Temperatureparameters.conf", "r");

	int minVal;

	int maxVal;

	fscanf(fp, "%d", &minVal);

	fscanf(fp, "%d", &maxVal);

	if (maxVal < minVal)
	{
		maxVal = maxVal + minVal;

		minVal = maxVal - minVal;

		maxVal = maxVal - minVal;
	}

	this->minVal = minVal;

	this->maxVal = maxVal;

	fclose(fp);
}

TemperatureSensor::~TemperatureSensor()
{
	if (instance != NULL)
	{
		delete instance;
		
		instance = NULL;
	}
}

BrightnessSensor::BrightnessSensor(){
       	vccPin = 22;
	gpio_export(this->vccPin);
}

bool BrightnessSensor::isReady(int val) {
	bool ret = (this->minVal < val) * (this->maxVal > val);
	printf("Value of brightness sensor: %d\n", val);
	if (ret)
		printf("The value is in the working range: [%d, %d]\n", this->minVal, this->maxVal);
	else
		printf("The value is not in the working range: [%d, %d]\n", this->minVal, this->maxVal);

	return ret;
}

bool BrightnessSensor::isOn() {

	unsigned int rez;

	gpio_set_dir(this->vccPin, 0);
	
	gpio_get_value(this->vccPin, &rez);

	return rez;
}

void BrightnessSensor::turnOn() {
	while (!BrightnessSensor::getInstance()->isOn()) {
		gpio_set_dir(this->vccPin, 1);
		gpio_set_value(this->vccPin, 1);
	}
}

void BrightnessSensor::turnOff() {
	while (BrightnessSensor::getInstance()->isOn()) {
		gpio_set_dir(this->vccPin, 1);
		gpio_set_value(this->vccPin, 0);
	}
}

void BrightnessSensor::SetRange() {

	FILE* fp = fopen("/var/www/html/BrightnessParameters.conf", "r");

	int minVal;

	int maxVal;

	fscanf(fp, "%d", &minVal);

	fscanf(fp, "%d", &maxVal);

	if (maxVal < minVal)
	{
		maxVal = maxVal + minVal;

		minVal = maxVal - minVal;

		maxVal = maxVal - minVal;
	}

	this->minVal = minVal;

	this->maxVal = maxVal;

	fclose(fp);
}

BrightnessSensor::~BrightnessSensor()
{
	if (instance != NULL)
	{
		delete instance;
		
		instance = NULL;
	}
}

