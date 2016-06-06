#include "game.hpp"
#include "game_state.hpp"
#include <iostream>


int mainImp(int argc, char *argv[]) 
{
    Game game;
    GameState state;
    game.Start();
    game.Loading();
    state = game.Menu();
    if (state == GameState::END)
        game.End();
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    try {
        return mainImp(argc, argv);
    } catch (std::exception const & e) {
        std::cout << "Unhandled exception -> " << e.what() << std::endl; 
    } catch (...) {
        std::cout << "Unrecognized unhandled exception" << std::endl;
    }
    
    return EXIT_FAILURE;
}
