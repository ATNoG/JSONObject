cmake_minimum_required(VERSION 2.6)
project(JSONObject)

find_package(Boost REQUIRED COMPONENTS regex thread)
find_package(Doxygen)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pipe -ansi -pedantic")
include_directories(${Boost_INCLUDE_DIR})

add_executable(main main.cpp JSONObject.cpp)
target_link_libraries(main ${Boost_REGEX_LIBRARY} ${Boost_THREAD_LIBRARY})

add_library(jsonobject SHARED JSONObject.cpp)
target_link_libraries(main ${Boost_REGEX_LIBRARY} ${Boost_THREAD_LIBRARY})

install(TARGETS jsonobject LIBRARY DESTINATION "lib")
install(FILES JSONObject.hpp DESTINATION "include")

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc ${DOXYGEN_EXECUTABLE} 
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)
