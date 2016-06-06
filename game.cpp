#include "game.hpp"

/*
void Game::grabInput()
{

}

void Game::update()
{

}

void Game::render()
{

}
*/

void Game::Start()
{
    main_config.loadConfig();
    gameWindow = new sf::RenderWindow;
    gameWindow->create(sf::VideoMode(main_config.windowSize.x, main_config.windowSize.y, 32), main_config.gameName, sf::Style::Fullscreen);
    textureResources.load("Loading.bmp", "Media/Textures/Loading.bmp");
    gameWindow->setFramerateLimit(60);
    if (!sf::Shader::isAvailable())
        throw std::runtime_error("Shaders unavailable");
}

void Game::Loading()
{
    sf::Sprite loading;
    loading.setTexture(textureResources.get("Loading.bmp"));
    loading.setScale(3., 3.);
    loading.setPosition(350., 250.);

    // To render in another thread window have to be detached 
    gameWindow->setActive(false);

    std::thread render_load_screen([&](){
        gameWindow->setActive();
       for (sf::Clock clock; clock.getElapsedTime() < sf::seconds(3.);) {
           gameWindow->clear(sf::Color::Transparent);
           gameWindow->draw(loading);
           gameWindow->display();
       }
    });

    // Load textures
    std::ifstream fin;
    fin.open("Media/Textures/texture.conf");
    int n;
    fin >> n;
    // Load all textures listed in  Media/Textures/texture.conf file
    for (int i = 0; i < n; ++i) {
        std::string temp;
        fin >> temp;
        textureResources.load(temp, std::string("Media/Textures/") + temp);
    }
    fin.close();

    // Load fonts
    fin.open("Media/Font/font.conf");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        std::string temp;
        fin >> temp;
        fontResources.load(temp, std::string("Media/Font/") + temp);
    }
    fin.close();

    // Load menu configuration
    menu_config.loadConfig();

    render_load_screen.join();
}

