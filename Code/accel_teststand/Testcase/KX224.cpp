////////////////////////////////////////////////////////////
// Source file : KX224.cpp
// Author : Dani
// Date : 12-03-2020
// Version : 1.0
//
// Description :
//
////////////////////////////////////////////////////////////
#include "KX224.h"

//defines
#define BUFFER_SIZE 0x6

#define XHPL 0x00 // X-axis high pass filter accelerometer output LSB
#define XHPH 0x01 // X-axis high pass filter accelerometer output MSB
#define YHPL 0x02 // Y-axis high pass filter accelerometer output LSB
#define YHPH 0x03 // Y-axis high pass filter accelerometer output MSB
#define ZHPL 0x04 // Z-axis high pass filter accelerometer output LSB
#define ZHPH 0x05 // Z-axis high pass filter accelerometer output MSB
#define XOUTL 0x06 // X-axis accelerometer output LSB
#define XOUTH 0x07 // X-axis accelerometer output MSB
#define YOUTL 0x08 // Y-axis accelerometer output LSB
#define YOUTH 0x09 // Y-axis accelerometer output MSB
#define ZOUTL 0x0A // Z-axis accelerometer output LSB
#define ZOUTH 0x0B // Z-axis accelerometer output MSB
#define COTR 0x0C //
#define WHO_AM_I 0x0F // default value is 0x2B
#define TSCP 0x10 // current titlt position
#define TSPP 0x11 // previous tilt position
#define INS 0x12 //indicates tap/double tap
#define INS2 0x13 // which function caused an interrupt
#define INS3 0x14 // axis and direction detected
#define STAT 0x15 //status of interrupt
#define INT_REL 0x17 // latched interrupt source information
#define CNTL1 0x18 // controls main feature set
#define CNTL2 0x19 //provides more feature set control
#define CNTL3 0x1A // output data rates for tilt, directional tap and motion wake up digital engines
#define ODCNTL 0x1B // ODR = output data rate
#define INC1 0x1C // physical intterupt pin INT1
#define INC2 0x1D // axis and direction of detected motion interrupt
#define INC3 0x1E // axis and direction of tap/double tap interrupt
#define INC4 0x1F // routing of an interrupt reporting to physical interrupt on pin INT1
#define INC5 0x20 // physical interrupt pint INT2
#define INC6 0x21 // routing of an interupt reporting to physical interrupt in pin INT2
#define TILT_TIMER 0x22 // tilt positon state timer
#define WUFC 0x23 // initial count for motion detection timer
#define TDTRC 0x24 // enable/disable reporting of tap/double tap
#define TDTC 0x25 // counter information for dection pf double tap event
#define TTH 0x26 // high threshold to determine if a tap is detected
#define TTL 0x27  // low threshold to determine if a tap is detected
#define FTD 0x28 // counter information of any tap event
#define STD 0x29 // counter informatino of double tap event
#define TLT 0x2A // counter information of tap event
#define TWS 0x2B // counter information of single and double taps
#define FFTH 0x2C // free fall threshold
#define FFC 0x2D // counter for free fall detection
#define FFCNTL 0x2E //free fall control
#define ATH 0x30 // wake up motion detect
#define TILT_ANGLE_L 0x32 // low threshold angle detection
#define TILT_ANGLE_H 0x33 // high threshold angle detection
#define HYST_SET 0x34 // hysteresis
#define LP_CNTL 0x35 // averaging filter control
#define BUF_CNTL1 0x3A // buffer sample threshold
#define BUF_CNTL2 0x3B // sample buffer operation
#define BUF_STATUS_1 0x3C // sample buffer status
#define BUF_STATUS_2 0x3D // sample buffer trigger function
#define BUF_CLEAR 0x3E // clear sample buffer
#define BUF_READ 0x3F // buffer output
#define SELF_TEST 0x60 // when 0xCA is written the MEMS self-test function is enabled 0x00 sets to normal operation
#define OUT_FILE       "kx224.txt"     //Output file
#define VENDOR_ADDR 0x1E //default address of KX224

