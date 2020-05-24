#pragma once
#include "../Jsonhandler/dataPoint.h"

class ISensor {
public:
	virtual ~ISensor() {};
	virtual int WriteDataToFile(short x, short y, short z) = 0;
	virtual int OpenOutFile() = 0;
	virtual int CloseOutFile() = 0;
	virtual int ReadSensorStateToFile(int samples) = 0;
	virtual int ReadSensorState(dataPoint * data, int samples) = 0;
};
