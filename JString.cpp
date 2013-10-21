/**
 * @file JString.cpp
 * @class JString
 * @author Mario Antunes (mariolpantunes@gmail.com)
 * @version 2.0
 * @date October, 2013
 *
 * JString class
 *
 */

#include "JObject.hpp"

namespace json
{
    JString::JString(const std::string& value):JValue(STRING)
    {
        _value = value;
    }

    JString::JString(const JString& value):JValue(STRING)
    {
        _value = value._value;
    }

    void JString::toString(std::string& toString) const
    {
        toString.append("\"");
        toString.append(_value);
        toString.append("\"");
    }

    JValue* JString::clone() const
    {
        return new JString(_value);
    }
    
    void JString::value(std::string& value)
    {
        value = _value;
    }

    JString::~JString()
    {
    }
}
