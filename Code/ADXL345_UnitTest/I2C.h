////////////////////////////////////////////////////////////
//
// Source file	: I2C.h
// Author				: Nikolaj
// Date 				: 3 Dec 2019
// Version 			: 1.1
//
// Description  : a I2C basedriver for BBB
//
////////////////////////////////////////////////////////////
#ifndef I2C_H_
#define I2C_H_

// includes
#include<iostream>
#include<sstream>
#include<fcntl.h>
#include<stdio.h>
#include<iomanip>
#include<unistd.h>
#include<sys/ioctl.h>
#include<linux/i2c.h>
#include<linux/i2c-dev.h>

// defines
#define BBB_I2C_0 "/dev/i2c-0"
#define BBB_I2C_1 "/dev/i2c-1"
#define BBB_I2C_2 "/dev/i2c-2"

using namespace std;

/**
 * @breif Generic I2C Driver to be used with I2C devices. I/O from registers
 * @class I2C
 *
 */
class I2C
{
	public:
		I2C(unsigned int bus, unsigned int address);
		virtual ~I2C ( );
		virtual unsigned char * readRegisters(unsigned int length, unsigned int FromAddress);
		virtual int writeRegister(unsigned int registerAddress, unsigned char value);
		virtual int open();
		virtual void close();

	private:
		unsigned int address;
		unsigned int bus;
		int file;
};

#endif /* I2C_H_ */
