#ifndef _JSON_OBJECT_H_
#define _JSON_OBJECT_H_

#include <string>
#include <sstream>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/regex.hpp>

namespace json
{
class JSONObject
{   
    public:
        JSONObject();
        JSONObject(const JSONObject& obj);

        bool parse(std::stringstream &stream);
        bool parse(const std::string &text);

        std::string get(const std::string &key) const;
        double getDouble(const std::string &key) const;
        int getInt(const std::string &key) const;
        bool getBoolean(const std::string &key) const;

        JSONObject getJSONObject(const std::string &key) const;

        std::vector<std::string> getArray(const std::string &key) const;
        std::vector<double> getArrayDouble(const std::string &key) const;
        std::vector<int> getArrayInt(const std::string &key) const;
        std::vector<bool> getArrayBoolean(const std::string &key) const;

        std::vector<JSONObject> getArrayJSONObject(const std::string &key) const;

        void put(const std::string& key, const std::string& value);
        void put(const std::string& key, const double value);
        void put(const std::string& key, const int value);
        void put(const std::string& key, const bool value);

        void put(const std::string& key, const std::vector<std::string>& values);
        void put(const std::string& key, const std::vector<int>& values);
        void put(const std::string& key, const std::vector<double>& values);
        void put(const std::string& key, const std::vector<bool>& values);

        std::string toString() const;

        ~JSONObject();
    private:
        JSONObject(boost::property_tree::ptree &ptChild);
        boost::property_tree::ptree *pt;
        boost::regex *exp;
};

std::ostream& operator<<(std::ostream& out, const JSONObject& json);
}
#endif
