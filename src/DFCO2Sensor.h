/*
* This file and associated .cpp file are licensed under the GPLv3 License Copyright (c) 2024 Sam Groveman
*
* External libraries needed:
* ESPSoftwareSerial: https://github.com/plerup/espsoftwareserial
*
* CO2 Sensor: https://www.dfrobot.com/product-1565.html
*
* Contributors: Sam Groveman
*/

#pragma once
#include <Arduino.h>
#include <Sensor.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>

/// @brief Device for controlling a DF Robot IR CO2 sensor
class DFCO2Sensor: public Sensor {
	public:
		DFCO2Sensor(String Name, HardwareSerial* SerialPort, int RX_Pin = 16, int TX_Pin = 17);
		DFCO2Sensor(String Name, int RX_Pin, int TX_pin);
		bool begin();
		bool takeMeasurement();

	protected:
		/// @brief Command to read CO2 data from sensor.
		const unsigned char readCO2Data[9] = { 0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79 };

		/// @brief Pointer to hardware serial port, if used
		HardwareSerial* hardwareSerialPort;

		/// @brief SoftwareSerial port, if using
		SoftwareSerial softwareSerialPort;

		/// @brief Indicates if software serial is being used
		bool use_soft_serial = false;

		/// @brief The RX pin used
		int rxpin;

		/// @brief The TX pin used
		int txpin;
};
