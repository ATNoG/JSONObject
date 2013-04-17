#include "JSONObject.hpp"

#include <iostream>
#include <sstream>
#include <stack>

namespace json
{
    enum PARSE_STATE {BEGIN, ROOT, JSON,
    PRE_KEY, KEY, COLON, COMMA, VALUE,
    JSTRING, JARRAY, END, ERROR};
    
    /**
     * 
     */
    JSONValue::JSONValue(JSON_TYPE type)
    {
        vtype = type;
    }

    JSONValue::~JSONValue()
    {
    }

    /**
     * 
     */
    JSONValueNumber::JSONValueNumber(double value):JSONValue(NUMBER)
    {
        vvalue = value;
    }

    void JSONValueNumber::toString(std::string& toString)
    {
        std::stringstream ss;
        ss << vvalue;
        toString.append(ss.str());
    }

    JSONValue* JSONValueNumber::clone()
    {
        return new JSONValueNumber(vvalue);
    }

    JSONValueNumber::~JSONValueNumber()
    {
    }

    /**
     * 
     */
    JSONValueString::JSONValueString(const std::string& value):JSONValue(STRING)
    {
        vvalue = value;
    }

    void JSONValueString::toString(std::string& toString)
    {
        toString.append("\"");
        toString.append(vvalue);
        toString.append("\"");
    }

    JSONValue* JSONValueString::clone()
    {
        return new JSONValueString(vvalue);
    }

    JSONValueString::~JSONValueString()
    {
    }

    /**
     *
     */
    JSONValueBoolean::JSONValueBoolean(bool value):JSONValue(BOOLEAN)
    {
        vvalue = value;
    }

    void JSONValueBoolean::toString(std::string& toString)
    {
        if(vvalue)
            toString.append("true");
        else
            toString.append("false");
    }

    JSONValue* JSONValueBoolean::clone()
    {
        return new JSONValueBoolean(vvalue);
    }

    JSONValueBoolean::~JSONValueBoolean()
    {
    }

    /**
     *
     */

    JSONValueNULL::JSONValueNULL():JSONValue(JNULL)
    {
    }

    void JSONValueNULL::toString(std::string& toString)
    {
        toString.append("null");
    }

    JSONValue* JSONValueNULL::clone()
    {
        return new JSONValueNULL();
    }

    JSONValueNULL::~JSONValueNULL()
    {
    }
    
    /**
     * 
     */
    JSONValueArray::JSONValueArray():JSONValue(ARRAY)
    {
    }
    
    JSONValueArray::JSONValueArray(std::vector<JSONValue*>& array):JSONValue(ARRAY)
    {
        std::vector<JSONValue*>::iterator it = array.begin();
        for(; it != array.end(); ++it)
        {
            varray.push_back((*it)->clone());
        }
    }
    
    void JSONValueArray::put(JSONValue* value)
    {
        varray.push_back(value);
    }
    
    void JSONValueArray::toString(std::string& toString)
    {
        toString.append("[");
        std::vector<JSONValue*>::iterator it = varray.begin();
        for(; it != varray.end(); ++it)
        {
            (*it)->toString(toString);
            toString.append(",");
        }
        if(toString[toString.size()-1] == ',')
            toString[toString.size()-1] = ']';
        else
            toString.append("]");
    }
    JSONValue* JSONValueArray::clone()
    {
        JSONValueArray* rv = new JSONValueArray();
        std::vector<JSONValue*>::iterator it = varray.begin();
        for(; it != varray.end(); ++it)
        {
            rv->varray.push_back((*it)->clone());
        }
        return rv;
    }
    JSONValueArray::~JSONValueArray()
    {
        std::vector<JSONValue*>::iterator it = varray.begin();
        for(; it != varray.end(); ++it)
        {
            delete *it;
        }
        varray.clear();
    }
    
    /**
     * 
     */
    JSONObject::JSONObject():JSONValue(OBJECT)
    {
    }
    
    JSONObject::JSONObject(const std::string& str):JSONValue(OBJECT)
    {
        parse(str);
    }

