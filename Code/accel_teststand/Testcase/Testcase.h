////////////////////////////////////////////////////////////
//
// Source file	: Testcase.h
// Author				: Nikolaj
// Date 				: 9 Apr 2020
// Version 			:
//
// Description :
//
////////////////////////////////////////////////////////////
#ifndef TESTCASE_TESTCASE_H_
#define TESTCASE_TESTCASE_H_

//includes
#include "Bus.h"
#include "ADXL345.h"
#include "I2C.h"
#include "ISensor.h"
#include "KX224.h"
#include "SPI.h"
#include "PWM.h"
#include "testStats.hpp"

//defines for PWM
#define BBB	"BBB"
#define PB	"PB"

const unsigned int ONEFREQ = 1;
const unsigned int SWEEP = 2;
const unsigned int DUTY = 50;

//bus for sensors
#define BUSADXL345 1
#define BUSKX224   1

//slave addresses
const unsigned int ADXL345I2C = 0x53;
const unsigned int KX224I2C = 0x1E; 	//or 0x1F
//spi id
const unsigned int ADXL345SPI = 0;
const unsigned int KX224SPI = 0;

//defines for samples
#define SAMPLES_I2C_ADXL 1600*5		//output rate 1600 Hz * seconds
#define SAMPLES_SPI_ADXL 3200*5		//output rate 3200 Hz * seconds
#define SAMPLES_I2C_KX224 1600*5	//output rate 1600 Hz * seconds
#define SAMPLES_SPI_KX224 3200		//output rate ?? Hz * seconds

class Testcase {
public:
	Testcase();
	Testcase(int sensorID_,int sensorType_, int startFrequency_, int stopFrequency_,
			int stepFrequency_, int stepTimeMs_);
	virtual ~Testcase();
	int startTestcase();
	dataPoint * getDataPoints() {return this->dataP;};
private:
	//sensor enums
	enum SENSORS {
		adxl345 = 1, kx224 = 2
	};
	enum SENSORTYPE {
		spi = 1, i2c = 2, analog = 3
	};

	//variables from testconfig
	int sensorID;		//from testconfig to ISensor/Bus
	int sensorType;		//from testconfig to ISensor/Bus
	int startFrequency;	//from testconfig to PWM
	int stopFrequency;	//from testconfig to PWM
	int stepFrequency;  	//from testconfig to PWM
	int stepTimeMs;		//from testconfig to PWM

	dataPoint *dataP;

	//functions
	int initpwm(PWM pwm);

};

#endif /* TESTCASE_TESTCASE_H_ */

