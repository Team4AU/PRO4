////////////////////////////////////////////////////////////
// Source file : SPI.h
// Author : Dani
// Date : 12-03-2020
// Version : 1.0
//
// Description :
//
////////////////////////////////////////////////////////////
#ifndef V2_ROCKET_SPI_H
#define V2_ROCKET_SPI_H

#include<stdint.h>
#include <string>
#include "Bus.h"

//defines
#define SPI_PATH "/dev/spidev"


class SPI : public Bus {
public:
    enum CPOL{
        LOGIC_LOW = 0,
        LOGIC_HIGH = 1
    };
    enum CPHA{
        RISING_EDGE = 0,
        FALLING_EDGE = 1
    };

private:
    std::string filename;
public:
    SPI(unsigned int bus, unsigned int device);
    ~SPI();
    unsigned char * readRegisters(unsigned int length, unsigned int FromAddress) override;
    int writeRegister(unsigned int registerAddress, unsigned char value) override;
    int open() override;
    void close() override;
    int setSpeed(uint32_t speed);
    int setMode(SPI::CPOL cpol, SPI::CPHA cpha);
    int setBitsPerWord(uint8_t bits);
    int transfer(unsigned char rx[], unsigned char tx[], int length);
private:
    CPOL cpol;
    CPHA cpha;
    int mode;
    uint8_t bits;
    uint32_t  speed;
    uint16_t  delay;
};


#endif //V2_ROCKET_SPI_H
