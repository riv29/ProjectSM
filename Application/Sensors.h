#ifndef SENSORS_H_
#define SENSORS_H_

class ISensor {

	protected:
	
		unsigned int vccPin;

		int minVal;

		int maxVal;

	public:
		virtual void turnOff() = 0;

		virtual void turnOn() = 0;
		
		virtual bool isReady(int) = 0;

		virtual void SetRange() = 0; 

		virtual bool isOn() = 0;
};

class SoilSensor: public ISensor {
	
	private:
	       	
		static SoilSensor* instance;

		SoilSensor();
	public:

		void turnOff();

		void turnOn();

		bool isReady(int val);

		bool isOn();

		void SetRange(); 
		
		static ISensor* getInstance() {
			
			if (SoilSensor::instance == NULL)
				SoilSensor::instance = new SoilSensor();
			
			return SoilSensor::instance;
		}


		SoilSensor(SoilSensor &obj) = delete;

		void operator=(const SoilSensor &obj) = delete;

		~SoilSensor();
};

class TemperatureSensor: public ISensor {

	private:

		static TemperatureSensor* instance;

		TemperatureSensor();

	public:

		void turnOff();

		void turnOn();

		bool isReady(int val);

		bool isOn();

		void SetRange(); 

		static ISensor* getInstance() {
			
			if (TemperatureSensor::instance == NULL)
				TemperatureSensor::instance = new TemperatureSensor();
			
			return TemperatureSensor::instance;
		}


		TemperatureSensor(TemperatureSensor &obj) = delete;

		void operator=(const TemperatureSensor &obj) = delete;

		~TemperatureSensor();
};

class BrightnessSensor: public ISensor {

	private:

		static BrightnessSensor* instance;

		BrightnessSensor();
	
	public:

		void turnOff();

		void turnOn();

		bool isReady(int val);

		bool isOn();

		void SetRange();

		static ISensor* getInstance() {
			
			if (BrightnessSensor::instance == NULL)
				BrightnessSensor::instance = new BrightnessSensor();
			
			return BrightnessSensor::instance;
		}


		BrightnessSensor(BrightnessSensor &obj) = delete;

		void operator=(const BrightnessSensor &obj) = delete;

		~BrightnessSensor();
};

#endif
