//
// Created by dani on 4/17/20.
//

#ifndef JSON_JSONVALIDATIONEXCEPTION_H
#define JSON_JSONVALIDATIONEXCEPTION_H
#include <exception>
#include <stdexcept>
#include <string>

namespace JsonValidationErrors {
    //Datatype errors 2xxx
    static const int _NOT_OBJECT = 2001;
    static const int _NOT_ARRAY = 2002;
    static const int _NOT_STRING = 2003;
    static const int _NOT_INT = 2004;
    static const int _NOT_DOUBLE = 2006;
    static const int _NOT_FLOAT = 2007;
    static const int _NOT_UINT = 2008;

    //missing member 3xxx
    static const int _MISSING_MEMBER = 3000;

    //Parse errors 4xxx
    static const int _NOT_VALID_JSON = 4001;
    static const int _SCHEMA_ERROR = 4002;

    //Document errors 5xxx
    static const int _PROTOCOL_MISMATCH = 5001;
    static const int _COMMAND_NOT_FOUND = 5002;
    static const int _MSG_TYPE_NOT_FOUND = 5003;
}

class jsonValidationException : public std::runtime_error {
protected:
    int errorNumber;
public:
    explicit jsonValidationException(const std::string& msg, int errNum);
    ~jsonValidationException() noexcept override;
    virtual int getErrorNumber() const noexcept;
};


#endif //JSON_JSONVALIDATIONEXCEPTION_H
