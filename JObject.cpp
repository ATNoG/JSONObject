/**
 * @file JObject.cpp
 * @class JObject
 * @author Mario Antunes (mariolpantunes@gmail.com)
 * @version 2.0
 * @date October, 2013
 *
 * JObject class
 *
 */

#include "JObject.hpp"

#include <iostream>
#include <sstream>
#include <stack>

namespace json
{
    enum PARSE_STATE {BEGIN, ROOT, JSON,
        PRE_KEY, KEY, COLON, COMMA, VALUE,
        JSTRING, JARRAY, END, ERROR};

    JObject::JObject():JValue(OBJECT)
    {
    }

    JObject::JObject(const std::string& str):JValue(OBJECT)
    {
        parse(str);
    }

    JObject::JObject(const JObject& obj):JValue(OBJECT)
    {
        std::map<std::string, JValue*>::const_iterator it = obj._map.begin();
        for(; it != obj._map.end(); ++it)
            _map[it->first] = it->second->clone();
    }

    void JObject::get(const std::string& key, JValue* &value)
    {
        JValue* _value = _map[key];

        if(_value != NULL)
            value = _value;
        else
            value = NULL;
    }

    void JObject::getBoolean(const std::string& key, bool &value)
    {
        JValue* _value = _map[key];

        if(_value != NULL && _value->isBooleanValue())
            ((JBoolean*)_value)->value(value);
    }

    void JObject::getDouble(const std::string& key, double &value)
    {
        JValue* _value = _map[key];

        if(_value != NULL && _value->isNumberValue())
            ((JNumber*)_value)->value(value);
    }

    void JObject::getInt(const std::string& key, int &value)
    {
        JValue* _value = _map[key];

        if(_value != NULL && _value->isNumberValue())
        {
            double temp = 0.0;
            ((JNumber*)_value)->value(temp);
            value = (int) temp;
        }
    }

    void JObject::getString(const std::string& key, std::string& value)
    {
        JValue* _value = _map[key];

        if(_value != NULL && _value->isStringValue())
            ((JString*)_value)->value(value);
    }

    void JObject::getJArray(const std::string& key, JArray &value)
    {
        JValue* _value = _map[key];

        if(_value != NULL && _value->isArrayValue())
            value = *((JArray*)_value);
    }

    void JObject::getJObject(const std::string& key, JObject &value) const
    {
        JValue* _value = _map.at(key);

        if(_value != NULL && _value->isObjectValue())
            value = *((JObject*)_value);
    }

    void JObject::put(const std::string& key, double value)
    {
        this->remove(key);
        _map[key] = new JNumber(value);
    }

    void JObject::put(const std::string& key, std::string value)
    {
        this->remove(key);
        _map[key] = new JString(value);
    }

    void JObject::put(const std::string& key, const char* value)
    {
        std::string strValue(value);
        this->put(key, strValue);
    }

    void JObject::put(const std::string& key, bool value)
    {
        this->remove(key);
        _map[key] = new JBoolean(value);
    }

    void JObject::putNull(const std::string& key)
    {
        this->remove(key);
        _map[key] = new JNull();
    }

    void JObject::put(const std::string& key, const JValue& obj)
    {
        this->remove(key);
        _map[key] = obj.clone();
    }

    void JObject::put(const std::string& key, JValue* obj)
    {
        this->remove(key);
        _map[key] = obj;
    }

    void JObject::put(const std::string& key, const JArray& array)
    {
        this->remove(key);
        _map[key] = array.clone();
    }

    void JObject::put(const std::string& key, const std::vector<std::string>& array)
    {
        this->remove(key);
        JArray* value = new JArray(array);
        _map[key] = value;
    }

    void JObject::put(const std::string& key, const std::vector<int>& array)
    {
        this->remove(key);
        JArray* value = new JArray(array);
        _map[key] = value;
    }

