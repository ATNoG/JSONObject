#include <boost/property_tree/json_parser.hpp>
#include <iostream>

#include "JSON.hpp"

JSON::JSON()
{
    pt = new boost::property_tree::ptree();
}

JSON::JSON(boost::property_tree::ptree &ptChild)
{
    pt = new boost::property_tree::ptree(ptChild);
}

bool JSON::parse(std::stringstream &stream)
{
    boost::property_tree::read_json(stream, *pt);

    return true;
}

bool JSON::parse(std::string &text)
{
    boost::property_tree::read_json(text, *pt);

    return true;
}

std::string JSON::get(const std::string &key)
{
    std::string rv = "null";

    rv = pt->get<std::string>(key);

    return rv;
}

double JSON::getDouble(const std::string &key)
{
    double rv = 0.0;

    rv = pt->get<double>(key);

    return rv;
}

int JSON::getInt(const std::string &key)
{
    int rv = 0;

    rv = pt->get<int>(key);

    return rv;
}

JSON JSON::getJSON(const std::string &key)
{
    boost::property_tree::ptree& ptChild = pt->get_child(key);
    std::cerr<<"KEY: "<<key<<std::endl;
    JSON rv(ptChild);

    return rv;
}

JSON::~JSON()
{
    std::cerr<<"Destructor"<<std::endl;
    
    delete pt;

    std::cerr<<"Destructor"<<std::endl;
}

std::ostream& operator<<(std::ostream& out, const JSON& json)
{
    return out<<"JSON";
}