/**
 *
 * @param busType
 */
KX224::KX224(Bus *busType) {
    this->busType = busType;
    this->accelX = 0;
    this->accelY = 0;
    this->accelZ = 0;
    this->operatingMode = 0;
    this->registers = NULL;
    this->range = KX224::PLUSMINUS_16_G;
    this->resolution = KX224::HIGH;
    this->baud = KX224::BANDWIDTH_12800_Hz;
    this->olddata = NULL;

    this->setPC1(STANDBY);

    this->busType->writeRegister(ODCNTL, 0x0f);//no filter, 12800 bandwidth

    this->setPC1(OPERATING);
}

/**
 *
 * @param range
 * @return
 */
int KX224::setRange(KX224::KX224_RANGE range) {
    if(this->setPC1(STANDBY) == 1){
        perror("KX224: Failed write Range to register\n");
        return 1;
    }

    this->range = range;

    if(this->setPC1(OPERATING) == 1){
        perror("KX224: Failed write Range to register\n");
        return 1;
    }
    return 0;
}

/**
 *
 * @param resolution
 * @return
 */
int KX224::setResolution(KX224::KX224_RESOLUTION resolution) {
    if(this->setPC1(STANDBY)==1){
        perror("KX224: Failed write Resolution to register\n");
        return 1;
    }
    this->resolution = resolution;
    if(this->setPC1(OPERATING)==1){
        perror("KX224: Failed write Resolution to register\n");
        return 1;
    }
    return 0;
}

/**
 *
 * @param baud
 * @return
 */
int KX224::setBWrate(KX224::KX224_BAUD baud) {
    if(this->setPC1(STANDBY)==1){
        perror("KX224: Failed write BW rate to register\n");
        return 1;
    }

    char data_format = 0x00;  // no filter 12.5 hz outputrate
    // 0-3 LSB output date rate
    data_format = data_format | baud;


    if (this->busType->writeRegister(ODCNTL, data_format) == 1) {
        perror("KX224: Failed write Baud rate to register\n");
        return 1;
    }

    this->baud = baud;

    if(this->setPC1(OPERATING)==1){
        perror("KX224: Failed write BW rate to register\n");
        return 1;
    }

    return 0;
}

/**
 * @deprecated
 * @return
 */
int KX224::updateRegisters() {
    return 0;
}

/**
 *
 */
KX224::~KX224() {

}

/**
 *
 * @param x
 * @param y
 * @param z
 * @return
 */
int KX224::WriteDataToFile(short x, short y, short z) {
    //write line to output file
    //check if bad bit is set. this bit is only set when there is
    //an actual write error, not guaranteed to happen before an actual
    // write is performed.
    if (this->outFile) {
        this->outFile << x << "," << y << "," << z << endl;
    }
    if (this->outFile.bad()) {
        return 1;
    }
    return 0;
}

/**
 *
 * @param os
 * @param x
 * @param y
 * @param z
 * @return
 */
int KX224::WriteDataToFile(ostream &os, short x, short y, short z) {
//function for testing write funcktion - boost variant
    if (os) {
        os << x << "," << y << "," << z << endl;
    }
    if (os.bad()) {
        return 1;
    }
    return 0;
}

/**
 *
 * @return
 */
int KX224::OpenOutFile() {
    //open output file
    this->outFile.open(OUT_FILE, ios::out | ios::trunc);
    if (!this->outFile.is_open()) {
        return 1;
    }

    //write header for file
    this->outFile << "x,y,z\n" << endl;
    return 0;
}

/**
 *
 * @return
 */
int KX224::CloseOutFile() {
    //close output file
    //flush buffer before file is closed
    //check for bad bit before closing.
    this->outFile.flush();
    if (this->outFile.bad()) {
        this->outFile.close();
        return 1;
    }
    this->outFile.close();
    return 0;
}

