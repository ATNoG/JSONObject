/**
 * @file JNumber.cpp
 * @class JNumber
 * @author Mario Antunes (mariolpantunes@gmail.com)
 * @version 2.0
 * @date October, 2013
 *
 * JNumber class
 *
 */

#include "JSONObject.hpp"

namespace json
{
    JNumber::JNumber(double value):JValue(NUMBER)
    {
        _value = value;
    }

    JNumber::JNumber(const JNumber& value):JValue(NUMBER)
    {
        _value = value._value;
    }

    void JNumber::toString(std::string& toString) const
    {
        std::stringstream ss;
        ss << _value;
        toString.append(ss.str());
    }

    JValue* JNumber::clone() const
    {
        return new JNumber(_value);
    }
    
    void JNumber::value(double& value)
    {
        value = _value;
    }

    JNumber::~JNumber()
    {
    }
}
