/////////////////////////////////
///   Main game class
/////////////////////////////////

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <array>
#include <fstream>
#include <chrono>
#include <thread>
#include <iostream>
#include <ctime>

#include "main_config.hpp"
#include "menu_config.hpp"
#include "game_state.hpp"
#include "resource_holder.hpp"
#include "menu_state.hpp"

class Game
{
public:

    void            Start();
    void            Loading();
    GameState       Menu();
//    GameState       Lvl();
    void            End();

private:
/*
    void            grabInput();
    void            update();
    void            render();
*/
private:

    MainConfig                  main_config;
    MenuConfig                  menu_config;
    sf::RenderWindow*           gameWindow;
    ResourceHolder<sf::Texture> textureResources;
    ResourceHolder<sf::Font>    fontResources;
    GameState                   game_state;
};

#endif // GAME_HPP