    bool JObject::exists(const std::string& key) const
    {
        bool rv = false;
        if(_map.count(key) > 0)
            rv = true;
        return rv;
    }

    void JObject::remove(const std::string& key)
    {
        if(this->exists(key))
        {
            JValue* value = _map[key];
            delete value;
            _map.erase(key);
        }
    }

    void JObject::clear()
    {
        std::map<std::string, JValue*>::iterator it = _map.begin();
        for(; it != _map.end(); ++it)
            delete it->second;
        _map.clear();
    }

    void JObject::toString(std::string& toString) const
    {
        toString.append("{");
        std::map<std::string, JValue*>::const_iterator it = _map.begin();
        for(; it != _map.end(); ++it)
        {
            toString.append("\"");
            toString.append(it->first);
            toString.append("\":");
            it->second->toString(toString);
            toString.append(",");
        }
        if(toString[toString.size()-1] == ',')
            toString[toString.size()-1] = '}';
        else
            toString.append("}");
    }

    JValue* JObject::clone() const
    {
        JObject* value = new JObject();

        std::map<std::string, JValue*>::const_iterator it = _map.begin();
        for(; it != _map.end(); ++it)
            value->_map[it->first] = it->second->clone(); 
        
        return value;
    }

    JObject& JObject::operator=(const JObject& obj)
    {
        if(this != &obj)
        {
            this->clear();
            std::map<std::string, JValue*>::const_iterator it = obj._map.begin();
            for(; it != obj._map.end(); ++it)
                this->_map[it->first] = it->second->clone();
        } 

        return *this;
    }

    JObject::~JObject()
    {
        this->clear();
    }

    JValue* JObject::factory(const std::string& str, size_t begin, size_t end)
    {
        JValue *rv = NULL;
        if(begin <= end)
        {
            std::string value = str.substr(begin, end-begin+1);
            if(value[0]=='"' && value[value.size()-1]=='"')
                rv = new JString(value.substr(1, value.size()-2));
            else if(value.find("null") != std::string::npos)
                rv = new JNull();
            else if(value.find("true") != std::string::npos)
                rv = new JBoolean(true);
            else if(value.find("false") != std::string::npos)
                rv = new JBoolean(false);
            else
            {
                std::istringstream is(value);
                double number;
                if (is >> number)
                    rv = new JNumber(number);
            }
        }
        return rv;
    }

