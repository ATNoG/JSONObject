/**
 * @file JValue.cpp
 * @class JValue
 * @author Mario Antunes (mariolpantunes@gmail.com)
 * @version 2.0
 * @date October, 2013
 *
 * JValue class
 *
 */

#include "JSONObject.hpp"

namespace json
{
    JValue::JValue(JSON_TYPE type)
    {
        _type = type;
    }

    bool JValue::isBooleanValue() const
    {
        bool rv = false;
        if(this->_type == BOOLEAN)
            rv = true;
        return rv;
    }

    bool JValue::isNumberValue() const
    {
        bool rv = false;
        if(this->_type == NUMBER)
            rv = true;
        return rv;
    }

    bool JValue::isStringValue() const
    {
        bool rv = false;
        if(this->_type == STRING)
            rv = true;
        return rv;
    }

    bool JValue::isObjectValue() const
    {
        bool rv = false;
        if(this->_type == OBJECT)
            rv = true;
        return rv;
    }

    bool JValue::isArrayValue() const
    {
        bool rv = false;
        if(this->_type == ARRAY)
            rv = true;
        return rv;
    }

    bool JValue::isNullValue() const
    {
        bool rv = false;
        if(this->_type == JNULL)
            rv = true;
        return rv;
    }

    JValue::~JValue()
    {
    }
}
