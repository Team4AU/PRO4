//
// Created by dani on 4/17/20.
//

#include <sstream>
#include "testConfig.h"

#define _sensorID "sensorID"
#define _sensorType "sensorType"
#define _startFrequency "startFrequency"
#define _stopFrequency "stopFrequency"
#define _stepFrequency "stepFrequency"
#define _stepTime "stepTime"

/**
 *
 */
testConfig::testConfig() {
    this->sensorID = -1;
    this->sensorType = -1;
    this->startFrequency = -1;
    this->stopFrequency = -1;
    this->stepFrequency = -1;
    this->stepTimeMs = -1;
}

/**
 *
 */
testConfig::~testConfig() {

}

/**
 *
 * @param allocator
 * @return
 */
rapidjson::Value testConfig::toJson(rapidjson::Document::AllocatorType& allocator) {
    rapidjson::Value jObj(rapidjson::kObjectType);
    rapidjson::Value val;

    val = this->sensorID;
    jObj.AddMember(_sensorID,val,allocator);

    val = this->sensorType;
    jObj.AddMember(_sensorType,val,allocator);

    val = this->startFrequency;
    jObj.AddMember(_startFrequency,val,allocator);

    val = this->stopFrequency;
    jObj.AddMember(_stopFrequency,val,allocator);

    val = this->stepFrequency;
    jObj.AddMember(_stepFrequency,val,allocator);

    val = this->stepTimeMs;
    jObj.AddMember(_stepTime,val,allocator);

    return jObj;
}

/**
 *
 * @param value
 * @param allocator
 */
void testConfig::toObject(const rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator) {
    //we have no schema for this object
    std::stringstream validationMsg;

    //check member sensorID
    if(!value.HasMember(_sensorID)){
        validationMsg << "Missing member: " << _sensorID << std::endl;
        throw jsonValidationException(validationMsg.str(),JsonValidationErrors::_MISSING_MEMBER);
    }
    if(!value[_sensorID].IsInt()){
        validationMsg << _sensorID << ": wrong datatype" << std::endl;
        throw jsonValidationException(validationMsg.str(),JsonValidationErrors::_NOT_INT);
    }
    this->sensorID = value[_sensorID].GetInt();

    //check member sensorType
    if(!value.HasMember(_sensorType)){
        validationMsg << "Missing member: " << _sensorType << std::endl;
        throw jsonValidationException(validationMsg.str(),JsonValidationErrors::_MISSING_MEMBER);
    }
    if(!value[_sensorType].IsInt()){
        validationMsg << _sensorType << ": wrong datatype" << std::endl;
        throw jsonValidationException(validationMsg.str(),JsonValidationErrors::_NOT_INT);
    }
    this->sensorType = value[_sensorType].GetInt();

    //check member startFrequency
    if(!value.HasMember(_startFrequency)){
        validationMsg << "Missing member: " << _startFrequency << std::endl;
        throw jsonValidationException(validationMsg.str(),JsonValidationErrors::_MISSING_MEMBER);
    }
    if(!value[_startFrequency].IsInt()){
        validationMsg << _startFrequency << ": wrong datatype" << std::endl;
        throw jsonValidationException(validationMsg.str(),JsonValidationErrors::_NOT_INT);
    }
    this->startFrequency = value[_startFrequency].GetInt();

    //check member stopFrequency
    if(!value.HasMember(_stopFrequency)){
        validationMsg << "Missing member: " << _stopFrequency << std::endl;
        throw jsonValidationException(validationMsg.str(),JsonValidationErrors::_MISSING_MEMBER);
    }
    if(!value[_stopFrequency].IsInt()){
        validationMsg << _stopFrequency << ": wrong datatype" << std::endl;
        throw jsonValidationException(validationMsg.str(),JsonValidationErrors::_NOT_INT);
    }
    this->stopFrequency = value[_stopFrequency].GetInt();

    //check member stepFrequency
    if(!value.HasMember(_stepFrequency)){
        validationMsg << "Missing member: " << _stepFrequency << std::endl;
        throw jsonValidationException(validationMsg.str(),JsonValidationErrors::_MISSING_MEMBER);
    }
    if(!value[_stepFrequency].IsInt()){
        validationMsg << _stepFrequency << ": wrong datatype" << std::endl;
        throw jsonValidationException(validationMsg.str(),JsonValidationErrors::_NOT_INT);
    }
    this->stepFrequency = value[_stepFrequency].GetInt();

    //check member stepTime
    if(!value.HasMember(_stepTime)){
        validationMsg << "Missing member: " << _stepTime << std::endl;
        throw jsonValidationException(validationMsg.str(),JsonValidationErrors::_MISSING_MEMBER);
    }
    if(!value[_stepTime].IsInt()){
        validationMsg << _stepTime << ": wrong datatype" << std::endl;
        throw jsonValidationException(validationMsg.str(),JsonValidationErrors::_NOT_INT);
    }
    this->stepTimeMs = value[_stepTime].GetInt();
}

/**
 *
 * @return
 */
int testConfig::getSensorID() {
    return this->sensorID;
}

/**
 *
 * @param sensorID
 */
void testConfig::setSensorID(int sensorID) {
    this->sensorID = sensorID;
}

/**
 *
 * @return
 */
int testConfig::getSensorType() {
    return this->sensorType;
}

/**
 *
 * @param sensorType
 */
void testConfig::setSensorType(int sensorType) {
    this->sensorType = sensorType;
}

/**
 *
 * @return
 */
int testConfig::getStartFrequency() {
    return this->startFrequency;
}

/**
 *
 * @param startFrequency
 */
void testConfig::setStartFrequency(int startFrequency) {
    this->startFrequency = startFrequency;
}

/**
 *
 * @return
 */
int testConfig::getStopFrequency() {
    return this->stopFrequency;
}

/**
 *
 * @param stopFrequency
 */
void testConfig::setStopFrequency(int stopFrequency) {
    this->stopFrequency = stopFrequency;
}

/**
 *
 * @return
 */
int testConfig::getStepFrequency() {
    return this->stepFrequency;
}

/**
 *
 * @param stepFrequency
 */
void testConfig::setStepFrequency(int stepFrequency) {
    this->stepFrequency = stepFrequency;
}

/**
 *
 * @return
 */
int testConfig::getStepTimeMs() {
    return this->stepTimeMs;
}

/**
 *
 * @param stepTimeMs
 */
void testConfig::setStepTimeMs(int stepTimeMs) {
    this->stepTimeMs = stepTimeMs;
}