    void JObject::parse(const std::string& str)
    {
        size_t begin = 0, end = 0;
        std::string key;
        std::stack<PARSE_STATE> state;
        std::stack<JObject*> objects;
        std::stack<JArray*> arrays;
        state.push(BEGIN);

        std::cout<<str<<std::endl;        
        for(size_t idx = 0; idx < str.size() && state.top() != ERROR; idx++)
        {
            switch(state.top())
            {
                case BEGIN:
                    switch(str[idx])
                    {
                        case '{':
                            state.pop();
                            state.push(END);
                            state.push(ROOT);
                            objects.push(this);
                            break;
                    }
                    break;
                case ROOT:
                    switch(str[idx])
                    {
                        case '"':
                            begin = idx+1;
                            state.push(KEY);
                            break;
                        case '}':
                            objects.pop();
                            state.pop();
                            break;
                    }
                    break;
                case JSON:
                    switch(str[idx])
                    {
                        case '"':
                            begin = idx+1;
                            state.push(KEY);
                            break;
                        case '}':
                            objects.pop();
                            state.pop();
                            state.push(COMMA);
                            break;
                    }
                    break;
                case PRE_KEY:
                    switch(str[idx])
                    {
                        case '"':
                            begin = idx+1;
                            state.pop();
                            state.push(KEY);
                            break;
                    }
                    break;
                case KEY:
                    switch(str[idx])
                    {
                        case '"':
                            end = idx-1;
                            key = str.substr(begin, end-begin+1);
                            state.pop();
                            state.push(COLON);
                            break;
                    }
                    break;
                case COLON:
                    switch(str[idx])
                    {
                        case ':':
                            begin = idx+1;
                            state.pop();
                            state.push(VALUE);
                            break;
                    }
                    break;
                case VALUE:
                    switch(str[idx])
                    {
                        case '"':
                            begin = idx;
                            state.pop();
                            state.push(JSTRING);
                            break;
                        case ',':
                            {
                                end = idx-1;
                                JValue *value = factory(str, begin, end);
                                if(value != NULL)
                                {
                                    objects.top()->put(key, value);
                                    state.pop();
                                }
                                else
                                    state.push(ERROR);
                                break;
                            }
                        case '{':
                            {
                                JObject* obj = new JObject();
                                objects.top()->put(key, obj);
                                objects.push(obj);
                                state.pop();
                                state.push(JSON);
                                break;
                            }
                        case '}':
                            {
                                end = idx-1;
                                JValue *value = factory(str, begin, end);
                                if(value != NULL)
                                {
                                    objects.top()->put(key, value);
                                    objects.pop();
                                    state.pop();
                                    state.pop();
                                    if(state.top() == JSON || state.top() == JARRAY)
                                        state.push(COMMA);
                                    else if(state.top() == ROOT)
                                        state.pop();
                                }
                                else
                                    state.push(ERROR);
                                break;
                            }
                        case '[':
                            {
                                begin = idx+1;
                                JArray *array = new JArray();
                                objects.top()->put(key, array);
                                arrays.push(array);
                                state.pop();
                                state.push(JARRAY);
                                break;
                            }
                    }
                    break;
                case JSTRING:
                    switch(str[idx])
                    {
                        case '"':
                            {
                                end = idx;
                                JValue *value = factory(str, begin, end);
                                if(value != NULL)
                                {
                                    objects.top()->put(key, value);
                                    state.pop();
                                    state.push(COMMA);
                                }
                                else
                                    state.push(ERROR);
                            }
                            break;
                    }
                    break;
                case COMMA:
                    switch(str[idx])
                    {
                        case ',':
                            {
                                state.pop();
                                begin = idx+1;
                                if(state.top() == ROOT || state.top() == JSON)
                                    state.push(PRE_KEY);
                                break;
                            }
                        case '}':
                            state.pop();
                            if(state.top() == JSON)
                            {
                                objects.pop();
                                state.pop();
                                state.push(COMMA);
                            }
                            else if(state.top() == ROOT)
                            {
                                objects.pop();
                                state.pop();
                            }
                            break;
                        case ']':
                            state.pop();
                            if(state.top() == JARRAY)
                            {
                                arrays.pop();
                                state.pop();
                                state.push(COMMA);
                            }
                            break;
                    }
                    break;
                case JARRAY:
                    switch(str[idx])
                    {
                        case '"':
                            begin = idx;
                            state.push(JSTRING);
                            break;
                        case '[':
                            {
                                begin = idx+1;
                                JArray *array = new JArray();
                                arrays.top()->put(array);
                                arrays.push(array);
                                state.push(JARRAY);
                                break;
                            }
                        case ']':
                            {
                                end = idx-1;
                                JValue *value = factory(str, begin, end);
                                if(value != NULL)
                                {
                                    arrays.top()->put(value);
                                    arrays.pop();
                                    state.pop();
                                    state.push(COMMA);
                                }
                                else
                                    state.push(ERROR);
                                break;
                            }
                        case ',':
                            end = idx-1;
                            arrays.top()->put(factory(str, begin, end));
                            begin = idx+1;
                            break;
                        case '{':
                            {
                                JObject* obj = new JObject();
                                arrays.top()->put(obj);
                                objects.push(obj);
                                state.push(JSON);
                                break;
                            }
                    }
                    break;
                case END:
                    break;
                case ERROR:
                    break;
            }
        }

        if(state.top() != END)
        {
            this->clear();
        }
    }
}
