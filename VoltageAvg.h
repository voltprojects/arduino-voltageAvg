/**
* @author Rhys Bryant <code@voltprojects.com>
* basic library for calculating a moving average of a given voltage
* if you can see an issue or better way please report a bug
* @copyright Rhys Bryant <code@voltprojects.com>
*
* === Legal Jargen  ===
* This code is provided "AS IS" without warranty of any kind.
*   In no event shall the author be held liable for any damages arising from the
*   use of this code.
* @licence LGPL
* this notice MUST not be removed
*/

#include "Arduino.h"
#define CLIprocessor_H 1
#ifndef CLIprocessor_CPP
	#define UPDATE_DELAY 300
	#include "VoltageAvg.cpp"
	//define static values
	float VoltageAvg::refVoltage=0.0;
	unsigned long VoltageAvg::lastUpdate=0;
#endif