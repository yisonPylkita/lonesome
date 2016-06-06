#ifndef MENU_CONFIG_HPP
#define MENU_CONFIG_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <SFML/System/Vector2.hpp>


struct MenuConfig {

    sf::Vector2f position[15][2];
    std::string fontName;
    unsigned int fontSize;

    void loadConfig()
    {
        std::ifstream configFile;
        configFile.open("Media/Menu/menu.conf");
        configFile >> fontName;
        configFile >> fontSize;
        // TODO: refactor this !!!
        for (int i = 0; i < 15; ++i) { 
            configFile >> position[i][0].x >> position[i][0].y;
            std::cout << position[i][0].x << " " << position[i][0].y << std::endl;
            configFile >> position[i][1].x >> position[i][1].y;
            std::cout << position[i][1].x << " " << position[i][1].y << std::endl;
        }
        configFile.close();
    }

};

#endif // MENU_CONFIG_HPP
