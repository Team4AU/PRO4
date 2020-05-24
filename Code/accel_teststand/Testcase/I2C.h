////////////////////////////////////////////////////////////
// Source file : I2C.h
// Author : Dani
// Date : 12-03-2020
// Version : 1.0
//
// Description :
//
////////////////////////////////////////////////////////////
#ifndef V2_ROCKET_I2C_H
#define V2_ROCKET_I2C_H

// includes
#include<iostream>
#include<sstream>
#include<fcntl.h>
#include<cstdio>
#include<iomanip>
#include<unistd.h>
#include<sys/ioctl.h>
#include<linux/i2c.h>
#include<linux/i2c-dev.h>
#include "Bus.h"

// defines
#define BBB_I2C_0 "/dev/i2c-0"
#define BBB_I2C_1 "/dev/i2c-1"
#define BBB_I2C_2 "/dev/i2c-2"

using namespace std;

class I2C : public Bus {
public:
    I2C(unsigned int bus, unsigned int address);
    virtual ~I2C ( );
    unsigned char * readRegisters(unsigned int length, unsigned int FromAddress) override;
    int writeRegister(unsigned int registerAddress, unsigned char value) override;
    int open() override;
    void close() override;
};


#endif //V2_ROCKET_I2C_H
