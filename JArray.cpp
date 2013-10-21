/**
 * @file JArray.cpp
 * @class JArray
 * @author Mario Antunes (mariolpantunes@gmail.com)
 * @version 2.0
 * @date October, 2013
 *
 * JArray class
 *
 */

#include "JObject.hpp"

namespace json
{
    JArray::JArray():JValue(ARRAY)
    {
    }

    JArray::JArray(const std::vector<std::string>& array):JValue(ARRAY)
    {
        size_t i = 0;

        for(; i < array.size()/8; i=i+8)
        {
            _array.push_back(new JString(array[i]));
            _array.push_back(new JString(array[i+1]));
            _array.push_back(new JString(array[i+2]));
            _array.push_back(new JString(array[i+3]));
            _array.push_back(new JString(array[i+4]));
            _array.push_back(new JString(array[i+5]));
            _array.push_back(new JString(array[i+6]));
            _array.push_back(new JString(array[i+7]));
        }

        for(; i < array.size(); ++i)
            _array.push_back(new JString(array[i]));
    }

    JArray::JArray(const std::vector<double>& array):JValue(ARRAY)
    {
        size_t i = 0;

        for(; i < array.size()/8; i=i+8)
        {
            _array.push_back(new JNumber(array[i]));
            _array.push_back(new JNumber(array[i+1]));
            _array.push_back(new JNumber(array[i+2]));
            _array.push_back(new JNumber(array[i+3]));
            _array.push_back(new JNumber(array[i+4]));
            _array.push_back(new JNumber(array[i+5]));
            _array.push_back(new JNumber(array[i+6]));
            _array.push_back(new JNumber(array[i+7]));
        }

        for(; i < array.size(); ++i)
            _array.push_back(new JNumber(array[i]));
    }


    JArray::JArray(const std::vector<int>& array):JValue(ARRAY)
    {
        size_t i = 0;

        for(; i < array.size()/8; i=i+8)
        {
            _array.push_back(new JNumber(array[i]));
            _array.push_back(new JNumber(array[i+1]));
            _array.push_back(new JNumber(array[i+2]));
            _array.push_back(new JNumber(array[i+3]));
            _array.push_back(new JNumber(array[i+4]));
            _array.push_back(new JNumber(array[i+5]));
            _array.push_back(new JNumber(array[i+6]));
            _array.push_back(new JNumber(array[i+7]));
        }

        for(; i < array.size(); ++i)
            _array.push_back(new JNumber(array[i]));
    }

    JArray::JArray(const std::vector<bool>& array):JValue(ARRAY)
    {
        size_t i = 0;

        for(; i < array.size()/8; i=i+8)
        {
            _array.push_back(new JBoolean(array[i]));
            _array.push_back(new JBoolean(array[i+1]));
            _array.push_back(new JBoolean(array[i+2]));
            _array.push_back(new JBoolean(array[i+3]));
            _array.push_back(new JBoolean(array[i+4]));
            _array.push_back(new JBoolean(array[i+5]));
            _array.push_back(new JBoolean(array[i+6]));
            _array.push_back(new JBoolean(array[i+7]));
        }

        for(; i < array.size(); ++i)
            _array.push_back(new JBoolean(array[i]));
    }

    JArray::JArray(const std::vector<JValue*>& array):JValue(ARRAY)
    {
        std::vector<JValue*>::const_iterator it = array.begin();
        for(; it != array.end(); ++it)
            _array.push_back((*it)->clone());
    }

    void JArray::put(JValue* value)
    {
        _array.push_back(value);
    }

    void JArray::toString(std::string& toString) const
    {
        toString.append("[");
        std::vector<JValue*>::const_iterator it = _array.begin();
        for(; it != _array.end(); ++it)
        {
            (*it)->toString(toString);
            toString.append(",");
        }
        if(toString[toString.size()-1] == ',')
            toString[toString.size()-1] = ']';
        else
            toString.append("]");
    }

    JValue* JArray::clone() const
    {
        JArray *value = new JArray();
        
        std::vector<JValue*>::const_iterator it = _array.begin();
        for(; it != _array.end(); ++it)
            value->_array.push_back((*it)->clone());
        
        return value;
    }

    JArray::~JArray()
    {
        std::vector<JValue*>::iterator it = _array.begin();
        for(; it != _array.end(); ++it)
            delete *it;
        _array.clear();
    }
}
