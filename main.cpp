#include <iostream>
#include <cstdlib>
#include </usr/share/include/selene.h>

#include "logger.hpp"


int main()
{
    Engine::Logger::_Logger test("main.log");
    sel::State lua;
    lua["logger"].SetObj(test,
                       "log", &Engine::Logger::_Logger::log);

    lua.Load("script.lua");
    return EXIT_SUCCESS;
}
