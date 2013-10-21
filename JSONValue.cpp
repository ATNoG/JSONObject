/**
 * @file JSONValue.cpp
 * @class JSONValue
 * @author Mario Antunes (mariolpantunes@gmail.com)
 * @version 2.0
 * @date October, 2013
 *
 * JSONValue class
 *
 */

#include "JObject.hpp"

namespace json
{
    JSONValue::JSONValue(JSON_TYPE type)
    {
        vtype = type;
    }
    
    bool JSONValue::isBooleanValue() const
    {
        bool rv = false;
        if(this->vtype == BOOLEAN)
            rv = true;
        return rv;
    }
    
    bool JSONValue::isNumberValue() const
    {
        bool rv = false;
        if(this->vtype == NUMBER)
            rv = true;
        return rv;
    }
    
    bool JSONValue::isStringValue() const
    {
        bool rv = false;
        if(this->vtype == STRING)
            rv = true;
        return rv;
    }
    
    bool JSONValue::isObjectValue() const
    {
        bool rv = false;
        if(this->vtype == OBJECT)
            rv = true;
        return rv;
    }
    
    bool JSONValue::isArrayValue() const
    {
        bool rv = false;
        if(this->vtype == ARRAY)
            rv = true;
        return rv;
    }
    
    bool JSONValue::isNullValue() const
    {
        bool rv = false;
        if(this->vtype == JNULL)
            rv = true;
        return rv;
    }

    JSONValue::~JSONValue()
    {
    }
}
