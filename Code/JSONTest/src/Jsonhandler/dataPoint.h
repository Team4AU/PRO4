//
// Created by dani on 4/17/20.
//

#ifndef JSON_DATAPOINT_H
#define JSON_DATAPOINT_H
#include "jsonBase.h"

class dataPoint : public jsonBase {
public:
    dataPoint(float x, float y, float z);
    dataPoint();
    virtual ~dataPoint();
    float getX();
    float getY();
    float getZ();
    rapidjson::Value toJson(rapidjson::Document::AllocatorType& allocator) override;
    void toObject(const rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator) override;
private:
    float x{};
    float y{};
    float z{};
};


#endif //JSON_DATAPOINT_H
