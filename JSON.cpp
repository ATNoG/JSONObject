#include <boost/property_tree/json_parser.hpp>

#include "JSON.hpp"

bool JSON::parse(std::stringstream &stream)
{
    boost::property_tree::read_json(stream, pt);

    return true;
}

std::string JSON::get(const std::string &key)
{
    std::string rv = "null";

    rv = pt.get<std::string>(key);

    return rv;
}

double JSON::getDouble(const std::string &key)
{
    double rv = 0.0;

    rv = pt.get<double>(key);

    return rv;
}

int JSON::getInt(const std::string &key)
{
    int rv = 0;

    rv = pt.get<int>(key);

    return rv;
}


std::ostream& operator<<(std::ostream& out, const JSON& json)
{
    return out << "JSON" << std::endl;
}
