//
// Created by dani on 4/17/20.
//

#ifndef JSON_MQTTPAYLOAD_H
#define JSON_MQTTPAYLOAD_H


#include "jsonBase.h"
#include "testConfig.h"

#define _protocolVersion "protocolVersion"
#define _sentBy "sentBy"
#define _msgType "msgType"
#define _statusCode "statusCode"
#define _parameterObj "parameterObj"
#define _dataObj "dataObj"
#define _dataPoints "dataPoints"
#define _commandList "commandList"

class mqttPayload : public jsonBase{
public:
    mqttPayload();
    virtual ~mqttPayload();
    rapidjson::Value toJson(rapidjson::Document::AllocatorType& allocator) override;
    void toObject(const rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator) override;
    void setTestConfig(testConfig test);
    testConfig getTestConfig();
    std::vector<dataPoint> getDataPoints();
    void addDataPoint(dataPoint dataPoint);
    void addDataPoints(dataPoint *dataPoints, int size);
    std::string getSentBy();
    void setSentBy(std::string sentBy);
    float getProtocolVersion();
    void setProtocolVersion(float protocolVersion);
    std::string getMsgType();
    void setMsgType(std::string msgType);
    std::vector<std::string> getCommandList();
    void addCommand(std::string command);
    std::string getStatusCode();
    void setStatusCode(std::string statusCode);
    bool getHasTestConfig();
    void setHasTestConfig(bool hasTestConfig);
private:
    bool verifyCommands();
    bool requiredSettings();
    bool verifyMsgType();
    bool hasTestConfig;
    std::vector<dataPoint> dataPoints;
    testConfig test;
    std::string sentBy;
    float protocolVersion;
    std::string msgType;
    std::vector<std::string> commandList;
    std::string statusCode;
    std::vector<std::string> suportedCmds;
    std::vector<std::string> cmdsWithSettings;
    std::vector<std::string> supportedMsgTypes;
};


#endif //JSON_MQTTPAYLOAD_H
