#include "DFCO2Sensor.h"

/// @brief Starts the CO2 sensor
/// @param RX_Pin The RX pin to use
/// @param TX_Pin The TX pin to use
/// @return True on success
bool DFCO2Sensor::begin(int RX_Pin, int TX_Pin) {
	Serial2.begin(9600, SERIAL_8N1, RX_Pin, TX_Pin);
	values.resize(1);
	Description.parameterQuantity = 1;
	Description.type = "Environmental Sensor";
	Description.name = "CO2 Sensor";
	Description.parameters = {"CO2"};
	Description.units = {"ppm"};
	Description.id = 3;
	bool result = false;
	return true;
}

/// @brief Take a CO2 measurement and stores it in an internal variable
/// @return True on success
bool DFCO2Sensor::takeMeasurement() {
	// Send command to take measurement
	Serial2.write(readCO2Data, 9);

	// Wait for measurement to be available
	vTaskDelay(500 / portTICK_PERIOD_MS);

	// Read measurement from serial
	for (int i = 0, j = 0; i < 9; i++)
	{
		if (Serial2.available() > 0)
		{
			uint high, low;
			int ch = Serial2.read();
			Serial1.println(ch);
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
}