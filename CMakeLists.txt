#Project name
project(Engine)

#Cmake minimum require version
cmake_minimum_required(VERSION 2.8)

#Compilation options
add_definitions(-std=c++11 -Wall -O2 -llua)

#Adding external libraries to project
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

#Project merge
add_executable(Engine logger.cpp main.cpp)
target_link_libraries(Engine ${SFML_LIBRARIES})

#Copy compiled project to destiny path
install(TARGETS Engine RUNTIME DESTINATION bin)
