////////////////////////////////////////////////////////////
// Source file : Bus.h
// Author : Dani
// Date : 12-03-2020
// Version : 1.0
//
// Description :
//
////////////////////////////////////////////////////////////
#ifndef V2_ROCKET_BUS_H
#define V2_ROCKET_BUS_H


class Bus {
protected:
    unsigned int bus;
    unsigned int deviceId;
    int file;
public:
     Bus(unsigned int bus, unsigned int deviceId);
    virtual ~Bus();
    virtual unsigned char * readRegisters(unsigned int length, unsigned int FromAddress) = 0;
    virtual int writeRegister(unsigned int registerAddress, unsigned char value) = 0;
    virtual int open() = 0;
    virtual void close() = 0;
};


#endif //V2_ROCKET_BUS_H
