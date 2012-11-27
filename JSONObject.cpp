#include "JSONObject.hpp"

#include <iostream>

#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#define NUMBER "[0-9]+(.[0-9]+)?"
#define KEYWORDS "null|true|false"
#define EXP "(:|\\[|,)\\s*\"("KEYWORDS"|"NUMBER")\""

namespace json
{

JSONObject::JSONObject()
{
    pt = new boost::property_tree::ptree();
    exp = new boost::regex(EXP);
}

JSONObject::JSONObject(const JSONObject& obj)
{
    pt = new boost::property_tree::ptree(*(obj.pt));
    exp = new boost::regex(EXP);
}

JSONObject::JSONObject(boost::property_tree::ptree &ptChild)
{
    pt = new boost::property_tree::ptree(ptChild);
    exp = new boost::regex(EXP);
}

bool JSONObject::parse(std::stringstream &stream)
{
    boost::property_tree::read_json(stream, *pt);

    return true;
}

bool JSONObject::parse(const std::string &text)
{
    std::stringstream ss(text);
    boost::property_tree::read_json(ss, *pt);

    return true;
}

std::string JSONObject::get(const std::string &key) const
{
    std::string rv = "null";
    rv = pt->get<std::string>(key);
    return rv;
}

double JSONObject::getDouble(const std::string &key) const
{
    double rv = 0.0;
    rv = pt->get<double>(key);
    return rv;
}

int JSONObject::getInt(const std::string &key) const
{
    int rv = 0;
    rv = pt->get<int>(key);
    return rv;
}

bool JSONObject::getBoolean(const std::string &key) const
{
    bool rv = false;
    rv = pt->get<bool>(key);
    return rv;
}

JSONObject JSONObject::getJSONObject(const std::string &key) const
{
    boost::property_tree::ptree ptChild = pt->get_child(key);
    JSONObject rv(ptChild);

    return rv;
}

std::vector<std::string> JSONObject::getArray(const std::string &key) const
{
    std::vector<std::string> rv;

    BOOST_FOREACH(boost::property_tree::ptree::value_type &values, pt->get_child(key))
    {
        rv.push_back(values.second.data());
    }

    return rv;
}

std::vector<double> JSONObject::getArrayDouble(const std::string &key) const
{
    std::vector<std::string> values = this->getArray(key);
    std::vector<double> rv;
    double number = 0.0;

    BOOST_FOREACH(std::string& text, values)
    {
        std::istringstream istream(text);
        istream >> number;
        rv.push_back(number);
    }

    return rv;
}

std::vector<int> JSONObject::getArrayInt(const std::string &key) const
{
    std::vector<std::string> values = this->getArray(key);
    std::vector<int> rv;
    int number = 0.0;

    BOOST_FOREACH(std::string& text, values)
    {
        std::istringstream istream(text);
        istream >> number;
        rv.push_back(number);
    }

    return rv;
}

std::vector<bool> JSONObject::getArrayBoolean(const std::string &key) const
{
    std::vector<std::string> values = this->getArray(key);
    std::vector<bool> rv;

    BOOST_FOREACH(std::string& text, values)
    {
        if(text=="true")
            rv.push_back(true);
        else
            rv.push_back(false);
    }

    return rv;
}

std::vector<JSONObject> JSONObject::getArrayJSONObject(const std::string &key) const
{
    std::vector<JSONObject> rv;
 
    BOOST_FOREACH(boost::property_tree::ptree::value_type &values, pt->get_child(key))
    {
        JSONObject obj(values.second);
        rv.push_back(obj);
    }

    return rv;
}

void JSONObject::put(const std::string& key, const std::string& value)
{
    pt->put(key, value);
}

void JSONObject::put(const std::string& key, const double value)
{
    pt->put(key, value);
}

void JSONObject::put(const std::string& key, const int value)
{
    pt->put(key, value);
}

void JSONObject::put(const std::string& key, const bool value)
{
    pt->put(key, value);
}

void JSONObject::put(const std::string& key, const std::vector<std::string>& values)
{
    boost::property_tree::ptree arrayChild;
    boost::property_tree::ptree arrayElement;

    BOOST_FOREACH(const std::string& text, values)
    {
        arrayElement.put_value(text);
        arrayChild.push_back(std::make_pair("",arrayElement));
    }

    pt->put_child(key, arrayChild);
}

void JSONObject::put(const std::string& key, const std::vector<int>& values)
{
    boost::property_tree::ptree arrayChild;
    boost::property_tree::ptree arrayElement;

    BOOST_FOREACH(int number, values)
    {
        arrayElement.put_value(number);
        arrayChild.push_back(std::make_pair("",arrayElement));
    }

    pt->put_child(key, arrayChild);
}

void JSONObject::put(const std::string& key, const std::vector<double>& values)
{
    boost::property_tree::ptree arrayChild;
    boost::property_tree::ptree arrayElement;

    BOOST_FOREACH(double number, values)
    {
        arrayElement.put_value(number);
        arrayChild.push_back(std::make_pair("",arrayElement));
    }

    pt->put_child(key, arrayChild);
}

void JSONObject::put(const std::string& key, const std::vector<bool>& values)
{
    boost::property_tree::ptree arrayChild;
    boost::property_tree::ptree arrayElement;

    BOOST_FOREACH(bool value, values)
    {
        arrayElement.put_value(value);
        arrayChild.push_back(std::make_pair("",arrayElement));
    }

    pt->put_child(key, arrayChild);
}

std::string JSONObject::toString() const
{
    std::stringstream ss;
    boost::property_tree::json_parser::write_json(ss, *pt);
    std::string rv = boost::regex_replace(ss.str(), *exp, "$1$2");
    //rv.erase(remove_if(rv.begin(), rv.end(), isspace), rv.end());

    return rv;
}

JSONObject::~JSONObject()
{
    delete pt;
    delete exp;
}

std::ostream& operator<<(std::ostream& out, const JSONObject& json)
{   
    return out<<json.toString();
}
}
