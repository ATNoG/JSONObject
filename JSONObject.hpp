#ifndef _JSON_OBJECT_H_
#define _JSON_OBJECT_H_

#include <string>
#include <sstream>
#include <vector>

#include <boost/property_tree/ptree.hpp>

class JSONObject
{   
    public:
        JSONObject();
        JSONObject(const JSONObject& obj);

        bool parse(std::stringstream &stream);
        bool parse(std::string &text);

        std::string get(const std::string &key);
        double getDouble(const std::string &key);
        int getInt(const std::string &key);
        bool getBoolean(const std::string &key);

        JSONObject getJSONObject(const std::string &key);

        std::vector<std::string> getArray(const std::string &key);
        std::vector<double> getArrayDouble(const std::string &key);
        std::vector<int> getArrayInt(const std::string &key);
        std::vector<bool> getArrayBoolean(const std::string &key);

        std::vector<JSONObject> getArrayJSONObject(const std::string &key);

        std::string toString() const;

        ~JSONObject();
    private:
        JSONObject(boost::property_tree::ptree &ptChild);
        boost::property_tree::ptree *pt;
};

std::ostream& operator<<(std::ostream& out, const JSONObject& json);

#endif
