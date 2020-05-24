////////////////////////////////////////////////////////////
// Source file : SPI.cpp
// Author : Dani
// Date : 12-03-2020
// Version : 1.0
//
// Description :
//
////////////////////////////////////////////////////////////
#include "SPI.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

/**
 *
 * @param bus
 * @param device
 */
SPI::SPI(unsigned int bus, unsigned int device) :
    Bus(bus,device){
    std::stringstream filepath;
    filepath << SPI_PATH << bus << "." << device;
    this->filename = std::string(filepath.str());
    this->mode = 0; // default mode
    this->cpha = RISING_EDGE; //default
    this->cpol = LOGIC_LOW; // default
    this->bits = 8; // default bits
    this->speed = 1000000; // default speed
    this->delay = 0; // default delay
    this->open();
}

/**
 *
 */
SPI::~SPI() {
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
SPI::readRegisters(unsigned int length, unsigned int FromAddress) {
    unsigned char* data = new unsigned char[length];
    unsigned char send[length +1], receive[length +1];
    memset(send, 0, sizeof send);
    send[0] =  (unsigned char) (0x80 | 0x40 | FromAddress); //set read bit and MB bit
	if (this->transfer(send, receive, length + 1) == -1) {
		return data;
	}
    memcpy(data, receive+1, length);  //ignore the first (address) byte in the array returned
    return data;
}

/**
 *
 * @param registerAddress
 * @param value
 * @return
 */
int SPI::writeRegister(unsigned int registerAddress, unsigned char value) {
    unsigned char send[2], receive[2];
    memset(receive, 0, sizeof receive);
    send[0] = (unsigned char) registerAddress;
    send[1] = value;
    //cout << "The value that was written is: " << (int) send[1] << endl;
	if (this->transfer(send, receive, 2) == -1) {
		return -1;
	}
    return 0; // consider returning status of transfer
}

/**
 *
 * @return
 */
int SPI::open() {
    //cout << "Opening the file: " << filename.c_str() << endl;
    if ((this->file = ::open(filename.c_str(), O_RDWR))<0){
        perror("SPI: Can't open device.");
        return -1;
    }
    if (this->setMode(this->cpol,this->cpha)==-1){
        return -1;
    }
    if (this->setSpeed(this->speed)==-1){
        return -1;
    }
    if (this->setBitsPerWord(this->bits)==-1) {
        return -1;
    }
    return 0;
}

/**
 *
 */
void SPI::close() {
    ::close(this->file);
    this->file = -1;
}

/**
 *
 * @param speed
 * @return
 */
int SPI::setSpeed(uint32_t speed) {
    this->speed = speed;
    if (ioctl(this->file, SPI_IOC_WR_MAX_SPEED_HZ, &this->speed)==-1){
        perror("SPI: Can't set max speed HZ");
        return -1;
    }
    if (ioctl(this->file, SPI_IOC_RD_MAX_SPEED_HZ, &this->speed)==-1){
        perror("SPI: Can't get max speed HZ.");
        return -1;
    }
    return 0;
}

/**
 *
 * @param cpol
 * @param cpha
 * @return
 */
int SPI::setMode(SPI::CPOL cpol, SPI::CPHA cpha) {
    //Must handle it accordingly
    if(cpol == LOGIC_LOW && cpha == RISING_EDGE){
        this->mode = 0;
    }else if(cpol == LOGIC_LOW && cpha == FALLING_EDGE){
        this->mode = 1;
    }else if(cpol == LOGIC_HIGH && cpha == FALLING_EDGE){
        this->mode = 2;
    }else{
        this->mode = 3;
    }
    if (ioctl(this->file, SPI_IOC_WR_MODE, &this->mode)==-1){
        perror("SPI: Can't set SPI mode.");
        return -1;
    }
    if (ioctl(this->file, SPI_IOC_RD_MODE, &this->mode)==-1){
        perror("SPI: Can't get SPI mode.");
        return -1;
    }
    return 0;
}

/**
 *
 * @param bits
 * @return
 */
int SPI::setBitsPerWord(uint8_t bits) {
    this->bits = bits;
    if (ioctl(this->file, SPI_IOC_WR_BITS_PER_WORD, &this->bits)==-1){
        perror("SPI: Can't set bits per word.");
        return -1;
    }
    if (ioctl(this->file, SPI_IOC_RD_BITS_PER_WORD, &this->bits)==-1){
        perror("SPI: Can't get bits per word.");
        return -1;
    }
    return 0;
}

/**
 *
 * @param rx
 * @param tx
 * @param length
 * @return
 */
int SPI::transfer(unsigned char *rx, unsigned char *tx, int length) {
    struct spi_ioc_transfer	transfer;
    memset(&transfer,0,sizeof(transfer));
    transfer.tx_buf = (unsigned long) tx;
    transfer.rx_buf = (unsigned long) rx;
    transfer.len = length;
    transfer.speed_hz = this->speed;
    transfer.bits_per_word = this->bits;
    transfer.delay_usecs = this->delay;

 //   transfer.tx_nbits = 0;        // no. bits for writing (default 0)
 //   transfer.rx_nbits = 0;        // no. bits for reading (default 0)
    transfer.cs_change = 0;       // affects chip select after transfe
    transfer.pad = 0;             // interbyte delay
    int status = ioctl(this->file, SPI_IOC_MESSAGE(1), &transfer);
    if (status < 0) {
        perror("SPI: SPI_IOC_MESSAGE Failed");
        return -1;
    }
    return status;
}
