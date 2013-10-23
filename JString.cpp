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

#include "JSONObject.hpp"
#include "StringUtils.hpp"

namespace json
{
    JString::JString(const std::string& value):JValue(STRING)
    {
        _value = unescapeJSON(value);
    }

    JString::JString(const JString& value):JValue(STRING)
    {
        _value = value._value;
    }

    void JString::toString(std::string& toString) const
    {
        toString.append("\"");
        toString.append(escapeJSON(_value));
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

    std::string JString::value()
    {
        return std::string(_value);
    }

    JString::~JString()
    {
    }
}
