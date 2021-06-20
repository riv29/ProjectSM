g++ -c AD7705Comm.cpp ad7705_main.cpp gpio-sysfs.cpp Sensors.cpp AD7705Callback.cpp Valve.cpp
g++ -pthread -lwiringPi *.o -o application
rm *.o
