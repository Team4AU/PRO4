//
// Created by dani on 4/17/20.
//

#ifndef JSON_JSONBASE_H
#define JSON_JSONBASE_H

#include "rapidjson/document.h"
#include "jsonValidationException.h"

namespace JSONProtocol {
    static const float _VERSION = 1.1f; //consider expanding to a list...
}

namespace WebStatusCodes {
    //for more clarification check protocol documentation
    //Success
    static const std::string _200 = "200";
    static const std::string _202 = "202";
    //Error in request
    static const std::string _400 = "400";
    static const std::string _404 = "404";
    static const std::string _405 = "405";
    //Error teststand
    static const std::string _500 = "500";
    static const std::string _501 = "501"; // vi er FUCKING busy,
    //Power states
    static const std::string _600 = "600";
    static const std::string _610 = "610";
}

namespace WebMsgTypes {
    static const std::string _COMMAND = "command";
    static const std::string _STATUS = "status";
    static const std::string _DATA = "data";
}

namespace WebCommands {
    static const std::string _RUN = "run";
    static const std::string _STATUS = "status";
}

class jsonBase {
public:
    jsonBase() = default;
    virtual ~jsonBase() = default;
    virtual rapidjson::Value toJson(rapidjson::Document::AllocatorType& allocator) = 0;
    virtual void toObject(const rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator) = 0;
};


#endif //JSON_JSONBASE_H
