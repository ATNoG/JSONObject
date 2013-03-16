/**
 * @file    JSONObject.hpp
 * @class   JSONObject
 * @author  Mario Antunes (mariolpantunes@gmail.com)
 * @version 1.0
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

#include <boost/property_tree/ptree.hpp>
#include <boost/regex.hpp>

#define BOOST_SPIRIT_THREADSAFE

namespace json
{
    /**
     * @class JSONObject
     * JSONObject is a easy to use JSON wrapper for boost property tree.
     * Based on the API of Java org.JSON library (http://www.json.org/java/index.html).
     */
    class JSONObject
    {   
        public:
            /**
             * Default constructor.
             */
            JSONObject();
            /**
             * Construct an JSON object from a input stream.
             * @param stream input stream from a file or string.
             */
            JSONObject(std::istream &stream);
            /**
             * Construct an JSON object from a string.
             * @param text input string that represents a JSON object. 
             */
            JSONObject(const std::string &text);
            /**
             * Copy constructor.
             * @param obj another JSONObject object.
             */
            JSONObject(const JSONObject& obj);

            /**
             * Retrieve the string value from the JSON object associated with the key.
             * @param key name of the value.
             * @return the string associated with the key.
             */
            std::string get(const std::string &key) const;
            /**
             * Retrieve the double value from the JSON object associated with the key.
             * @param key name of the value.
             * @return the double associated with the key.
             */
            double getDouble(const std::string &key) const;
            /**
             * Retrieve the int value from the JSON object associated with the key.
             * @param key name of the value.
             * @return the int associated with the key.
             */
            int getInt(const std::string &key) const;
            /**
             * Retrieve the boolean value from the JSON object associated with the key.
             * @param key name of the value.
             * @return the boolean associated with the key.
             */
            bool getBoolean(const std::string &key) const;
            /**
             * Verifies if the value associated with the key is NULL or not.
             * @param key name of the value.
             * @return true if the value is NULL; false otherwise.
             */
            bool isNull(const std::string &key) const;
            /**
             * Retrieve the JSON object associated with the key.
             * @param key name of the value.
             * @return the JSON object associated with the key.
             */
            JSONObject getJSONObject(const std::string &key) const;
            /**
             * Retrieve the vector of strings associated with the key.
             * If the value associated with the key is NULL the functions returns a empty vector.
             * @param key name of the value.
             * @return the vector of strings associated with the key.
             */
            std::vector<std::string> getArray(const std::string &key) const;
            /**
             * Retrieve the vector of doubles associated with the key.
             * If the value associated with the key is NULL the functions returns a empty vector.
             * @param key name of the value.
             * @return the vector of doubles associated with the key.
             */
            std::vector<double> getArrayDouble(const std::string &key) const;
            /**
             * Retrieve the vector of ints associated with the key.
             * If the value associated with the key is NULL the functions returns a empty vector.
             * @param key name of the value.
             * @return the vector of ints associated with the key.
             */
            std::vector<int> getArrayInt(const std::string &key) const;
            /**
             * Retrieve the vector of booleans associated with the key.
             * If the value associated with the key is NULL the functions returns a empty vector.
             * @param key name of the value.
             * @return the vector of booleans associated with the key.
             */
            std::vector<bool> getArrayBoolean(const std::string &key) const;
            /**
             * Retrieve the vector of JSON objects associated with the key.
             * If the value associated with the key is NULL the functions returns a empty vector.
             * @param key name of the value.
             * @return the vector of JSON objects associated with the key.
             */
            std::vector<JSONObject> getArrayJSONObject(const std::string &key) const;
            /**
             * Insert a string value with the specified key.
             * @param key name of the value.
             * @param value the value associated with the key.
             */
            void put(const std::string& key, const std::string& value);
            /**
             * Insert a C style string value with the specified key.
             * @param key name of the value.
             * @param value the value associated with the key.
             */
            void put(const std::string& key, const char* value);
            /**
             * Insert a double value with the specified key.
             * @param key name of the value.
             * @param value the value associated with the key.
             */
            void put(const std::string& key, const double value);
            /**
             * Insert a int value with the specified key.
             * @param key name of the value.
             * @param value the value associated with the key.
             */
            void put(const std::string& key, const int value);
            /**
             * Insert a boolean value with the specified key.
             * @param key name of the value.
             * @param value the value associated with the key.
             */
            void put(const std::string& key, const bool value);
            /**
             * Insert a NULL value with the specified key.
             * @param key name of the value.
             */
            void putNull(const std::string& key);
            /**
             * Insert a JSON object with the specified key.
             * @param key name of the value.
             * @param value the value associated with the key.
             */
            void put(const std::string& key, const JSONObject& value);
            /**
             * Insert a vector of string values with the specified key.
             * @param key name of the value.
             * @param values the values associated with the key.
             */
            void put(const std::string& key, const std::vector<std::string>& values);
            /**
             * Insert a vector of double values with the specified key.
             * @param key name of the value.
             * @param values the values associated with the key.
             */     
            void put(const std::string& key, const std::vector<double>& values);
            /**
             * Insert a vector of int values with the specified key.
             * @param key name of the value.
             * @param values the values associated with the key.
             */
            void put(const std::string& key, const std::vector<int>& values);
            /**
             * Insert a vector of boolean values with the specified key.
             * @param key name of the value.
             * @param values the values associated with the key.
             */
            void put(const std::string& key, const std::vector<bool>& values);
            /**
             * Insert a vector of JSON objects with the specified key.
             * @param key name of the value.
             * @param values the values associated with the key.
             */
            void put(const std::string& key, const std::vector<JSONObject>& values);
            /**
             * Writes the JSON object into a string.
             * @return a string that represents the JSON object.
             */ 
            std::string toString() const;
            /**
             * Overload attribution operator.
             * The overload manages the deletion, creation and copy of Boost Property Tree. 
             * @param obj another JSON object.
             */ 
            JSONObject& operator=(const JSONObject& obj);

            /**
             * Default destructor.
             */
            ~JSONObject();
        private:
            /**
             * Private constructor.
             * Constructs a JSON object based on a existing Boost property tree. 
             * @param ptChild an Boost Property Tree.
             */ 
            JSONObject(const boost::property_tree::ptree& ptChild);

            /**
             * Boost property tree used to store the JSON object.
             * The property tree is the backend of the JSON object.
             */
            boost::property_tree::ptree pt;
            /**
             * Boost Regular expression, used to fix a limitation of boost property tree write_json() function.
             * The regular expression represents numbers and keywords (null, true and false) and correct their value in the JSON toString() funtion.
             */
            boost::regex exp;
    };

    /**
     * Overload out stream operator.
     * It prints out the result of the toString() function.
     * @param out output stream.
     * @param json another JSON object.
     */ 
    std::ostream& operator<<(std::ostream& out, const JSONObject& json);
}

#endif
