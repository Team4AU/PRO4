////////////////////////////////////////////////////////////
// Source file : KX224.h
// Author : Dani
// Date : 12-03-2020
// Version : 1.0
//
// Description :
//
////////////////////////////////////////////////////////////
#ifndef V2_ROCKET_KX224_H
#define V2_ROCKET_KX224_H

#include <fstream>
#include <string.h>
#include "I2C.h"
#include "SPI.h"
#include "Bus.h"
#include "ISensor.h"


class KX224 : public ISensor {
public:
    // An enumeration to define the gravity range of the sensor
    enum KX224_RANGE {
        PLUSMINUS_8_G = 0,// plus/minus 8g
        PLUSMINUS_16_G = 1, // plus/minus 16g
        PLUSMINUS_32_G = 3 // plus/minus 32
    };
    // The resolution of the sensor. High is only available in +/- 16g range.
    enum KX224_RESOLUTION {
        LOWCURRENT = 0,//!< 8-bit resolution
        HIGH = 1   //!< HIGH 16-bit resolution
    };
    //an enumeration to define operating mode
    enum KX224_OPERATION {
        STANDBY = 0,
        OPERATING = 1
    };
    // an enumeration to define Baud bandwich and output rate.
    enum KX224_BAUD {
        BANDWIDTH_6f25_Hz = 0,	// BW 12.5 Hz Outputrate 2*BW Hz
        BANDWIDTH_12f5_Hz = 1,	// BW 25 Hz Outputrate 2*BW Hz
        BANDWIDTH_25_Hz = 2,	// BW 50 Hz Outputrate 2*BW Hz
        BANDWIDTH_50_Hz = 3,	// BW 100 Hz Outputrate 2*BW Hz
        BANDWIDTH_100_Hz = 4,	// BW 200 Hz Outputrate 2*BW Hz
        BANDWIDTH_200_Hz = 5,	// BW 400 Hz Outputrate 2*BW Hz
        BANDWIDTH_400_Hz = 6,	// BW 800 Hz Outputrate 2*BW Hz
        BANDWIDTH_800_Hz = 7,	// BW 1600 Hz Outputrate 2*BW Hz
        BANDWIDTH_0f39_Hz = 8,	// BW 0.781 Hz Outputrate 2*BW Hz
        BANDWIDTH_0f78_Hz = 9,	// BW 1.563 Hz Outputrate 2*BW Hz
        BANDWIDTH_1f56_Hz = 10,	// BW 3.125 Hz Outputrate 2*BW Hz
        BANDWIDTH_3f125_Hz = 11,	// BW 6.25 Hz Outputrate 2*BW Hz
        BANDWIDTH_1600_Hz = 12,	// BW 3200 Hz Outputrate 2*BW Hz
        BANDWIDTH_3200_Hz = 13,	// BW 6400 Hz Outputrate 2*BW Hz
        BANDWIDTH_6400_Hz = 14,	// BW 12800 Hz Outputrate 2*BW Hz
        BANDWIDTH_12800_Hz = 15	// BW 25600 Hz Outputrate 2*BW Hz
    };
    KX224(Bus *busType);
    int setRange(KX224::KX224_RANGE range);
    int setResolution(KX224::KX224_RESOLUTION resolution);
    int setBWrate(KX224::KX224_BAUD baud);
    int updateRegisters();
    virtual ~KX224();
    KX224::KX224_RANGE getRange() { return this->range; };
    KX224::KX224_RESOLUTION getResolution() { return this->resolution; };
    KX224::KX224_BAUD getBaud() { return this->baud; };
    short getaccelX() { return this->accelX; };
    short getaccelY() { return this->accelY; };
    short getaccelZ() { return this->accelZ; };
    int WriteDataToFile(short x, short y, short z) override;
    int WriteDataToFile(ostream& os, short x, short y, short z);
    int OpenOutFile() override;
    int CloseOutFile() override;
    int ReadSensorStateToFile(int samples) override;
    int ReadSensorState(dataPoint * data, int samples) override;
    int readSensorData();
private:
    Bus *busType;
    short combineRegisters(unsigned char msb, unsigned char lsb);
    int setPC1(KX224::KX224_OPERATION operation);
    short accelX, accelY, accelZ;
    unsigned char * registers;
    unsigned int operatingMode;
    KX224::KX224_RANGE range;
    KX224::KX224_RESOLUTION resolution;
    KX224::KX224_BAUD baud;
    ofstream outFile;
    unsigned char * olddata;
};


#endif //V2_ROCKET_KX224_H
