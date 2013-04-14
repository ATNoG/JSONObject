#include <string>
#include <ctime>
#include "JSONObject.hpp"

#define SIZE 100000

int main(int argc, char *argv[])
{
    std::cout<<"JSONObject simple performance test."<<std::endl;
    
    std::vector<std::string> array;
    
    for(int i = 0; i < SIZE; i++)
    {
        array.push_back("<item id='0df3ecaa-3af9-4e38-ba82-37243e92f882'><lofar xmlns='http://lofar/agriculture'><published> Thu Jan 01 01:00:00 WET 1970 </published><fieldSensor><temperature> -14.472147147695637 </temperature><humidity> 59.0 </humidity></fieldSensor><weatherForecast><temperature> 17.07871504916448 </temperature><humidity> 87.0 </humidity><windSpeed> 9.774725608655714 </windSpeed><windDirection> WNW </windDirection><rain> 0.804741766718436 </rain></weatherForecast></lofar></item>");
    }
    
    json::JSONObject j;
    std::cerr<<"Testing..."<<std::endl;
    clock_t begin = clock();
    j.put("strings", array);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    std::cout<<"Insert array: "<<elapsed_secs<<std::endl;
    
    std::cerr<<"Testing..."<<std::endl;
    begin = clock();
    std::vector<std::string> array2 = j.getArray("strings");
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    std::cout<<"Retrieve array: "<<elapsed_secs<<std::endl;

    return 0;
}
