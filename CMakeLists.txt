#Project name
project(System_Overload)

#Cmake minimum require version
cmake_minimum_required(VERSION 2.8)

#Compilation options
add_definitions(-std=c++11 -Wall -O2 -pedantic)

#Adding external libraries to project
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

#Project merge
add_executable(System_Overload game.cpp main.cpp)
target_link_libraries(System_Overload ${SFML_LIBRARIES})

#Copy compiled project to destiny path
install(TARGETS System_Overload RUNTIME DESTINATION bin)
