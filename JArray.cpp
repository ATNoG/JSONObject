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

#include "JSONObject.hpp"

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

        for(; i < array.size()/8; i = i+8)
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

        for(; i < array.size()/8; i = i+8)
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
        size_t i = 0;

        for(; i < array.size()/8; i = i+8)
        {
            _array.push_back(array[i]->clone());
            _array.push_back(array[i+1]->clone());
            _array.push_back(array[i+2]->clone());
            _array.push_back(array[i+3]->clone());
            _array.push_back(array[i+4]->clone());
            _array.push_back(array[i+5]->clone());
            _array.push_back(array[i+6]->clone());
            _array.push_back(array[i+7]->clone());
        }
        
        for(; i < array.size(); ++i)
            _array.push_back(array[i]->clone());
    }


    void JArray::get(const size_t idx, JValue* &value) const
    {
        value = _array.at(idx);
    }

    void JArray::get(const size_t idx, bool &value) const 
    {
        JValue* _value = _array.at(idx);

        if(_value != NULL && _value->isBooleanValue())
            ((JBoolean*)_value)->value(value);
    }

    void JArray::get(const size_t idx, double &value) const
    {
        JValue* _value = _array.at(idx);

        if(_value != NULL && _value->isNumberValue())
            ((JNumber*)_value)->value(value);
    }

    void JArray::get(const size_t idx, int &value) const
    {
        JValue* _value = _array.at(idx);

        if(_value != NULL && _value->isNumberValue())
        {
            double temp = 0.0;
            ((JNumber*)_value)->value(temp);
            value = (int) temp;
        }
    }

    void JArray::get(const size_t idx, size_t &value) const
    {
        JValue* _value = _array.at(idx);

        if(_value != NULL && _value->isNumberValue())
        {
            double temp = 0.0;
            ((JNumber*)_value)->value(temp);
            value = (size_t) temp;
        }
    }

    void JArray::get(const size_t idx, std::string& value) const
    {
        JValue* _value = _array.at(idx);

        if(_value != NULL && _value->isStringValue())
            ((JString*)_value)->value(value);
    }

    
    void JArray::get(const size_t idx, JArray &value) const
    {
        JValue* _value = _array.at(idx);

        if(_value != NULL && _value->isArrayValue())
            value = *((JArray*)_value);
    }


    void JArray::put(const size_t idx, JValue* &value)
    {
        JValue* _value = _array.at(idx);

        if(_value != NULL)
            delete _value;

        _array[idx] = value;
    }
    
    void JArray::put(const size_t idx, const std::string value)
    {
        JValue* _value = _array.at(idx);

        if(_value != NULL)
            delete _value;

        _array[idx] = new JString(value);
    }
    
    void JArray::put(const size_t idx, const char* value)
    {
        JValue* _value = _array.at(idx);

        if(_value != NULL)
            delete _value;

        _array[idx] = new JString(value);
    }

    void JArray::put(const size_t idx, const double value)
    {
        JValue* _value = _array.at(idx);

        if(_value != NULL)
            delete _value;

        _array[idx] = new JNumber(value);
    }

    void JArray::put(const size_t idx, const int value)
    {
        JValue* _value = _array.at(idx);

        if(_value != NULL)
            delete _value;

        _array[idx] = new JNumber(value);
    }

    void JArray::put(const size_t idx, const bool value)
    {
        JValue* _value = _array.at(idx);

        if(_value != NULL)
            delete _value;

        _array[idx] = new JBoolean(value);
    }

    void JArray::put(const size_t idx, const JArray& value)
    {
        JValue* _value = _array.at(idx);

        if(_value != NULL)
            delete _value;

        _array[idx] = value.clone();
    }

    void JArray::put(JValue* value)
    {
        _array.push_back(value);
    }

    JValue*& JArray::at(size_t i)
    {
        return _array.at(i);
    }

    size_t JArray::size() const
    {
        return _array.size();
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
