////////////////////////////////////////////////////////////
// Source file : I2C.cpp
// Author : Dani
// Date : 12-03-2020
// Version : 1.0
//
// Description :
//
////////////////////////////////////////////////////////////
#include "I2C.h"

/**
 *
 * @param bus
 * @param address
 */
I2C::I2C(unsigned int bus, unsigned int address):
    Bus(bus,address){
    this->deviceId = address;
    this->bus = bus;
    this->file = -1;
    this->open();
}

/**
 *
 */
I2C::~I2C() {
    if(this->file!=-1){
        this->close();
    }
}

/**
 *
 * @param length
 * @param FromAddress
 * @return
 */
unsigned char *
I2C::readRegisters(unsigned int length, unsigned int FromAddress) {
    unsigned buffer[1];
    buffer[0] = FromAddress;
    if(::write(this->file,buffer,1) != 1) {
        perror("I2C: Failed write to the device\n");
        return nullptr;
    }
    auto * data = new unsigned char[length];
    if(::read(this->file, data, length)!=(int)length){
        perror("IC2: Failed to read in the full buffer.\n");
        return nullptr;
    }
    return data;
}

/**
 *
 * @param registerAddress
 * @param value
 * @return
 */
int I2C::writeRegister(unsigned int registerAddress, unsigned char value) {
    unsigned char buffer[2];
    buffer[0] = registerAddress;
    buffer[1] = value;
    if(::write(this->file, buffer, 2)!=2){
        perror("I2C: Failed write to the device\n");
        return -1;
    }
    return 0;
}

/**
 *
 * @return
 */
int I2C::open() {
    string I2Cname;
    if(this->bus == 0) {
        I2Cname = BBB_I2C_0;
    }
    else if(this->bus == 1) {
        I2Cname = BBB_I2C_1;
    }
    else if(this->bus == 2) {
        I2Cname = BBB_I2C_2;
    }
    if((this->file=::open(I2Cname.c_str(), O_RDWR)) < 0){
        perror("I2C: failed to open the bus\n");
        return -1;
    }
    if(ioctl(this->file, I2C_SLAVE, this->deviceId) < 0){
        perror("I2C: Failed to connect to the address\n");
        return -1;
    }
    return 0;
}

/**
 *
 */
void I2C::close() {
    ::close(this->file);
    this->file = -1;
}
