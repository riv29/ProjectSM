/*
 * AD7705 test/demo program for the Raspberry PI
 *
 * Copyright (c) 2007  MontaVista Software, Inc.
 * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
 * Copyright (c) 2013-2020  Bernd Porr <mail@berndporr.me.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Cross-compile with cross-gcc -I/path/to/cross-kernel/include
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "AD7705Callback.h"

SoilSensor *SoilSensor::instance = NULL;

TemperatureSensor *TemperatureSensor::instance = NULL;

BrightnessSensor *BrightnessSensor::instance = NULL;

Valve *Valve::instance = NULL;

// Creates an instance of the AD7705 class.
// Registers the callback.
// Prints data till the user presses a key.
int main(int argc, char *argv[]) {

	AD7705Comm* ad7705comm = new AD7705Comm();
	AD7705Callback ad7705callback;
	ad7705comm->setCallback(&ad7705callback);
	ad7705comm->start(AD7705Comm::SAMPLING_RATE_50HZ);
	getchar();
	ad7705comm->stop();
	delete ad7705comm;
	return 0;
}
