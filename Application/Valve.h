#ifndef VALVE_H_
#define VALVE_H_

#include <wiringPi.h>

class Valve {
	
	private:
	       	
		static Valve* instance;

		unsigned int vccPin;

		Valve();
	public:

		void turnOff();

		void turnOn();

		static Valve* getInstance() {
			
			if (Valve::instance == 0)
				Valve::instance = new Valve();
			
			return Valve::instance;
		}


		Valve(Valve &obj) = delete;

		void operator=(const Valve &obj) = delete;

		~Valve();
};

#endif
