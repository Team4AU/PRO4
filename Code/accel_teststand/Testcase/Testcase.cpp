////////////////////////////////////////////////////////////
//
// Source file	: Testcase.cpp
// Author				: Nikolaj
// Date 				: 9 Apr 2020
// Version 			:
//
// Description : standard return if not implementet -1000
//
////////////////////////////////////////////////////////////
#include "Testcase.h"

Testcase::Testcase ( )
{

	this->sensorID = -1;
	this->sensorType = -1;
	this->startFrequency = -1;
	this->stopFrequency = -1;
	this->stepFrequency = -1;
	this->stepTimeMs = -1;

}

Testcase::~Testcase ( )
{

}

Testcase::Testcase (int sensorID_,
					int sensorType_,
                    int startFrequency_,
                    int stopFrequency_,
                    int stepFrequency_,
                    int stepTimeMs_)
{
	this->sensorID = sensorID_;
	this->sensorType = sensorType_;
	this->startFrequency = startFrequency_;
	this->stopFrequency = stopFrequency_;
	this->stepFrequency = stepFrequency_;
	this->stepTimeMs = stepTimeMs_;
}

int Testcase::startTestcase ( )
{
	int code;
	if (sensorID == adxl345 && sensorType == i2c)	//ADXL345 I2C
	{
		I2C i2c (BUSADXL345, ADXL345I2C);
		ADXL345 adxl345 (&i2c);
		adxl345.setBWrate (ADXL345::BANDWITH_800_Hz);
		PWM pwm (BBB);
		if ((code = (this->initpwm (pwm))) != 0)
		{
			return code;
		}
		if (!pwm.startPWM ())
		{
			return TestStatusCodes::_514;
		}
		if (adxl345.ReadSensorState (this->dataP,SAMPLES_I2C_ADXL) != 0)
		{
			return TestStatusCodes::_520;
		}
		if (!pwm.stopPWM ())
		{
			return TestStatusCodes::_515;
		}

	}
	else if (sensorID == adxl345 && sensorType == spi) 	//ADXL345 SPI
	{
		SPI spi (BUSADXL345, ADXL345SPI);
		ADXL345 adxl345 (&spi);	//default bandwith is 1600 Hz
		PWM pwm (BBB);

		if ((code = (this->initpwm (pwm))) != 0)
		{
			return code;
		}
		if (!pwm.startPWM ())
		{
			return TestStatusCodes::_514;
		}
		if (adxl345.ReadSensorState (this->dataP,SAMPLES_SPI_ADXL) != 0)
		{
			return TestStatusCodes::_520;
		}
		if (!pwm.stopPWM ())
		{
			return TestStatusCodes::_515;
		}

	}
	else if (sensorID == kx224 && sensorType == i2c)		//KX224 I2C
	{
		I2C i2c (BUSKX224, KX224I2C);
		KX224 kx224 (&i2c);
		PWM pwm (BBB);
		kx224.setBWrate(KX224::BANDWIDTH_800_Hz);
		if ((code = (this->initpwm (pwm))) != 0)
		{
			return code;
		}
		if (!pwm.startPWM ())
		{
			return TestStatusCodes::_514;
		}
		if (kx224.ReadSensorState (this->dataP,SAMPLES_I2C_KX224) != 0)
		{
			return TestStatusCodes::_520;
		}
		if (!pwm.stopPWM ())
		{
			return TestStatusCodes::_515;
		}

	}
	else if (sensorID == kx224 && sensorType == spi)		//KX224 SPI
	{
		return -1000; // not implemented (spi not connected on dev-board)
		SPI spi (BUSKX224, KX224SPI);
		KX224 kx224 (&spi);
		PWM pwm (BBB);
		if ((code = (this->initpwm (pwm))) != 0)
		{
			return code;
		}
		if (!pwm.startPWM ())
		{
			return TestStatusCodes::_514;
		}
		if (kx224.ReadSensorState (this->dataP,SAMPLES_SPI_KX224) != 0)
		{
			return TestStatusCodes::_520;
		}
		if (!pwm.stopPWM ())
		{
			return TestStatusCodes::_515;
		}
	}
	else
	{
		return -404; //sensor not found;
	}

	return 0;
}

int Testcase::initpwm (PWM pwm)
{
	if (!pwm.init ())
	{
		return TestStatusCodes::_511;
	}
	if (this->stopFrequency == ONEFREQ)
	{
		pwm.setup (startFrequency, DUTY);
	}
	else if (this->stopFrequency  != ONEFREQ)
	{
		return TestStatusCodes::_555; // not implemented yet
		pwm.runSweep (startFrequency, stopFrequency, stepFrequency);
	}
	else {
		return TestStatusCodes::_512; //wrong setup
	}

	return 0;
}


