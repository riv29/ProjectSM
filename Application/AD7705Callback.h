#ifndef AD7705CALLBACK_H_
#define AD7705CALLBACK_H_
#include <iostream>
#include <unistd.h>
#include <vector>
#include "AD7705Comm.h"
#include "Valve.h"
#include "Sensors.h"

class AD7705Callback : public AD7705callback {
	
	private:
		std::vector<ISensor*> sensors;

		ISensor* currentSensor;

		Valve* solenoid;

		int sysfs_fd;

		int fd;
		
		uint32_t speed;

		uint16_t delay;
		
		uint8_t bpw;

		bool QuerySensors();

		unsigned short int running;

		int hasSample(); 

		void Pipeline(); 
		
		void StopSensors();

		void ChangeSensor(ISensor* sensor);

	public:

		virtual void Start(int sysfs_fd, int fd, const uint32_t speed, const uint16_t delay, const uint8_t bpw);
		
		virtual void Stop();
};

#endif
