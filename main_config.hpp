#ifndef __MAIN_CONFIG__
#define __MAIN_CONFIG__

#include <SFML/System/Vector2.hpp>
#include <string>
#include <fstream>


struct MainConfig {
    sf::Vector2u windowSize;
    std::string gameName;
    std::ifstream gameConfigFile;

    void loadConfig() {
        gameConfigFile.open("main.conf");
        gameConfigFile >> windowSize.x >> windowSize.y;
        gameConfigFile >> gameName;
        gameConfigFile.close();
    }
};

#endif // __MAIN_CONFIG__
