#include "DFCO2Sensor.h"

/// @brief Creates a Bosch BME280 object using hardware serial
/// @param SerialPort Pointer to the serial port to use
/// @param RX_Pin The RX pin to use
/// @param TX_Pin The TX pin to use
DFCO2Sensor::DFCO2Sensor(HardwareSerial* SerialPort, int RX_Pin, int TX_Pin) {
	rxpin = RX_Pin;
	txpin = TX_Pin;
	hardwareSerialPort = SerialPort;
}

/// @brief Creates a Bosch BME280 object using software serial
/// @param RX_Pin The RX pin to use
/// @param TX_Pin The TX pin to use
DFCO2Sensor::DFCO2Sensor(int RX_Pin, int TX_Pin) : softwareSerialPort(RX_Pin, TX_Pin) {
	use_soft_serial = true;
}

bool DFCO2Sensor::begin() {
	Description.parameterQuantity = 1;
	Description.type = "Environmental Sensor";
	Description.name = "CO2 Sensor";
	Description.parameters = {"CO2"};
	Description.units = {"ppm"};
	Description.id = 3;
	values.resize(Description.parameterQuantity);
	if (use_soft_serial) {
		softwareSerialPort.begin(9600);
	} else 
	{
		hardwareSerialPort->begin(9600, SERIAL_8N1, rxpin, txpin);
	}
	return true;
}

bool DFCO2Sensor::takeMeasurement() {
	// Send command to take measurement
	if(use_soft_serial) {
		softwareSerialPort.write(readCO2Data, 9);
	} else {
		hardwareSerialPort->write(readCO2Data, 9);
	}

	// Wait for measurement to be available
	delay(500);
	
	uint high, low;
	int ch;
	// Read measurement from serial
	for (int i = 0, j = 0; i < 9; i++)
	{
		if (use_soft_serial) {
			if (softwareSerialPort.available() > 0)
			{
				ch = softwareSerialPort.read();
			}
		} else {
			if (hardwareSerialPort->available() > 0)
			{
				ch = hardwareSerialPort->read();
			}
		}
		if (i == 2) {
			high = ch;    // High concentration
		}
		if (i == 3) {
			low = ch;    // Low concentration
		}
		if (i == 8) {
			values[0] = high * 256 + low; // CO2 concentration
		}
	}
}
