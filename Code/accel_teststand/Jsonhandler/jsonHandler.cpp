//
// Created by dani on 4/17/20.
//

#include "jsonHandler.h"
#include "rapidjson/prettywriter.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <rapidjson/schema.h>

/**
 *
 */
jsonHandler::jsonHandler() {

}

/**
 *
 */
jsonHandler::~jsonHandler() {

}

/**
 *
 * @param payload
 * @return
 */
std::string jsonHandler::payloadJsonMsg(mqttPayload payload) {
    //create json string
    rapidjson::Document doc;
    rapidjson::Value val;

    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    val = payload.toJson(allocator);
    doc.Swap(val);

    //make it a string - ready to send
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    writer.SetMaxDecimalPlaces(2);//change if we ever need more
    doc.Accept(writer);
    return buffer.GetString();
}

/**
 *
 * @param jsonString
 * @return
 */
mqttPayload jsonHandler::toMqttMessage(const std::string& jsonString) {
    rapidjson::Document doc;
    rapidjson::Document schemaDoc;

    //validate against SCHEMA
    if(schemaDoc.Parse(getSchema().c_str()).HasParseError()){
        //schema is not valid JSON
        throw jsonValidationException("JSON Schema is not valid JSON",JsonValidationErrors::_NOT_VALID_JSON);
    }

    rapidjson::SchemaDocument schema(schemaDoc);//schemaDoc can be deallocated

    //parse to DOM
    if(doc.Parse(jsonString.c_str()).HasParseError()){
        //error
        throw jsonValidationException("Parse error in document",JsonValidationErrors::_NOT_VALID_JSON);
    }

    rapidjson::SchemaValidator validator(schema);
    if(!doc.Accept(validator)){
        //validation error
        rapidjson::StringBuffer buffer;
        validator.GetInvalidSchemaPointer().StringifyUriFragment(buffer);
        std::stringstream errorMsg;

        errorMsg << "Invalid schema" << buffer.GetString() << std::endl <<
        "Invalid keyword: " << validator.GetInvalidSchemaKeyword() << std::endl;

        throw jsonValidationException(errorMsg.str(),JsonValidationErrors::_SCHEMA_ERROR);
    }

    //parse to object
    mqttPayload msg;
    msg.toObject(doc.GetObject(),doc.GetAllocator());
    return msg;
}

/**
 *
 * @param sentBy
 * @param statusCode
 * @param msgType
 * @return
 */
std::string jsonHandler::acknowledgeJsonMsg(std::string sentBy, std::string statusCode, std::string msgType) {
    //create json string

    mqttPayload payload;
    payload.setProtocolVersion(1.1);
    payload.setSentBy(std::move(sentBy));
    payload.setStatusCode(std::move(statusCode));
    payload.setMsgType(std::move(msgType));
    rapidjson::Document doc;
    rapidjson::Value val;

    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    val = payload.toJson(allocator);
    doc.Swap(val);

    //make it a string - ready to send
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    writer.SetMaxDecimalPlaces(2);//change if we ever need more
    doc.Accept(writer);
    return buffer.GetString();
}

/**
 *
 * @return
 */
std::string jsonHandler::getSchema() {
    //open file and get schema
    std::ifstream schemaFile;
    schemaFile.open(schemaFilePath);
    std::stringstream stringStream;
    stringStream << schemaFile.rdbuf(); //read file
    return stringStream.str();
}


