////////////////////////////////////////////////////////////
// Source file : Bus.cpp
// Author : Dani
// Date : 12-03-2020
// Version : 1.0
//
// Description :
//
////////////////////////////////////////////////////////////
#include "Bus.h"

Bus::Bus(unsigned int bus, unsigned int deviceId)
{
    this->bus = bus;
    this->deviceId = deviceId;
    this->file = -1;
}

Bus::~Bus() {}

