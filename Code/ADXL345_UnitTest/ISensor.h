#pragma once
class ISensor {
public:
	virtual ~ISensor() {};
	virtual int WriteDataToFile(short x, short y, short z) = 0;
	virtual int OpenOutFile() = 0;
	virtual int CloseOutFile() = 0;
	virtual int ReadSensorState(int samples) = 0;
};