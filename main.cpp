#include "JSONObject.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

#define SIZE 1000000

int main(int argc, char *argv[])
{
    //std::string txt="{\"keys\":[\"0x000\",\"0x001\",\"0x002\",\"0x003\"],\"type\":\"getall request\"}";
    std::string txt="{\"keys\":[],\"type\":\"getall request\",\"json\":{}}";
    //std::string txt= "{\"keys\":[\"0x000\",\"0x001\",\"0x002\",\"0x003\"]}";

    std::cout<<"TXT:"<<txt<<std::endl;
    std::string str;
    json::JSONObject j(txt);

    j.toString(str);
    std::cout<<str<<std::endl;
    str.clear();

    /*j.get("type", str);
    std::cout<<str<<std::endl;
    str.clear();

    j.put("J", "Hello World!!");
    j.toString(str);
    std::cout<<str<<std::endl;
    
    j.put("J", std::string("Hello World V2!!"));
    str.clear();
    j.toString(str);
    std::cout<<str<<std::endl;
    
    json::JSONObject insideJ;
    
    std::vector<int> v (8,5);

    insideJ.put("array", v);

    insideJ.put("string", "new stuff");
    insideJ.put("number", 3.141516);
    j.put("JSON", insideJ);
    
    str.clear();
    j.toString(str);
    std::cout<<str<<std::endl;
    json::JSONObject retriveJ;
    
    j.get("JSON", retriveJ);
    
    str="";
    retriveJ.toString(str);
    std::cout<<str<<std::endl;
    
    std::string path="sample.json";
    std::ifstream file;
    std::stringstream ss;

    if(argc > 1)
    {
        path = std::string(argv[1]);
    }
    std::cout<<"Open file: ";
    file.open(path.c_str());
    if (file.is_open())
    {
        std::cout<<"success"<<std::endl;
        ss << file.rdbuf();
        std::string txt = ss.str();
        json::JSONObject stuff(txt);
        str="";
        stuff.toString(str);
        std::cout<<str<<std::endl;
    }
    else
    {
        std::cout<<"fail"<<std::endl;
    }*/
    
    return 0;
}
