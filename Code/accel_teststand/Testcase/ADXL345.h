////////////////////////////////////////////////////////////
//
// Source file	: ADXL345.h
// Author				: Nikolaj
// Date 				: 4 Dec 2019
// Version 			:
//
// Description : adxl345 driver
//
////////////////////////////////////////////////////////////
#ifndef ADXL345_H_
#define ADXL345_H_

//includes
#include <fstream>
#include"I2C.h"
#include "ISensor.h"
#include <string.h>
#include "Bus.h"

/**
 * @breif ADXL345 driver, to setup adxl345 sensor, inherance from I2Cdriver
 * @class ADXL345
 *
 */

class ADXL345 : public ISensor
{
public:
	// An enumeration to define the gravity range of the sensor
	enum RANGE {
		PLUSMINUS_2_G = 0,// plus/minus 2g
		PLUSMINUS_4_G = 1,// plus/minus 4g
		PLUSMINUS_8_G = 2,// plus/minus 8g
		PLUSMINUS_16_G = 3 // plus/minus 16g
	};
	// The resolution of the sensor. High is only available in +/- 16g range.
	enum RESOLUTION {
		NORMAL = 0,//!< NORMAL 10-bit resolution
		HIGH = 1   //!< HIGH 13-bit resolution
	};
	// an enumeration to define Baud bandwich and output rate.
	enum BAUD {
		BANDWITH_3f125_Hz = 6,	// BW 3.125 Hz Outputrate 2*BW Hz
		BANDWITH_6f25_Hz = 7,	// BW 6.25 Hz Outputrate 2*BW Hz
		BANDWITH_12f5_Hz = 8,	// BW 12.5 Hz Outputrate 2*BW Hz
		BANDWITH_25_Hz = 9,	// BW 25 Hz Outputrate 2*BW Hz
		BANDWITH_50_Hz = 10,	// BW 50 Hz Outputrate 2*BW Hz
		BANDWITH_100_Hz = 11,	// BW 100 Hz Outputrate 2*BW Hz
		BANDWITH_200_Hz = 12,	// BW 200 Hz Outputrate 2*BW Hz
		BANDWITH_400_Hz = 13,	// BW 400 Hz Outputrate 2*BW Hz
		BANDWITH_800_Hz = 14,	// BW 800 Hz Outputrate 2*BW Hz
		BANDWITH_1600_Hz = 15	// BW 1600 Hz Outputrate 2*BW Hz
	};

	ADXL345(Bus *busType);
	int setRange(ADXL345::RANGE range);
	int setResolution(ADXL345::RESOLUTION resolution);
	int setBWrate(ADXL345::BAUD baud);
	int updateRegisters();
	virtual ~ADXL345();
	ADXL345::RANGE getRange() { return this->range; };
	ADXL345::RESOLUTION getResolution() { return this->resolution; };
	ADXL345::BAUD getBaud() { return this->baud; };
	short getaccelX() { return this->accelX; };
	short getaccelY() { return this->accelY; };
	short getaccelZ() { return this->accelZ; };
	int WriteDataToFile(short x, short y, short z) override;
	int WriteDataToFile(ostream os, short x, short y, short z);
	int OpenOutFile() override;
	int CloseOutFile() override;
	int ReadSensorStateToFile(int samples) override;
    int ReadSensorState(dataPoint * data, int samples) override;

private:
    Bus *busType;
	short combineRegisters(unsigned char msb, unsigned char lsb);
	short accelX, accelY, accelZ;
	unsigned char * registers;
	ADXL345::RANGE range;
	ADXL345::RESOLUTION resolution;
	ADXL345::BAUD baud;
	ofstream outFile;
	unsigned char * olddata;





};

#endif /* ADXL345_H_ */
