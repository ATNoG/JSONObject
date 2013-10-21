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
    
    class JValue
    {
        public:
            JValue(JSON_TYPE type);
            virtual void toString(std::string& toString)const=0;
            virtual JValue* clone()const=0;
            bool isBooleanValue() const;
            bool isNumberValue() const;
            bool isStringValue() const;
            bool isObjectValue() const;
            bool isArrayValue() const;
            bool isNullValue() const;
            virtual ~JValue();
        protected:
            JSON_TYPE _type;
    };
    
    class JNumber: public JValue
    {
        public:
            JNumber(double value);
            JNumber(const JNumber& value);
            void toString(std::string& toString)const;
            JValue* clone()const;
            void value(double& value);
            ~JNumber();
        private:
            double _value;
    };
    
    class JString: public JValue
    {
        public:
            JString(const std::string& value);
            JString(const JString& value);
            void toString(std::string& toString) const;
            JValue* clone() const;
            void value(std::string& value);
            ~JString();
        private:
            std::string _value; 
    };

    class JBoolean: public JValue
    {
        public:
            JBoolean(bool value);
            JBoolean(const JBoolean& value);
            void toString(std::string& toString)const;
            JValue* clone() const;
            void value(bool& value) const;
            ~JBoolean();
        private:
            bool _value;
    };

    class JNull: public JValue
    {
        public:
            JNull();
            void toString(std::string& toString)const;
            JValue* clone()const;
            ~JNull();
    };
    
    class JArray: public JValue
    {
        public:
            JArray();
            JArray(const std::vector<JValue*>& array);
            JArray(const std::vector<std::string>& array);
            JArray(const std::vector<double>& array);
            JArray(const std::vector<int>& array);
            JArray(const std::vector<bool>& array);
            void put(JValue* value);
            void toString(std::string& toString)const;
            JValue* clone()const;
            ~JArray();
        private:
            std::vector<JValue*> _array;
    };
    
    class JObject: public JValue
    {   
        public:
            JObject();
            JObject(const std::string& str);
            JObject(const JObject& obj);
            void get(const std::string& key, JValue* &value);
            void getBoolean(const std::string& key, bool &value);
            void getDouble(const std::string& key, double &value);
            void getInt(const std::string& key, int &value);
            void getString(const std::string& key, std::string& value);
            void getJArray(const std::string& key, JArray& value);
            void getJObject(const std::string& key, JObject& value) const;
            void put(const std::string& key, const std::string value);
            void put(const std::string& key, const char* value);
            void put(const std::string& key, const double value);
            void put(const std::string& key, const int value);
            void put(const std::string& key, const bool value);
            void put(const std::string& key, const JArray& array);
            void put(const std::string& key, const std::vector<std::string>& array);
            void put(const std::string& key, const std::vector<double>& array);
            void put(const std::string& key, const std::vector<int>& array);
            void put(const std::string& key, const std::vector<bool>& array);
            void put(const std::string& key, const JValue& obj);
            void putNull(const std::string& key);
            bool exists(const std::string& key) const;
            void remove(const std::string& key);
            void clear();
            void toString(std::string& toString) const;
            JValue* clone() const;
            JObject& operator=(const JObject& obj);
            ~JObject();
        private:
            void put(const std::string& key, JValue* obj);
            void parse(const std::string& str);
            JValue* factory(const std::string& str,size_t begin,size_t end);
           
            std::map<std::string, JValue*> _map;
    };
}
#endif