GameState Game::Menu()
{
    // Set game state to Game::MENU
    game_state = GameState::MENU;

    std::string fontName;
    fontName = menu_config.fontName;
    sf::Text game_name(main_config.gameName, fontResources.get(fontName));

    sf::Text start("Start Game", fontResources.get(fontName));
        sf::Text new_game("New Game", fontResources.get(fontName));
            sf::Text easy("Easy", fontResources.get(fontName));
            sf::Text normal("Normal", fontResources.get(fontName));
            sf::Text hard("Hard", fontResources.get(fontName));
            sf::Text backFromNewGame("Back", fontResources.get(fontName));
        sf::Text continue_game("Continue", fontResources.get(fontName));
        sf::Text backFromStart("Back", fontResources.get(fontName));
    sf::Text options("Options", fontResources.get(fontName));
        sf::Text music_vol("Music", fontResources.get(fontName));
        sf::Text sfx_vol("SFX", fontResources.get(fontName));
        sf::Text fulscreen_game("Fulscreen", fontResources.get(fontName));
        sf::Text backFromOptions("Back", fontResources.get(fontName));
    sf::Text credits("Credits", fontResources.get(fontName));
    sf::Text quit("Quit", fontResources.get(fontName));

    game_name.setCharacterSize(35);

    start.setCharacterSize(menu_config.fontSize);
        new_game.setCharacterSize(menu_config.fontSize);
            easy.setCharacterSize(menu_config.fontSize);
            normal.setCharacterSize(menu_config.fontSize);
            hard.setCharacterSize(menu_config.fontSize);
            backFromNewGame.setCharacterSize(menu_config.fontSize);
        continue_game.setCharacterSize(menu_config.fontSize);
        backFromStart.setCharacterSize(menu_config.fontSize);
    options.setCharacterSize(menu_config.fontSize);
        music_vol.setCharacterSize(menu_config.fontSize);
        sfx_vol.setCharacterSize(menu_config.fontSize);
        fulscreen_game.setCharacterSize(menu_config.fontSize);
        backFromOptions.setCharacterSize(menu_config.fontSize);
    credits.setCharacterSize(menu_config.fontSize);
    quit.setCharacterSize(menu_config.fontSize);

    game_name.setColor(sf::Color::White);

    start.setColor(sf::Color::Cyan);
        new_game.setColor(sf::Color::White);
            easy.setColor(sf::Color::White);
            normal.setColor(sf::Color::White);
            hard.setColor(sf::Color::White);
            backFromNewGame.setCharacterSize(menu_config.fontSize);
        continue_game.setColor(sf::Color::White);
        backFromStart.setCharacterSize(menu_config.fontSize);
    options.setColor(sf::Color::White);
        music_vol.setColor(sf::Color::White);
        sfx_vol.setColor(sf::Color::White);
        fulscreen_game.setColor(sf::Color::White);
        backFromOptions.setCharacterSize(menu_config.fontSize);
    credits.setColor(sf::Color::White);
    quit.setColor(sf::Color::White);

    game_name.setPosition(320., 25.);

    start.setPosition(menu_config.position[0][1].x, menu_config.position[0][1].y);
        new_game.setPosition(menu_config.position[1][1].x, menu_config.position[1][1].y);
            easy.setPosition(menu_config.position[2][1].x, menu_config.position[2][1].y);
            normal.setPosition(menu_config.position[3][0].x, menu_config.position[3][0].y);
            hard.setPosition(menu_config.position[4][0].x, menu_config.position[4][0].y);
            backFromNewGame.setPosition(menu_config.position[5][0].x, menu_config.position[5][0].y);
        continue_game.setPosition(menu_config.position[6][0].x, menu_config.position[6][0].y);
        backFromStart.setPosition(menu_config.position[7][0].x, menu_config.position[7][0].y);
     options.setPosition(menu_config.position[8][0].x, menu_config.position[8][0].y);
        music_vol.setPosition(menu_config.position[9][1].x, menu_config.position[9][1].y);
        sfx_vol.setPosition(menu_config.position[10][0].x, menu_config.position[10][0].y);
        fulscreen_game.setPosition(menu_config.position[11][0].x, menu_config.position[11][0].y);
        backFromOptions.setPosition(menu_config.position[12][0].x, menu_config.position[12][0].y);
    credits.setPosition(menu_config.position[13][0].x, menu_config.position[13][0].y);
    quit.setPosition(menu_config.position[14][0].x, menu_config.position[14][0].y);

    MenuState menu_state = MenuState::START_GAME;

    // While in MENU state
    while (game_state == GameState::MENU)
    {
        sf::Event event;
        while(gameWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                return GameState::END;

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    return GameState::END;

                if  (menu_state == MenuState::START_GAME)
                {
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        menu_state = MenuState::OPTIONS;
                        start.setColor(sf::Color::White);
                        start.setPosition(menu_config.position[0][0].x, menu_config.position[0][0].y);
                        options.setColor(sf::Color::Cyan);
                        options.setPosition(menu_config.position[8][1].x, menu_config.position[8][1].y);
                    }
                    else if (event.key.code == sf::Keyboard::Space)
                    {
                        menu_state = MenuState::NEW_GAME;
                        start.setColor(sf::Color::White);
                        new_game.setColor(sf::Color::Cyan);
                        new_game.setPosition(menu_config.position[1][1].x, menu_config.position[1][1].y);
                    }
                }
                else if (menu_state == MenuState::NEW_GAME)
                {
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        menu_state = MenuState::CONTINUE;
                        new_game.setColor(sf::Color::White);
                        new_game.setPosition(menu_config.position[1][0].x, menu_config.position[1][0].y);
                        continue_game.setColor(sf::Color::Cyan);
                        continue_game.setPosition(menu_config.position[6][1].x, menu_config.position[6][1].y);
                    }
                    else if (event.key.code == sf::Keyboard::Space)
                    {
                        menu_state = MenuState::EASY;
                        new_game.setColor(sf::Color::White);
                        easy.setColor(sf::Color::Cyan);
                        easy.setPosition(menu_config.position[2][1].x, menu_config.position[2][1].y);
                    }
                }
                else if (menu_state == MenuState::EASY)
                {
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        menu_state = MenuState::NORMAL;
                        easy.setColor(sf::Color::White);
                        easy.setPosition(menu_config.position[2][0].x, menu_config.position[2][0].y);
                        normal.setColor(sf::Color::Cyan);
                        normal.setPosition(menu_config.position[3][1].x, menu_config.position[3][1].y);
                    }
                }
                else if (menu_state == MenuState::NORMAL)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        menu_state = MenuState::EASY;
                        normal.setColor(sf::Color::White);
                        normal.setPosition(menu_config.position[3][0].x, menu_config.position[3][0].y);
                        easy.setColor(sf::Color::Cyan);
                        easy.setPosition(menu_config.position[2][1].x, menu_config.position[2][1].y);
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        menu_state = MenuState::HARD;
                        normal.setColor(sf::Color::White);
                        normal.setPosition(menu_config.position[3][0].x, menu_config.position[3][0].y);
                        hard.setColor(sf::Color::Cyan);
                        hard.setPosition(menu_config.position[4][1].x, menu_config.position[4][1].y);
                    }
                }
                else if (menu_state == MenuState::HARD)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        menu_state = MenuState::NORMAL;
                        hard.setColor(sf::Color::White);
                        hard.setPosition(menu_config.position[4][0].x, menu_config.position[4][0].y);
                        normal.setColor(sf::Color::Cyan);
                        normal.setPosition(menu_config.position[3][1].x, menu_config.position[3][1].y);
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        menu_state = MenuState::BACK_TO_MENU_FROM_NEW_GAME;
                        hard.setColor(sf::Color::White);
                        hard.setPosition(menu_config.position[4][0].x, menu_config.position[4][0].y);
                        backFromNewGame.setColor(sf::Color::Cyan);
                        backFromNewGame.setPosition(menu_config.position[5][1].x, menu_config.position[5][1].y);
                    }
                }
                else if (menu_state == MenuState::BACK_TO_MENU_FROM_NEW_GAME)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        menu_state = MenuState::HARD;
                        backFromNewGame.setColor(sf::Color::White);
                        backFromNewGame.setPosition(menu_config.position[5][0].x, menu_config.position[5][0].y);
                        hard.setColor(sf::Color::Cyan);
                        hard.setPosition(menu_config.position[4][1].x, menu_config.position[4][1].y);
                    }
                    else if (event.key.code == sf::Keyboard::Space)
                    {
                        menu_state = MenuState::START_GAME;
                        backFromNewGame.setColor(sf::Color::White);
                        start.setColor(sf::Color::Cyan);
                        start.setPosition(menu_config.position[0][1].x, menu_config.position[0][1].y);
                        backFromNewGame.setPosition(menu_config.position[5][0].x, menu_config.position[5][0].y);
                    }
                }
                else if (menu_state == MenuState::CONTINUE)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        menu_state = MenuState::NEW_GAME;
                        continue_game.setColor(sf::Color::White);
                        continue_game.setPosition(menu_config.position[6][0].x, menu_config.position[6][0].y);
                        new_game.setColor(sf::Color::Cyan);
                        new_game.setPosition(menu_config.position[1][1].x, menu_config.position[1][1].y);
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        menu_state = MenuState::BACK_TO_MENU_FROM_START_GAME;
                        continue_game.setColor(sf::Color::White);
                        continue_game.setPosition(menu_config.position[6][0].x, menu_config.position[6][0].y);
                        backFromStart.setColor(sf::Color::Cyan);
                        backFromStart.setPosition(menu_config.position[7][1].x, menu_config.position[7][1].y);
                    }
                }
                else if (menu_state == MenuState::BACK_TO_MENU_FROM_START_GAME)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        menu_state = MenuState::CONTINUE;
                        backFromStart.setColor(sf::Color::White);
                        backFromStart.setPosition(menu_config.position[7][0].x, menu_config.position[7][0].y);
                        continue_game.setColor(sf::Color::Cyan);
                        continue_game.setPosition(menu_config.position[6][1].x, menu_config.position[6][1].y);
                    }
                    else if (event.key.code == sf::Keyboard::Space)
                    {
                        menu_state = MenuState::START_GAME;
                        backFromStart.setColor(sf::Color::White);
                        backFromStart.setPosition(menu_config.position[7][0].x, menu_config.position[7][0].y);
                        start.setColor(sf::Color::Cyan);
                        start.setPosition(menu_config.position[0][1].x, menu_config.position[0][1].y);
                    }
                }
                else if (menu_state == MenuState::OPTIONS)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        menu_state = MenuState::START_GAME;
                        start.setColor(sf::Color::Cyan);
                        start.setPosition(menu_config.position[0][1].x, menu_config.position[0][1].y);
                        options.setColor(sf::Color::White);
                        options.setPosition(menu_config.position[8][0].x, menu_config.position[8][0].y);
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        menu_state = MenuState::CREDITS;
                        credits.setColor(sf::Color::Cyan);
                        credits.setPosition(menu_config.position[13][1].x, menu_config.position[13][1].y);
                        options.setColor(sf::Color::White);
                        options.setPosition(menu_config.position[8][0].x, menu_config.position[8][0].y);
                    }
                    else if (event.key.code == sf::Keyboard::Space)
                    {
                        menu_state = MenuState::MUSIC_VOL;
                        options.setColor(sf::Color::White);
                        options.setPosition(menu_config.position[8][0].x, menu_config.position[8][0].y);
                        music_vol.setColor(sf::Color::Cyan);
                        music_vol.setPosition(menu_config.position[9][1].x, menu_config.position[9][1].y);
                    }
                }
                else if (menu_state == MenuState::MUSIC_VOL)
                {
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        menu_state = MenuState::SFX_VOL;
                        music_vol.setColor(sf::Color::White);
                        music_vol.setPosition(menu_config.position[9][0].x, menu_config.position[9][0].y);
                        sfx_vol.setColor(sf::Color::Cyan);
                        sfx_vol.setPosition(menu_config.position[10][1].x, menu_config.position[10][1].y);
                    }
                }
                else if (menu_state == MenuState::SFX_VOL)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        menu_state = MenuState::MUSIC_VOL;
                        sfx_vol.setColor(sf::Color::White);
                        sfx_vol.setPosition(menu_config.position[10][0].x, menu_config.position[10][0].y);
                        music_vol.setColor(sf::Color::Cyan);
                        music_vol.setPosition(menu_config.position[9][1].x, menu_config.position[9][1].y);
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        menu_state = MenuState::FULSCREEN;
                        sfx_vol.setColor(sf::Color::White);
                        sfx_vol.setPosition(menu_config.position[10][0].x, menu_config.position[10][0].y);
                        fulscreen_game.setColor(sf::Color::Cyan);
                        fulscreen_game.setPosition(menu_config.position[11][1].x, menu_config.position[11][1].y);

                    }
                }
                else if (menu_state == MenuState::FULSCREEN)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        menu_state = MenuState::SFX_VOL;
                        fulscreen_game.setColor(sf::Color::White);
                        fulscreen_game.setPosition(menu_config.position[11][0].x, menu_config.position[11][0].y);
                        sfx_vol.setColor(sf::Color::Cyan);
                        sfx_vol.setPosition(menu_config.position[10][1].x, menu_config.position[10][1].y);
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        menu_state = MenuState::BACK_TO_MENU_FROM_OPTIONS;
                        fulscreen_game.setColor(sf::Color::White);
                        fulscreen_game.setPosition(menu_config.position[11][0].x, menu_config.position[11][0].y);
                        backFromOptions.setColor(sf::Color::Cyan);
                        backFromOptions.setPosition(menu_config.position[12][1].x, menu_config.position[12][1].y);
                    }
                }
                else if (menu_state == MenuState::BACK_TO_MENU_FROM_OPTIONS)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        menu_state = MenuState::FULSCREEN;
                        backFromOptions.setColor(sf::Color::White);
                        backFromOptions.setPosition(menu_config.position[12][0].x, menu_config.position[12][0].y);
                        fulscreen_game.setColor(sf::Color::Cyan);
                        fulscreen_game.setPosition(menu_config.position[11][1].x, menu_config.position[11][1].y);
                    }
                    else if (event.key.code == sf::Keyboard::Space)
                    {
                        menu_state = MenuState::START_GAME;
                        backFromOptions.setColor(sf::Color::White);
                        backFromOptions.setPosition(menu_config.position[12][0].x, menu_config.position[12][0].y);
                        start.setColor(sf::Color::Cyan);
                        start.setPosition(menu_config.position[0][1].x, menu_config.position[0][1].y);
                    }
                }
                else if (menu_state == MenuState::CREDITS)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        menu_state = MenuState::OPTIONS;
                        credits.setColor(sf::Color::White);
                        credits.setPosition(menu_config.position[13][0].x, menu_config.position[13][0].y);
                        options.setColor(sf::Color::Cyan);
                        options.setPosition(menu_config.position[8][1].x, menu_config.position[8][1].y);
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        menu_state = MenuState::QUIT;
                        credits.setColor(sf::Color::White);
                        credits.setPosition(menu_config.position[13][0].x, menu_config.position[13][0].y);
                        quit.setColor(sf::Color::Cyan);
                        quit.setPosition(menu_config.position[14][1].x, menu_config.position[14][1].y);
                    }
                }
                else if (menu_state == MenuState::QUIT)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        menu_state = MenuState::CREDITS;
                        quit.setColor(sf::Color::White);
                        quit.setPosition(menu_config.position[14][0].x, menu_config.position[14][0].y);
                        credits.setColor(sf::Color::Cyan);
                        credits.setPosition(menu_config.position[13][1].x, menu_config.position[13][1].y);
                    }
                    else if (event.key.code == sf::Keyboard::Space)
                    {
                        return GameState::END;
                    }
                }
            }

        }

        gameWindow->clear(sf::Color::Transparent);

        gameWindow->draw(game_name);

        if (menu_state == MenuState::START_GAME || menu_state == MenuState::OPTIONS ||
            menu_state == MenuState::CREDITS || menu_state == MenuState::QUIT)
        {
            gameWindow->draw(start);
            gameWindow->draw(options);
            gameWindow->draw(credits);
            gameWindow->draw(quit);
        }
        else if (menu_state == MenuState::NEW_GAME || menu_state == MenuState::CONTINUE ||
                menu_state == MenuState::BACK_TO_MENU_FROM_START_GAME)
        {
            gameWindow->draw(new_game);
            gameWindow->draw(continue_game);
            gameWindow->draw(backFromStart);
        }
        else if (menu_state == MenuState::EASY || menu_state == MenuState::NORMAL ||
                 menu_state == MenuState::HARD || menu_state == MenuState::BACK_TO_MENU_FROM_NEW_GAME)
        {
            gameWindow->draw(easy);
            gameWindow->draw(normal);
            gameWindow->draw(hard);
            gameWindow->draw(backFromNewGame);
        }
        else if (menu_state == MenuState::MUSIC_VOL || menu_state == MenuState::SFX_VOL ||
                 menu_state == MenuState::FULSCREEN ||menu_state == MenuState::BACK_TO_MENU_FROM_OPTIONS)
        {
            gameWindow->draw(music_vol);
            gameWindow->draw(sfx_vol);
            gameWindow->draw(fulscreen_game);
            gameWindow->draw(backFromOptions);
        }

        gameWindow->display();
    }
    return GameState::END; // This event will never take place // TODO: fix it
}

void Game::End()
{
    gameWindow->close();
}
