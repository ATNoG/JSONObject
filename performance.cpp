#include <string>
#include <ctime>
#include "JSONObject.hpp"

#define SIZE 1024

int main(int argc, char *argv[])
{
    std::cout<<"JSONObject simple performance test."<<std::endl;
    
    std::vector<std::string> array;
    
    for(int i = 0; i < SIZE; i++)
    {
        array.push_back("This is a gigantic string...");
    }
    
    json::JSONObject j;
    std::cerr<<"Testing..."<<std::endl;
    clock_t begin = clock();
    j.put("strings", array);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    std::cout<<"Insert array: "<<elapsed_secs<<std::endl;
    
    return 0;
}
