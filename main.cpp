#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "JSON.hpp"

int main()
{
    std::cout<<"JSON V0.1"<<std::endl;

    std::string line;
    std::ifstream file;
    std::stringstream ss;
    JSON obj;

    file.open("small.json");
    if (file.is_open())
    {
        std::cout<<"File opened"<<std::endl;
        ss << file.rdbuf();
        
        obj.parse(ss);
        file.close();

        std::cout<<obj.get("string")<<std::endl;
        std::cout<<obj.getDouble("number")<<std::endl;
        std::cout<<obj.getInt("integer")<<std::endl;

        JSON obj2 = obj.getJSON("json");
        std::cout<<obj2.get("string")<<std::endl;
    }

    std::cout<<obj<<std::endl;

    return 0;
}
