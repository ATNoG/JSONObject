/**
 * @file JBoolean.cpp
 * @class JBoolean
 * @author Mario Antunes (mariolpantunes@gmail.com)
 * @version 2.0
 * @date October, 2013
 *
 * JBoolean class
 *
 */

#include "JSONObject.hpp"

#include <iostream>

namespace json
{
    JBoolean::JBoolean(bool value):JValue(BOOLEAN)
    {
        _value = value;
    }

    JBoolean::JBoolean(const JBoolean& value):JValue(BOOLEAN)
    {
        _value = value._value;
    }

    void JBoolean::toString(std::string& toString) const
    {
        if(_value)
            toString.append("true");
        else
            toString.append("false");
    }

    JValue* JBoolean::clone() const
    {
        return new JBoolean(_value);
    }
    
    void JBoolean::value(bool& value) const
    {
        value = _value;
    }

    JBoolean::~JBoolean()
    {
    }
}
