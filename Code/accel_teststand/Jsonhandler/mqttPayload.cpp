//
// Created by dani on 4/17/20.
//

#include "mqttPayload.h"

/**
 *
 */
mqttPayload::mqttPayload() {
    this->protocolVersion = 1.1f; //this is not a good solution
    this->suportedCmds.emplace_back(WebCommands::_RUN);
    this->suportedCmds.emplace_back(WebCommands::_STATUS);
    this->cmdsWithSettings.emplace_back(WebCommands::_RUN);

    this->supportedMsgTypes.emplace_back(WebMsgTypes::_COMMAND);
    this->supportedMsgTypes.emplace_back(WebMsgTypes::_STATUS);
    this->supportedMsgTypes.emplace_back(WebMsgTypes::_DATA);

    this->hasTestConfig = false;
}

/**
 *
 */
mqttPayload::~mqttPayload() {

}

/**
 *
 * @param test
 */
void mqttPayload::setTestConfig(testConfig test) {
    this->test = test;
    this->hasTestConfig = true;
}

/**
 *
 * @return
 */
testConfig mqttPayload::getTestConfig() {
    return this->test;
}

/**
 *
 * @param dataPoint
 */
void mqttPayload::addDataPoint(dataPoint dataPoint) {
    this->dataPoints.push_back(dataPoint);
}

/**
 *
 * @param dataPoints
 * @param size
 */
void mqttPayload::addDataPoints(dataPoint *dataPoints, int size) {
    for (int i = 0; i < size;i++){
        this->dataPoints.push_back(dataPoints[i]);
    }
}

/**
 *
 * @return
 */
std::vector<dataPoint> mqttPayload::getDataPoints() {
    return this->dataPoints;
}

/**
 *
 * @return
 */
std::string mqttPayload::getSentBy() {
    return this->sentBy;
}

/**
 *
 * @param sentBy
 */
void mqttPayload::setSentBy(std::string sentBy) {
    this->sentBy = sentBy;
}

/**
 *
 * @return
 */
float mqttPayload::getProtocolVersion() {
    return this->protocolVersion;
}

/**
 *
 * @param protocolVersion
 */
void mqttPayload::setProtocolVersion(float protocolVersion) {
    this->protocolVersion = protocolVersion;
}

/**
 *
 * @return
 */
std::string mqttPayload::getMsgType() {
    return this->msgType;
}

/**
 *
 * @param msgType
 */
void mqttPayload::setMsgType(std::string msgType) {
    this->msgType = msgType;
}

/**
 *
 * @return
 */
std::vector<std::string> mqttPayload::getCommandList() {
    return this->commandList;
}

/**
 *
 * @param command
 */
void mqttPayload::addCommand(std::string command) {
    this->commandList.push_back(command);
}

std::string mqttPayload::getStatusCode() {
    return this->statusCode;
}

/**
 *
 * @param statusCode
 */
void mqttPayload::setStatusCode(std::string statusCode) {
    this->statusCode = statusCode;
}

/**
 *
 * @param allocator
 * @return
 */
rapidjson::Value mqttPayload::toJson(
        rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) {
    rapidjson::Value jObj(rapidjson::kObjectType);
    rapidjson::Value val;

    //add protocolVersion
    val = this->protocolVersion;
    jObj.AddMember(_protocolVersion,val,allocator);
    //add sentBy
    val.SetString(this->sentBy.c_str(),this->sentBy.length());
    jObj.AddMember(_sentBy,val,allocator);
    //add msgType
    val.SetString(this->msgType.c_str(),this->msgType.length());
    jObj.AddMember(_msgType,val,allocator);
    //add statusCode
    val.SetString(this->statusCode.c_str(),this->statusCode.length());
    jObj.AddMember(_statusCode,val,allocator);
    //check if we have data from test.
    if(this->hasTestConfig){
        //add paramObj
        jObj.AddMember(_parameterObj,getTestConfig().toJson(allocator),allocator);
        //add dataObj
        rapidjson::Value dp(rapidjson::kArrayType);
        rapidjson::Value dataObj(rapidjson::kObjectType);
        //for(auto it = data.getDataPoints().begin();it != data.getDataPoints().end();++it)
        //above should work - if below does not
        for(auto & it : this->dataPoints){
            dp.PushBack(it.toJson(allocator),allocator);
        }
        dataObj.AddMember(_dataPoints, dp,allocator);
        jObj.AddMember(_dataObj,dataObj,allocator);
    }
    return jObj;
}

