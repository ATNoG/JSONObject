/**
 * @file    JSONObject.hpp
 * @class   JSONObject
 * @author  Mario Antunes (mariolpantunes@gmail.com)
 * @version 2.0
 * @date    January, 2013
 *
 * JSONObject is a easy to use JSON wrapper for boost property tree.
 * Based on the API of Java org.JSON library (http://www.json.org/java/index.html).
 */

#ifndef _JSON_OBJECT_H_
#define _JSON_OBJECT_H_

#include <string>
#include <sstream>
#include <vector>
#include <map>

namespace json
{
    enum JSON_TYPE {NUMBER, STRING, OBJECT, BOOLEAN, ARRAY, JNULL};
    
    class JSONValue
    {
        public:
            JSONValue(JSON_TYPE type);
            virtual void toString(std::string& toString)=0;
            virtual JSONValue* clone()=0;
            bool isBooleanValue() const;
            bool isNumberValue() const;
            bool isStringValue() const;
            bool isObjectValue() const;
            bool isArrayValue() const;
            bool isNullValue() const;
            virtual ~JSONValue();
        protected:
            JSON_TYPE vtype;
    };
    
    class JSONValueNumber: public JSONValue
    {
        public:
            JSONValueNumber(double value);
            void toString(std::string& toString);
            JSONValue* clone();
            void value(double& value);
            ~JSONValueNumber();
        private:
            double vvalue; 
    };
    
    class JSONValueString: public JSONValue
    {
        public:
            JSONValueString(const std::string& value);
            void toString(std::string& toString);
            JSONValue* clone();
            void value(std::string& value);
            ~JSONValueString();
        private:
            std::string vvalue; 
    };

    class JSONValueBoolean: public JSONValue
    {
        public:
            JSONValueBoolean(bool value);
            void toString(std::string& toString);
            JSONValue* clone();
            void value(bool& value) const;
            ~JSONValueBoolean();
        private:
            bool vvalue;
    };

    class JSONValueNULL: public JSONValue
    {
        public:
            JSONValueNULL();
            void toString(std::string& toString);
            JSONValue* clone();
            ~JSONValueNULL();
    };
    
    class JSONValueArray: public JSONValue
    {
        public:
            JSONValueArray();
            JSONValueArray(std::vector<JSONValue*>& array);
            void put(JSONValue* value);
            void toString(std::string& toString);
            JSONValue* clone();
            ~JSONValueArray();
        private:
            std::vector<JSONValue*> varray;
    };
    
    class JSONObject: public JSONValue
    {   
        public:
            JSONObject();
            JSONObject(const std::string& str);
            JSONObject(const JSONObject& obj);
            void get(const std::string& key, JSONValue* &value);
            void getBoolean(const std::string& key, bool &value);
            void getDouble(const std::string& key, double &value);
            void getInt(const std::string& key, int &value);
            void getString(const std::string& key, std::string& value);
            void getJSONArray(const std::string& key, JSONValueArray* &value);
            void getJSONObject(const std::string& key, JSONObject* &value);
            void put(const std::string& key, double value);
            void put(const std::string& key, std::string value);
            void put(const std::string& key, bool value);
            void put(const std::string& key, JSONValueArray& array);
            void put(const std::string& key, std::vector<std::string>& array);
            void put(const std::string& key, JSONValue& obj);
            void putNull(const std::string& key);
            void toString(std::string& toString);
            JSONValue* clone();
            ~JSONObject();
        private:
            std::map<std::string, JSONValue*> map;
            void put(const std::string& key, JSONValue* obj);
            void parse(const std::string& str);
            JSONValue* factory(const std::string& str, size_t begin,
            size_t end);
    };
}
#endif
