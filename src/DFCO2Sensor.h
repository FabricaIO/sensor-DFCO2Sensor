/*
* This file and associated .cpp file are licensed under the GPLv3 License Copyright (c) 2024 Sam Groveman
*
* CO2 Sensor: https://www.dfrobot.com/product-1565.html
*
* Contributors: Sam Groveman
*/

#pragma once
#include <Arduino.h>
#include <Sensor.h>

class DFCO2Sensor: public Sensor {
	public:
		
		bool begin(int RX_Pin = 16, int TX_Pin = 17);
		bool takeMeasurement();

	private:
		/// @brief Command to read CO2 data from sensor.
		const unsigned char readCO2Data[9] = { 0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79 };
};