/**
 *
 * @param value
 * @param allocator
 */
void mqttPayload::toObject(const rapidjson::Value &value,
                           rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) {
    //validate protocolVersion first
    this->protocolVersion = value[_protocolVersion].GetFloat();
    if(this->protocolVersion != JSONProtocol::_VERSION){
        throw jsonValidationException("Wrong protocol version",JsonValidationErrors::_PROTOCOL_MISMATCH);
    }

    this->msgType =value[_msgType].GetString();
    //verify msgType
    if(!verifyMsgType()){
        throw jsonValidationException("msgType not found",JsonValidationErrors::_MSG_TYPE_NOT_FOUND);
    }
    this->sentBy = value[_sentBy].GetString();
    this->statusCode = value[_statusCode].GetString();

    //should always check for member commandList - not required field
    if(!value.HasMember(_commandList)){
        throw jsonValidationException("Missing member commandList",JsonValidationErrors::_MISSING_MEMBER);
    }
    const rapidjson::Value& cmdList = value[_commandList];
    //loop array
    for(rapidjson::Value::ConstValueIterator it = cmdList.Begin(); it != cmdList.End();++it){
        addCommand(it->GetString());
    }

    //verify commands
    if(!verifyCommands()){
        //commands are wrong
        throw jsonValidationException("Command not found",JsonValidationErrors::_COMMAND_NOT_FOUND);
    }

    //check if we require test parameters
    if(requiredSettings()){
        //should always check for member paramObj - not required field
        if(!value.HasMember(_parameterObj)){
            throw jsonValidationException("parameterObj is missing",JsonValidationErrors::_MISSING_MEMBER);
        }
        testConfig testConfig;
        const rapidjson::Value& paramObj = value[_parameterObj];
        testConfig.toObject(paramObj,allocator); //initialize from JSON
        this->test = testConfig; //set paramObj
        this->hasTestConfig = true; //tell it has testConfig
    }

    /**
     * THIS IS NOT NEEDED, WHAT AM I THINKING, WE ONLY SEND DATAPOINTS NOT RECIEVE THEM
     * CODE FOR WHEN WE WANNA GO JSON TO OBJECT FOR DATAPOINTS
    const rapidjson::Value& dataObj = doc[msg._dataObj.c_str()];
    //loop array
    for(rapidjson::Value::ConstValueIterator it = dataObj.Begin(); it != dataObj.End();++it){
        dataPoint reading;
        const rapidjson::Value& jRead = *it;
        if(!reading.toObject(jRead)){
            //error - error should be thrown inside
        }
        msg.addDataPoint(reading);
    }
     */

}

/**
 *
 * @return
 */
bool mqttPayload::verifyCommands() {
    //verify all commands
    int totalCommands = this->commandList.size();
    int validated = 0;
    for(auto & it_cl : this->commandList){
        //compare shit..
        for(auto & it_cr : this->suportedCmds){
            if(it_cl == it_cr){
                if(++validated == totalCommands){
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 *
 * @return
 */
bool mqttPayload::requiredSettings() {
    //based on commands- we might not required parameterObj
    for(auto & it_cl : this->commandList){
        //compare shit..
        for(auto & it_cr : this->cmdsWithSettings){
            if(it_cl == it_cr){
                return true;
            }
        }
    }
    return false;
}

/**
 *
 * @return
 */
bool mqttPayload::verifyMsgType() {
    for(auto & it : this->supportedMsgTypes){
        if(it == this->msgType){
            return true;
        }
    }
    return false;
}

/**
 *
 * @return
 */
bool mqttPayload::getHasTestConfig() {
    return this->hasTestConfig;
}

/**
 *
 * @param hasTestConfig
 */
void mqttPayload::setHasTestConfig(bool hasTestConfig) {
    this->hasTestConfig = hasTestConfig;
}



