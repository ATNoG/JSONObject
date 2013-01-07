#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "JSONObject.hpp"

int main(int argc, char *argv[])
{
    std::cout<<"JSON wrapper for Boost V1.0"<<std::endl;

    std::string *path;
    std::ifstream file;
    std::stringstream ss;

    if(argc > 1)
    {
        path = new std::string(argv[1]);
    }
    else
    {
        path = new std::string("small.json");
    }

    file.open(path->c_str());
    delete path;
    if (file.is_open())
    {
        std::cout<<"File opened"<<std::endl;
        ss << file.rdbuf();
        
        json::JSONObject obj(ss);
        file.close();

        std::cout<<obj.get("string")<<std::endl;
        std::cout<<obj.getDouble("number")<<std::endl;
        std::cout<<obj.getInt("integer")<<std::endl;
        std::cout<<obj.getBoolean("boolean")<<std::endl;

        std::vector<std::string> vec = obj.getArray("array");
        std::cout<<"Array: "<<vec.size()<<std::endl;
        for(size_t i = 0; i < vec.size(); i++)
        {
            std::cout<<"Value "<<i<<": "<<vec.at(i)<<std::endl;
        }

        std::vector<double> vecDouble = obj.getArrayDouble("arrayDouble");
        std::cout<<"Array: "<<vecDouble.size()<<std::endl;
        for(size_t i = 0; i < vecDouble.size(); i++)
        {
            std::cout<<"Value "<<i<<": "<<vecDouble.at(i)<<std::endl;
        }

        std::vector<int> vecInt = obj.getArrayInt("arrayInt");
        std::cout<<"Array: "<<vecInt.size()<<std::endl;
        for(size_t i = 0; i < vecInt.size(); i++)
        {
            std::cout<<"Value "<<i<<": "<<vecInt.at(i)<<std::endl;
        }

        std::vector<bool> vecBool = obj.getArrayBoolean("arrayBoolean");
        std::cout<<"Array: "<<vecBool.size()<<std::endl;
        for(size_t i = 0; i < vecBool.size(); i++)
        {
            std::cout<<"Value "<<i<<": "<<vecBool.at(i)<<std::endl;
        }

        std::vector<json::JSONObject> vecJSON = obj.getArrayJSONObject("arrayJSON");
        std::cout<<"Array: "<<vecJSON.size()<<std::endl;
        for(size_t i = 0; i < vecJSON.size(); i++)
        {
            std::cout<<"Value "<<i<<": "<<std::endl<<vecJSON.at(i)<<std::endl;
        }

        json::JSONObject obj2 = obj.getJSONObject("json");
        json::JSONObject obj3 = obj.getJSONObject("json");
        obj2.put("number", 5.23);
        obj2.putNull("null value");
        std::cout<<"Internal JSON:"<<std::endl<<obj2<<std::endl;


        std::vector<json::JSONObject> vecJSON2;
        vecJSON2.push_back(obj2);
        vecJSON2.push_back(obj3);
        vecJSON2.push_back(obj);

        obj.put("array JSON", vecJSON2);

        obj.put("new json object", obj2);

        obj.put("newArrayString", vec);
        obj.put("newArrayInt", vecInt);
        obj.put("newArrayDouble", vecDouble);
        obj.put("newArrayBool", vecBool);
    }

    return 0;
}
