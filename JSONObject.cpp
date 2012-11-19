#include <iostream>

#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "JSONObject.hpp"

JSONObject::JSONObject()
{
    pt = new boost::property_tree::ptree();
}

JSONObject::JSONObject(const JSONObject& obj)
{
    std::cerr<<"Copy constructor..."<<std::endl;
    pt = new boost::property_tree::ptree(*(obj.pt));
}

JSONObject::JSONObject(boost::property_tree::ptree &ptChild)
{
    pt = new boost::property_tree::ptree(ptChild);
}

bool JSONObject::parse(std::stringstream &stream)
{
    boost::property_tree::read_json(stream, *pt);

    return true;
}

bool JSONObject::parse(std::string &text)
{
    boost::property_tree::read_json(text, *pt);

    return true;
}

std::string JSONObject::get(const std::string &key)
{
    std::string rv = "null";
    rv = pt->get<std::string>(key);
    return rv;
}

double JSONObject::getDouble(const std::string &key)
{
    double rv = 0.0;
    rv = pt->get<double>(key);
    return rv;
}

int JSONObject::getInt(const std::string &key)
{
    int rv = 0;
    rv = pt->get<int>(key);
    return rv;
}

bool JSONObject::getBoolean(const std::string &key)
{
    bool rv = false;
    rv = pt->get<bool>(key);
    return rv;
}

JSONObject JSONObject::getJSONObject(const std::string &key)
{
    boost::property_tree::ptree ptChild = pt->get_child(key);
    JSONObject rv(ptChild);

    return rv;
}

std::vector<std::string> JSONObject::getArray(const std::string &key)
{
    std::vector<std::string> rv;

    BOOST_FOREACH(boost::property_tree::ptree::value_type &values, pt->get_child(key))
    {
        rv.push_back(values.second.data());
    }

    return rv;
}

std::vector<double> JSONObject::getArrayDouble(const std::string &key)
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

std::vector<int> JSONObject::getArrayInt(const std::string &key)
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

std::vector<bool> JSONObject::getArrayBoolean(const std::string &key)
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

std::vector<JSONObject> JSONObject::getArrayJSONObject(const std::string &key)
{
    std::vector<JSONObject> rv;
 
    BOOST_FOREACH(boost::property_tree::ptree::value_type &values, pt->get_child(key))
    {
        JSONObject obj(values.second);
        rv.push_back(obj);
    }

    return rv;
}

std::string JSONObject::toString() const
{
    std::stringstream ss;
    boost::property_tree::json_parser::write_json(ss, *pt);
    std::string rv = ss.str();

    return rv;
}

JSONObject::~JSONObject()
{
    delete pt;
}

std::ostream& operator<<(std::ostream& out, const JSONObject& json)
{   
    return out<<json.toString();
}
