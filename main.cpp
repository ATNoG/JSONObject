#include "JSONObject.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

#define SIZE 1000000

int main(int argc, char *argv[])
{
    /*std::vector<std::string> array;
    for(int i = 0; i < SIZE; i++)
        array.push_back("<item id='0df3ecaa-3af9-4e38-ba82-37243e92f882'><lofar xmlns='http://lofar/agriculture'><published> Thu Jan 01 01:00:00 WET 1970 </published><fieldSensor><temperature> -14.472147147695637 </temperature><humidity> 59.0 </humidity></fieldSensor><weatherForecast><temperature> 17.07871504916448 </temperature><humidity> 87.0 </humidity><windSpeed> 9.774725608655714 </windSpeed><windDirection> WNW </windDirection><rain> 0.804741766718436 </rain></weatherForecast></lofar></item>");
    json::JSONObject j;
    clock_t begin = clock();
    j.put("strings", array);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout<<"Time: "<<elapsed_secs<<" seconds."<<std::endl;*/
    
    std::string txt="{\"J\":5,\"0\":\"{\\\"key\\\":\\\"value\\\"}\"}";

    std::cout<<"TXT:"<<txt<<std::endl;
    
    std::string str;
    json::JSONObject j2(txt);

    j2.getString("0", str);
    std::cout<<str<<std::endl;
    str.clear();

    j2.toString(str);
    std::cout<<str<<std::endl;
    str.clear();

    json::JSONObject j;
    j.put("string", "Hello World!!");
    
    j.toString(str);
    std::cout<<str<<std::endl;
    
    j.put("string", std::string("Hello World V2!!"));
    str="";
    j.toString(str);
    std::cout<<str<<std::endl;
    
    json::JSONObject insideJ;
    
    std::vector<int> v (8,5);

    insideJ.put("array", v);

    insideJ.put("string", "new stuff");
    insideJ.put("number", 3.141516);
    j.put("JSON", insideJ);
    
    str="";
    j.toString(str);
    std::cout<<str<<std::endl;
    
    json::JSONObject retriveJ;
    
    j.getJSONObject("JSON", retriveJ);
    
    str="";
    retriveJ.toString(str);
    std::cout<<str<<std::endl;
    
    /*std::string path="sample.json";
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
