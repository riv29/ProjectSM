#include "AD7705Callback.h"

#include <signal.h>

int AD7705Callback::hasSample() {

	// let's wait for data for max one second
	// goes to sleep until an interrupt happens
	int ret = gpio_poll(this->sysfs_fd,1000);
	if (ret<1) {
		fprintf(stderr,"Poll error %d\n",ret);
		throw "Interrupt timeout";
	}

	// tell the AD7705 to read the data register (16 bits)
	
	uint8_t tr2 = 0x38;

	uint8_t rx2 = 0;

	struct spi_ioc_transfer tr;
	memset(&tr,0,sizeof(struct spi_ioc_transfer));
	tr.tx_buf = (unsigned long)&tr2;
	tr.rx_buf = (unsigned long)&rx2;
	tr.len = 1;
	tr.delay_usecs = this->delay;
	tr.speed_hz = this->speed;
	tr.bits_per_word = this->bpw;	
	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	
	if (ret < 1)
		throw "can't send spi message";
	// read the data register by performing two 8 bit reads

	uint8_t tx[2] = {0,0};
	uint8_t rx[2] = {0,0};
	
	memset(&tr,0,sizeof(struct spi_ioc_transfer));
	tr.tx_buf = (unsigned long)&tx;
	tr.rx_buf = (unsigned long)&rx;
	tr.len = 2;
	tr.delay_usecs = this->delay;
	tr.speed_hz = this->speed;
	tr.bits_per_word = this->bpw;	
	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	
	if (ret < 1) {
		printf("\n can't send spi message, ret = %d\n",ret);
		throw "Can't send spi message";
	}
	
	return ((rx[0]<<8)|(rx[1]))-0x8000;
}

bool AD7705Callback::QuerySensors() {
	
	bool ret = true;
	
	int value;

	for(std::vector<ISensor*>::iterator it = this->sensors.begin(); it != this->sensors.end(); ++it) {

		this->ChangeSensor(*it);

		value = this->hasSample();

		this->currentSensor->SetRange();

		ret = ret && this->currentSensor->isReady(value);
	}

	this->StopSensors();

	return ret;
}

void AD7705Callback::Pipeline() {

	int seconds;

	while (this->running) {

		do{
			printf("Starting a query in: 30 seconds \n");
			sleep(30);
		} while (!this->QuerySensors());

		solenoid->turnOn();

		printf("Keeping the valve open for: 10 seconds \n");

		sleep(10);

		solenoid->turnOff();
	}
}

void AD7705Callback::StopSensors() {
	
	for (std::vector<ISensor*>::iterator it = this->sensors.begin(); it != this->sensors.end(); ++it)
	
		(*it)->turnOff();

}

void AD7705Callback::ChangeSensor(ISensor* sensor) {

	this->StopSensors();

	currentSensor = sensor;

	currentSensor->turnOn();

}

void AD7705Callback::Start(int sysfs_fd, int fd, const uint32_t speed, const uint16_t delay, const uint8_t bpw)
{
	this->running = 1;

	this->sysfs_fd = sysfs_fd;

	this->fd = fd;

	sensors.push_back(SoilSensor::getInstance());

	sensors.push_back(TemperatureSensor::getInstance());

	solenoid = Valve::getInstance();

	this->speed = speed;

	this->delay = delay;

	this->bpw = bpw;

	solenoid->turnOff();

	this->StopSensors();

	this->Pipeline();
}

void AD7705Callback::Stop()
{
	printf("Stopped\n");

	this->StopSensors();

	this->running = 0;
}

