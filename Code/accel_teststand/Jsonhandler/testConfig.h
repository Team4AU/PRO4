//
// Created by dani on 4/17/20.
//

#ifndef JSON_TESTCONFIG_H
#define JSON_TESTCONFIG_H
#include "jsonBase.h"
#include "dataPoint.h"
#include <vector>

class testConfig : public jsonBase {
public:
    testConfig();
    virtual ~testConfig();
    rapidjson::Value toJson(rapidjson::Document::AllocatorType& allocator) override;
    void toObject(const rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator) override;
    int getSensorID();
    void setSensorID(int sensorID);
    int getSensorType();
    void setSensorType(int sensorType);
    int getStartFrequency();
    void setStartFrequency(int startFrequency);
    int getStopFrequency();
    void setStopFrequency(int stopFrequency);
    int getStepFrequency();
    void setStepFrequency(int stepFrequency);
    int getStepTimeMs();
    void setStepTimeMs(int stepTimeMs);
private:
    int sensorID;
    int sensorType;
    int startFrequency;
    int stopFrequency;
    int stepFrequency;
    int stepTimeMs;
};


#endif //JSON_TESTCONFIG_H