/**
 *
 * @param samples
 * @return
 */
int KX224::ReadSensorStateToFile(int samples) {
	//open file here..
	if (OpenOutFile()) {
		perror("KX224: Failed open file");
		return -1;
	}

	for (int i = 0; i < samples;i++) {
		this->registers = this->busType->readRegisters(BUFFER_SIZE, XOUTL);
		if (this->registers == NULL) {
			perror("KX224: Failure Condition - Sensor ID not Verified");
			return -1;
		}
		//checks if data is the same as before. Registers start at the first data register
		if ((memcmp (olddata, registers + XOUTL, BUFFER_SIZE)) == 0) {
			i--;
		}
		else {

	    this->accelX = this->combineRegisters(*(registers + 1), *(registers + 0));
	    this->accelY = this->combineRegisters(*(registers + 3), *(registers + 2));
	    this->accelZ = this->combineRegisters(*(registers + 5), *(registers + 4));

		if (WriteDataToFile(this->accelX, this->accelY, this->accelZ)) {
			perror("ADXL345: Failed write X, Y & Z to file");
			return -1;
		}
		//sets new data to old data. Register starts at first data register
		memcpy(olddata,registers+XOUTL,BUFFER_SIZE);
		}
	}
	if (CloseOutFile()) {
		perror("ADXL345: Failed close out file");
		return 1;
	}
	return 0;
}

/**
 * @brief Reads sensor state, by reading register 0x6-0x11
 * @return -1 on failure and 1 on success
 */
int KX224::readSensorData() {
    this->registers = this->busType->readRegisters(BUFFER_SIZE, XOUTL);

    if(this->registers == NULL){
        perror("KX224: Failure Condition - Sensor ID not Verified");
        return -1;
    }

    this->accelX = this->combineRegisters(*(registers + 1), *(registers + 0));
    this->accelY = this->combineRegisters(*(registers + 3), *(registers + 2));
    this->accelZ = this->combineRegisters(*(registers + 5), *(registers + 4));

    return 0;
}

/**
 * @brief Reads sensor state, by reading register 0x6-0x11 continuously N times
 * @param data array of dataPoints
 * @param samples number of readings
 * @return -1 on failure and 1 on success
 */
int KX224::ReadSensorState(dataPoint * data, int samples) {
    for (int i = 0; i < samples;i++) {
        this->registers = this->busType->readRegisters(BUFFER_SIZE, XOUTL);
        if (this->registers == NULL) {
            perror("KX224: Failure Condition - Sensor ID not Verified");
            return -1;
        }
        //checks if data is the same as before. Registers start at the first data register
        if ((memcmp (olddata, registers + XOUTL, BUFFER_SIZE)) == 0) {
            i--;
        }
        else {

            this->accelX = this->combineRegisters(*(registers + 1), *(registers + 0));
            this->accelY = this->combineRegisters(*(registers + 3), *(registers + 2));
            this->accelZ = this->combineRegisters(*(registers + 5), *(registers + 4));

            dataPoint dp(this->accelX,this->accelY,this->accelZ);
            data[i] = dp;
            //sets new data to old data. Register starts at first data register
            memcpy(olddata,registers+XOUTL,BUFFER_SIZE);
        }
    }
    return 0;
}

/**
 *
 * @param msb
 * @param lsb
 * @return
 */
short KX224::combineRegisters(unsigned char msb, unsigned char lsb) {
    //shift the MSB left by 8 bits and OR with LSB
    return ((short)msb << 8) | (short)lsb;
}

/**
 *
 * @param operation
 * @return
 */
int KX224::setPC1(KX224::KX224_OPERATION operation) {
    unsigned char data_format = 0x00;
    //Full_resolution is the 7th LSB
    data_format = data_format | ((this->resolution) << 7);
    data_format = data_format | (this->range << 5); // 5th and 6th LSB
    data_format = data_format | (operation << 8); //0
    return this->busType->writeRegister(CNTL1, data_format);
}
