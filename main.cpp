#include "JSONObject.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

#define SIZE 1000000

int main(int argc, char *argv[])
{
    std::vector<std::string> array;
    for(int i = 0; i < SIZE; i++)
        array.push_back("<item id='0df3ecaa-3af9-4e38-ba82-37243e92f882'><lofar xmlns='http://lofar/agriculture'><published> Thu Jan 01 01:00:00 WET 1970 </published><fieldSensor><temperature> -14.472147147695637 </temperature><humidity> 59.0 </humidity></fieldSensor><weatherForecast><temperature> 17.07871504916448 </temperature><humidity> 87.0 </humidity><windSpeed> 9.774725608655714 </windSpeed><windDirection> WNW </windDirection><rain> 0.804741766718436 </rain></weatherForecast></lofar></item>");
    json::JSONObject j;
    clock_t begin = clock();
    j.put("strings", array);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout<<"Time: "<<elapsed_secs<<" seconds."<<std::endl;
    
    begin = clock();
    json::JSONObject obj, obj2;
    obj2.put("string", "Hello world!!");
    std::string str;
    obj2.toString(str);
    std::cout<<str<<std::endl;
    
    obj.put("number", 3.1416);
    obj.put("boolean", false);
    obj.put("success", true);
    std::vector<std::string> v;
    v.push_back(std::string("hello"));
    v.push_back(std::string("world"));
    obj.put("array", v);
    obj.putNull("NULL");
    str="";
    obj.toString(str);
    std::cout<<str<<std::endl;
    
    obj.put("obj", obj2);
    str="";
    obj.toString(str);
    std::cout<<str<<std::endl;
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout<<"Time: "<<elapsed_secs<<" seconds."<<std::endl;
    
    std::string txt = "{\"json\":\n\
    {\"another json\":\n\
    {\"yet another json\":\n\
    {\"key1\":\"hello\",\n\
    \"key2\":null,\n\
    \"key3\":false,\n\
    \"key4\":12.00,\n\
    \"key5\":\"hello\",\n\
    \"key6\":\"world\"}}}, \"key\":52, \"stuff\":[1,2,3]}";
    begin = clock();
    json::JSONObject stuff(txt);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout<<"Time: "<<elapsed_secs<<" seconds."<<std::endl;
    str="";
    stuff.toString(str);
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
        txt = ss.str();
        
        begin = clock();
        json::JSONObject stuff(txt);
        end = clock();
        elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout<<"Time: "<<elapsed_secs<<" seconds."<<std::endl;
        str="";
        stuff.toString(str);
        std::cout<<str<<std::endl;
    }
    else
    {
        std::cout<<"fail"<<std::endl;
    }
    
    return 0;
}