    JSONObject::JSONObject(const JSONObject& obj):JSONValue(OBJECT)
    {
        map = obj.map;
    }

    void JSONObject::put(const std::string& key, double value)
    {
        map[key] = new JSONValueNumber(value);
    }

    void JSONObject::put(const std::string& key, std::string value)
    {
        map[key] = new JSONValueString(value);
    }

    void JSONObject::put(const std::string& key, bool value)
    {
        map[key] = new JSONValueBoolean(value);
    }

    void JSONObject::putNull(const std::string& key)
    {
        map[key] = new JSONValueNULL();
    }

    void JSONObject::put(const std::string& key, JSONValue& obj)
    {
        map[key] = obj.clone();
    }
    
    void JSONObject::put(const std::string& key, JSONValue* obj)
    {
        map[key] = obj;
    }
    
    void JSONObject::put(const std::string& key, JSONValueArray& array)
    {
        map[key] = array.clone();
    }
    
    void JSONObject::put(const std::string& key, std::vector<std::string>& array)
    {
        JSONValueArray* value = new JSONValueArray();
        std::vector<std::string>::iterator it = array.begin();
        for(; it != array.end(); ++it)
        {
            value->put(new JSONValueString((*it)));
        }
        map[key] = value;
    }

    void JSONObject::toString(std::string& toString)
    {
        toString.append("{");
        std::map<std::string, JSONValue*>::iterator it = map.begin();
        for(; it != map.end(); ++it)
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

    JSONValue* JSONObject::clone()
    {
        JSONObject* rv = new JSONObject();
        std::map<std::string, JSONValue*>::iterator it = map.begin();
        for(it=map.begin(); it != map.end(); ++it)
            rv->map[it->first] = it->second->clone();
        return rv;
    }
    
    JSONValue* JSONObject::factory(const std::string& str,
    size_t begin, size_t end)
    {
        JSONValue *rv = NULL;
        
        if(begin <= end)
        {
            std::string value = str.substr(begin, end-begin+1);
            if(value[0]=='"' && value[value.size()-1]=='"')
                rv = new JSONValueString(value.substr(1, value.size()-2));
            else if(value.find("null") != std::string::npos)
                rv = new JSONValueNULL();
            else if(value.find("true") != std::string::npos)
                rv = new JSONValueBoolean(true);
            else if(value.find("false") != std::string::npos)
                rv = new JSONValueBoolean(false);
            else
            {
                std::istringstream is(value);
                double number;
                if (is >> number)
                    rv = new JSONValueNumber(number);
            }
        }
        return rv;
    }
    
    void JSONObject::parse(const std::string& str)
    {
        size_t begin = 0, end = 0;
        std::string key;
        std::stack<PARSE_STATE> state;
        std::stack<JSONObject*> objects;
        std::stack<JSONValueArray*> arrays;
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
                            JSONValue *value = factory(str, begin, end);
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
                            JSONObject* obj = new JSONObject();
                            objects.top()->put(key, obj);
                            objects.push(obj);
                            state.pop();
                            state.push(JSON);
                            break;
                        }
                        case '}':
                        {
                            end = idx-1;
                            JSONValue *value = factory(str, begin, end);
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
                            JSONValueArray *array = new JSONValueArray();
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
                            JSONValue *value = factory(str, begin, end);
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
                            JSONValueArray *array = new JSONValueArray();
                            arrays.top()->put(array);
                            arrays.push(array);
                            state.push(JARRAY);
                            break;
                        }
                        case ']':
                        {
                            end = idx-1;
                            JSONValue *value = factory(str, begin, end);
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
                            JSONObject* obj = new JSONObject();
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
            std::map<std::string, JSONValue*>::iterator it = map.begin();
            for(it=map.begin(); it != map.end(); ++it)
            {
                delete it->second;
            }
            map.clear();
        }
    }

    JSONObject::~JSONObject()
    {
        std::map<std::string, JSONValue*>::iterator it = map.begin();
        for(it=map.begin(); it != map.end(); ++it)
        {
            delete it->second;
        }
        map.clear();
    }
}
