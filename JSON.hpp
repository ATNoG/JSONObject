#ifndef _JSON_H_
#define _JSON_H_

#include <string>
#include <sstream>

#include <boost/property_tree/ptree.hpp>

class JSON
{   
    public:
        bool parse(std::stringstream &stream);
        std::string get(const std::string &key);
        double getDouble(const std::string &key);
        int getInt(const std::string &key);

    private:
        boost::property_tree::ptree pt;
};

std::ostream& operator<<(std::ostream& out, const JSON& json);

#endif
