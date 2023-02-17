#include "./Core.hpp"
#include <string> // std::string, std::to_string
#define MAX_INPUT_CHARS 9

#define NUM_FRAMES 3
#define NB_PLAYERS 2

Core::~Core()
{
    closeAudioDevice();
    closeWindow();
}

Core::Core(ScreenSize screenSize, std::string name, int fps)
{
    _screenSize = screenSize;
    setConfigFlags(FLAG_WINDOW_RESIZABLE);
    initWindow(name);
    setFps(fps);
    initAudioDevice();
    SetWindowMinSize(500, 400);
    setWindowSize(_screenSize.width, _screenSize.height);
    // int monitor = getCurrentMonitor();
    // if (!isWindowFullscreen())
    // {
    //     setWindowSize(getMonitorWidth(monitor), getMonitorHeight(monitor));
    //     toggleFullscreen();
    // }
    // if (getMonitorWidth(monitor) > 1920 && getMonitorHeight(monitor) > 1080)
    // {
    //     setWindowSize(1920, 1080);
    //     toggleFullscreen();
    // }

    _playerFactory = std::make_unique<PlayerFactory>();
    _projectileFactory = std::make_unique<ProjectilesFactory>();
    _ennemyFactory = std::make_unique<EnnemyFactory>();
    _cameraFactory = std::make_unique<CameraFactory>();
    _heartFactory = std::make_unique<HeartFactory>();
    _buttonFactory = std::make_unique<ButtonFactory>();
    _backgroundFactory = std::make_unique<BackgroundFactory>();
    _players.push_back(reinterpret_cast<Player *>(_playerFactory->create()));
    _players.at(0)->getObjectComp()->setRefRect({0.0f, 0.0f, (float)_players.at(0)->getObjectComp()->getTexture().width / 5, (float)_players.at(0)->getObjectComp()->getTexture().height / 5});
    _players.at(0)->getPositionComp()->setPosition({400, 400});
    _players.at(0)->setKeys({KEY_Z, KEY_D, KEY_S, KEY_Q});
    _gameState = MENU;
    handleState();
}

void Core::setWindowifResized(void)
{
    if (IsWindowResized()) {

        if (_gameState == GAME) {
            int newWidth = GetScreenWidth(); 
            int newHeight = GetScreenHeight();
            for (auto &player : _players) {
                Vector2 playerPos = player->getPositionComp()->getPosition();
                player->getPositionComp()->setPosition({newWidth * playerPos.x / _screenSize.width, newHeight * playerPos.y / _screenSize.height});
            }

            Vector2 heatPos = _heart->getPositionComp()->getPosition();
            _heart->getPositionComp()->setPosition({newWidth * heatPos.x / _screenSize.width, newHeight * heatPos.y / _screenSize.height});

            for (auto &ennemy : _ennemy) {
                Vector2 ennemyPos = ennemy->getPositionComp()->getPosition();
                ennemy->getPositionComp()->setPosition({newWidth * ennemyPos.x / _screenSize.width, newHeight * ennemyPos.y / _screenSize.height});
                
            }

            for (auto &proj : _projectiles) {
                Vector2 projPos = proj->getPositionComp()->getPosition();
                proj->getPositionComp()->setPosition({newWidth * projPos.x / _screenSize.width, newHeight * projPos.y / _screenSize.height});
            }

            _screenSize = {newWidth, newHeight};
        }
        /* 
            remettre les pos
                assets menus()
        */
    }
}

void Core::intro()
{
    _intro.setIntro();
    while (_gameState == INTRO)
    {
        windowShouldClose();
        setWindowifResized();

        _intro.incrementFramesCounter();

        if (_intro.getFramesCounter() >= (_fps * 5))
            _gameState = MENU;
        if (_intro.getAlpha() < 255)
            _intro.incrementAlpha();

        _draw.beginDrawing();
        _draw.clearBackground(BLACK);
        _draw.drawTexture(_intro.getTexture(), {(float)(getScreenSize().width / 2) - (_intro.getTexture().width / 2), (float)(getScreenSize().height / 2) - (_intro.getTexture().height / 2)}, {255, 255, 255, (unsigned char)(_intro.getAlpha())});
        _draw.endDrawing();
    }
    _intro.unloadIntro();
}

void Core::handleState()
{
    while (1)
    {
        if (_gameState == INTRO)
            intro();
        if (_gameState == MENU)
            menu();
        if (_gameState == GAME)
            game();
        if (_gameState == OPTION)
            option();
        if (_gameState == SPACESHIP_CHOISE)
            spaceShipChoise();
        // if (_gameState == WELCOME_SPACESHIP)
        //     welcomeToYourSpaceship();
        if (_gameState == CLOSE)
            break;
    }
}

void Core::menu()
{
    _welcomeMenu = LoadTexture(BACKGROUND_MENU);
    // _musicMenu = LoadSound(MENU_MUSIC);
    // _audio.playSound(_musicMenu);
    // _audio.setSoundVolume(_musicMenu, 0.3f);
    while (!windowShouldClose() && _gameState == MENU)
    {
        if (_input.isKeyDown(R_TYPE_KEY_E))
            _gameState = GAME;
        if (_input.isKeyDown(R_TYPE_KEY_R))
            _gameState = OPTION;
        if (_input.isKeyDown(R_TYPE_KEY_T))
            _gameState = SPACESHIP_CHOISE;
        // if (_input.isKeyDown(R_TYPE_KEY_V))
        //     _gameState = WELCOME_SPACESHIP;
        windowShouldClose();
        setWindowifResized();
        _draw.beginDrawing();
        _draw.clearBackground(RAYWHITE);
        _draw.drawTexture(_welcomeMenu, {0, 0}, WHITE);
        _draw.drawText("menu\nappuyez sur e pour passer au jeu", {800, 500}, 20, WHITE);
        _draw.drawText("appuyez sur r pour passer aux options", {800, 600}, 20, WHITE);
        _draw.drawText("appuyez sur t pour choisir votre vaisseau", {800, 700}, 20, WHITE);
        // _draw.drawText("appuyez sur v pour passer aux WelcomeTo", {600, 600}, 20, WHITE);
        _draw.endDrawing();
    }
    // _audio.stopSound(_musicMenu);
    unloadTexture(_welcomeMenu);
}

void Core::initSpaceShipChoise()
{
    _btnNext = reinterpret_cast<Button *>(_buttonFactory->create());
    _btnNext->getPositionComp()->setPosition({1525, 900});
    _btnNext->getTextComp()->setText("Next");
    _btnNext->getTextComp()->setRect({1525, 900, 100, 50});

    _btnReturn = reinterpret_cast<Button *>(_buttonFactory->create());
    _btnReturn->getPositionComp()->setPosition({70, 940});
    _btnReturn->getTextComp()->setText("Return");
    _btnReturn->getTextComp()->setRect({70, 940, 100, 50});

    _btnCreate = reinterpret_cast<Button *>(_buttonFactory->create());
    _btnCreate->getPositionComp()->setPosition({1535, 200});
    _btnCreate->getTextComp()->setText("Create");
    _btnCreate->getTextComp()->setRect({1535, 200, 100, 50});

    _btnJoin = reinterpret_cast<Button *>(_buttonFactory->create());
    _btnJoin->getPositionComp()->setPosition({1535, 300});
    _btnJoin->getTextComp()->setText("Join");
    _btnJoin->getTextComp()->setRect({1535, 300, 100, 50});

    _backgroundMenu = reinterpret_cast<Background *>(_backgroundFactory->create());
    _backgroundMenu->getObjectComp()->setTexture("./assets/Menus/GameLobbyWithoutAnything.png");
    _players.at(0)->getPositionComp()->setPosition({130, 650});
    _players.at(0)->getObjectComp()->setTexture("./assets/GamePlay/spaceship/r-typesheet42.png");
    _spaceShipColorIndex = 0;
    _players.at(0)->getObjectComp()->setRefRect({0.0f, 0.0f, (float)_players.at(0)->getObjectComp()->getTexture().width / 5, (float)_players.at(0)->getObjectComp()->getTexture().height / 5});
}

void Core::inputSpaceShipChoise()
{
    if (_input.isKeyPressed(R_TYPE_KEY_D) && _spaceShipColorIndex + 1 < 5)
    {
        _spaceShipColorIndex = _spaceShipColorIndex + 1;
        _players.at(0)->getObjectComp()->setRefRect({_players.at(0)->getObjectComp()->getRefRect().x, _players.at(0)->getObjectComp()->getRefRect().height * _spaceShipColorIndex, _players.at(0)->getObjectComp()->getRefRect().width, _players.at(0)->getObjectComp()->getRefRect().height});
    }
    if (_input.isKeyPressed(R_TYPE_KEY_Q) && _spaceShipColorIndex - 1 > -1)
    {
        _spaceShipColorIndex = _spaceShipColorIndex - 1;
        _players.at(0)->getObjectComp()->setRefRect({_players.at(0)->getObjectComp()->getRefRect().x, _players.at(0)->getObjectComp()->getRefRect().height * _spaceShipColorIndex, _players.at(0)->getObjectComp()->getRefRect().width, _players.at(0)->getObjectComp()->getRefRect().height});
    }

    if (_input.isInRect(_btnNext->getTextComp()->getRect()))
    {
        _btnNext->getTextComp()->setColor(GREEN);
        if (_input.isClicked(_btnNext->getTextComp()->getRect()))
            _gameState = GAME;
    }
    else
        _btnNext->getTextComp()->setColor(RED);

    if (_input.isInRect(_btnReturn->getTextComp()->getRect()))
    {
        _btnReturn->getTextComp()->setColor(GREEN);
        if (_input.isClicked(_btnReturn->getTextComp()->getRect()))
            _gameState = MENU;
    }
    else
        _btnReturn->getTextComp()->setColor(RED);

    if (_input.isInRect(_btnCreate->getTextComp()->getRect()))
        _btnCreate->getTextComp()->setColor(GREEN);
    else
        _btnCreate->getTextComp()->setColor(RED);
    if (_input.isInRect(_btnJoin->getTextComp()->getRect()))
        _btnJoin->getTextComp()->setColor(GREEN);
    else
        _btnJoin->getTextComp()->setColor(RED);
}

void Core::spaceShipChoise()
{
    initSpaceShipChoise();

    while (_gameState == SPACESHIP_CHOISE)
    {
        windowShouldClose();
        setWindowifResized();
        inputSpaceShipChoise();
        drawSpaceShipChoise();
    }
}

void Core::drawSpaceShipChoise()
{
    _draw.beginDrawing();
    _draw.clearBackground(RAYWHITE);
    _draw.drawTexture(_backgroundMenu->getObjectComp()->getTexture(), {0, 0}, WHITE);
    _draw.drawText(_btnNext->getTextComp()->getText(), _btnNext->getPositionComp()->getPosition(), _btnNext->getTextComp()->getSize(), _btnNext->getTextComp()->getColor());
    _draw.drawText(_btnReturn->getTextComp()->getText(), _btnReturn->getPositionComp()->getPosition(), _btnReturn->getTextComp()->getSize(), _btnReturn->getTextComp()->getColor());
    _draw.drawText(_btnCreate->getTextComp()->getText(), _btnCreate->getPositionComp()->getPosition(), _btnCreate->getTextComp()->getSize(), _btnCreate->getTextComp()->getColor());
    _draw.drawText(_btnJoin->getTextComp()->getText(), _btnJoin->getPositionComp()->getPosition(), _btnJoin->getTextComp()->getSize(), _btnJoin->getTextComp()->getColor());
    _draw.drawText("appuyez sur Q/D pour passer au vaisseau suivant", {550, 150}, 20, RED);
    _draw.drawTexturePro(_players.at(0)->getObjectComp()->getTexture(), _players.at(0)->getObjectComp()->getRefRect(), {(float)_players.at(0)->getPositionComp()->getPosition().x, (float)_players.at(0)->getPositionComp()->getPosition().y, 200, 200}, {0, 0}, 0.0f, WHITE);
    _draw.endDrawing();
}

void Core::option()
{
    while (_gameState == OPTION)
    {
        windowShouldClose();
        setWindowifResized();
        if (_input.isKeyPressed(R_TYPE_KEY_O))
            setFps(_fps - 1);
        if (_input.isKeyPressed(R_TYPE_KEY_P))
            setFps(_fps + 1);
        _draw.beginDrawing();
        _draw.clearBackground(RAYWHITE);
        _draw.drawText("appuyez sur o pour diminuer les fps", {600, 300}, 20, RED);
        _draw.drawText("appuyez sur p pour augmenter les fps", {600, 400}, 20, RED);
        _draw.drawText(std::to_string(_fps), {200, 300}, 20, RED);
        _draw.endDrawing();
    }
}

void Core::initGame()
{
    _audio.loadShotSound("./assets/sound/Blaster.ogg");

    _ennemy.push_back(reinterpret_cast<Ennemy *>(_ennemyFactory->create()));
    _camera = reinterpret_cast<rTypeCamera *>(_cameraFactory->create());
    _heart = reinterpret_cast<Heart *>(_heartFactory->create());
    _background = reinterpret_cast<Background *>(_backgroundFactory->create());

    _ennemy.at(0)->getObjectComp()->setRefRect({0.0f, 0.0f, (float)_ennemy.at(0)->getObjectComp()->getTexture().width / 8, (float)_ennemy.at(0)->getObjectComp()->getTexture().height / 2});
    _ennemy.at(0)->getCollisionComp()->setCollisionRect(_ennemy.at(0)->getObjectComp()->getRect());
    
    _players.at(0)->getObjectComp()->setRefRect({0.0f, 0.0f, (float)_players.at(0)->getObjectComp()->getTexture().width / 5, (float)_players.at(0)->getObjectComp()->getTexture().height / 5});
    _players.at(0)->getPositionComp()->setPosition({400, 400});
    // _players.at(0)->setUuid(_client.connect());
    _scrollingBack = 0.0f;
    // _data.id = 1;
}

void Core::inputGame()
{
    if (_input.isKeyDown(_players.at(0)->getKeys().key_up) && _players.at(0)->getPositionComp()->getPosition().y - _players.at(0)->getMovementsComp()->getSpeed() >= 0)
        _players.at(0)->getMovementsComp()->move(_players.at(0)->getPositionComp(), UP);
    if (_input.isKeyDown(_players.at(0)->getKeys().key_right) && _players.at(0)->getPositionComp()->getPosition().x + _players.at(0)->getMovementsComp()->getSpeed() <= _screenSize.width - _players.at(0)->getObjectComp()->getRect().width)
        _players.at(0)->getMovementsComp()->move(_players.at(0)->getPositionComp(), RIGHT);
    if (_input.isKeyDown(_players.at(0)->getKeys().key_down) && _players.at(0)->getPositionComp()->getPosition().y + _players.at(0)->getMovementsComp()->getSpeed() + _players.at(0)->getObjectComp()->getRect().height < _screenSize.height)
        _players.at(0)->getMovementsComp()->move(_players.at(0)->getPositionComp(), DOWN);
    if (_input.isKeyDown(_players.at(0)->getKeys().key_left) && _players.at(0)->getPositionComp()->getPosition().x - _players.at(0)->getMovementsComp()->getSpeed() >= 0)
        _players.at(0)->getMovementsComp()->move(_players.at(0)->getPositionComp(), LEFT);
    if (_input.isMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        _audio.playSoundMulti(_audio.getShot());
        _projectiles.push_back(reinterpret_cast<Projectiles *>(_projectileFactory->create()));
        _projectiles.at(_projectiles.size() - 1)->getPositionComp()->setPosition({_players.at(0)->getPositionComp()->getPosition().x, _players.at(0)->getPositionComp()->getPosition().y});
    }
}

void Core::game()
{
    initGame();
    // _client.receive();
    while (_gameState == GAME)
    {
        // try
        // {
            // _dataReceived = _client.getData();
        //     for (std::size_t i = 0; i < _dataReceived.size(); i++)
        //     {
        //         bool isNewPlayer = true;
        //         for (auto &player : _players) {
        //             if (_dataReceived.at(i).uuid == player->getUuid()) {
        //                 player->getPositionComp()->setPosition({(float)_dataReceived.at(i).playerPosX, (float)_dataReceived.at(i).playerPosY});
        //                 isNewPlayer = false;
        //             }
        //         }
        //         if (isNewPlayer == true) {
        //             _players.push_back(reinterpret_cast<Player *>(_playerFactory->create()));
        //             _players.at(_players.size() - 1)->setUuid(_dataReceived.at(i).uuid);
        //             _players.at(_players.size() - 1)->getObjectComp()->setRefRect({0.0f, 0.0f, (float)_players.at(_players.size() - 1)->getObjectComp()->getTexture().width / 5, (float)_players.at(_players.size() - 1)->getObjectComp()->getTexture().height / 5});
        //             _players.at(_players.size() - 1)->getPositionComp()->setPosition({400, 400 + (100 * (float)i)});
        //         }
        //     }
        //     _client.clearData();
        // }
        // catch (std::exception &e)
        // {
        //     throw(e.what());
        // }

        windowShouldClose();
        setWindowifResized();
        _players.at(0)->getAnimationComp()->animate(_fps, _players.at(0)->getObjectComp());
        _players.at(0)->getCollisionComp()->setCollisionRect({(float)_players.at(0)->getPositionComp()->getPosition().x,
                                                              (float)_players.at(0)->getPositionComp()->getPosition().y,
                                                              _players.at(0)->getCollisionComp()->getCollisionRect().width,
                                                              _players.at(0)->getCollisionComp()->getCollisionRect().height});

        for (std::size_t j = 0; j < _ennemy.size(); j++)
        {
            _ennemy.at(j)->getAnimationComp()->animate(_fps, _ennemy.at(j)->getObjectComp());
            _ennemy.at(j)->getAiComp()->play(_ennemy.at(j)->getPositionComp(), _ennemy.at(j)->getMovementsComp(), _ennemy.at(j)->getAnimationComp(), _fps);
            _ennemy.at(j)->getCollisionComp()->setCollisionRect({(float)_ennemy.at(j)->getPositionComp()->getPosition().x,
                                                                 (float)_ennemy.at(j)->getPositionComp()->getPosition().y,
                                                                 _ennemy.at(j)->getCollisionComp()->getCollisionRect().width,
                                                                 _ennemy.at(j)->getCollisionComp()->getCollisionRect().height});
        }

        _scrollingBack -= 0.8f;
        if (_scrollingBack <= -_background->getObjectComp()->getTexture().width * 2)
            _scrollingBack = 0;

        for (std::size_t i = 0; i < _projectiles.size(); i++)
        {
            _projectiles.at(i)->getMovementsComp()->move(_projectiles.at(i)->getPositionComp(), RIGHT);
            _projectiles.at(i)->getAnimationComp()->animate(_fps, _projectiles.at(i)->getObjectComp());
            _projectiles.at(i)->getCollisionComp()->setCollisionRect({(float)_projectiles.at(i)->getPositionComp()->getPosition().x,
                                                                      (float)_projectiles.at(i)->getPositionComp()->getPosition().y,
                                                                      _projectiles.at(i)->getCollisionComp()->getCollisionRect().width,
                                                                      _projectiles.at(i)->getCollisionComp()->getCollisionRect().height});
            for (std::size_t j = 0; j < _ennemy.size(); j++)
            {
                if (_projectiles.at(i)->getCollisionComp()->checkCollision(_ennemy.at(j)->getCollisionComp()))
                {
                    _ennemy.erase(_ennemy.begin() + j);
                    _projectiles.erase(_projectiles.begin() + i);
                }
            }
        }

        if (!_players.at(0)->getHealthComp()->IsHit())
        {
            for (std::size_t j = 0; j < _ennemy.size(); j++)
            {
                if (_ennemy.at(j)->getCollisionComp()->checkCollision(_players.at(0)->getCollisionComp()))
                {
                    _players.at(0)->getHealthComp()->setHp(_players.at(0)->getHealthComp()->getHp() - 1);
                    _players.at(0)->getHealthComp()->setIsHit(true);
                }
            }
        }

        _players.at(0)->getHealthComp()->handleInvicibility(_fps);

        inputGame();
        // for (auto &player : _players) {
        //     _data.uuid = player->getUuid();
        //     _data.playerPosX = player->getPositionComp()->getPosition().x;
        //     _data.playerPosY = player->getPositionComp()->getPosition().y;
        //     _client.send(_data);
        // }
        deleteProjectiles(_projectiles);
        drawGame();
        // _client.poll();
    }
    unloadGame();
}

void Core::drawGame()
{
    _draw.beginDrawing();
    _draw.clearBackground(BLACK);
    beginMode2d(_camera->getCameraComp()->getCamera2d());

    _draw.drawTextureEx(_background->getObjectComp()->getTexture(), {_scrollingBack, 0}, 0.0, 2.0f, WHITE);

    for (int i = 0; i < _players.at(0)->getHealthComp()->getHp(); i++)
        _draw.drawTexture(_heart->getObjectComp()->getTexture(), 
        {_heart->getPositionComp()->getPosition().x + (100 * i), _heart->getPositionComp()->getPosition().y},
         WHITE);


    for (std::size_t i = 0; i < _projectiles.size(); i++)
        _draw.drawTextureRec(_projectiles.at(i)->getObjectComp()->getTexture(), _projectiles.at(i)->getObjectComp()->getRect(), _projectiles.at(i)->getPositionComp()->getPosition(), WHITE);
    for (std::size_t i = 0; i < _ennemy.size(); i++)
        _draw.drawTextureRec(_ennemy.at(i)->getObjectComp()->getTexture(), _ennemy.at(i)->getObjectComp()->getRect(), _ennemy.at(i)->getPositionComp()->getPosition(), WHITE);
    for (std::size_t i = 0; i < _players.size(); i++) {
        if (!_players.at(i)->getHealthComp()->IsHit())
            _draw.drawTextureRec(_players.at(i)->getObjectComp()->getTexture(), _players.at(i)->getObjectComp()->getRect(), _players.at(i)->getPositionComp()->getPosition(), WHITE);
        else if (_players.at(i)->getHealthComp()->IsHit() && _players.at(i)->getHealthComp()->getFramesCounter() % 10 <= 5)
            _draw.drawTextureRec(_players.at(i)->getObjectComp()->getTexture(), _players.at(i)->getObjectComp()->getRect(), _players.at(i)->getPositionComp()->getPosition(), WHITE);
    }

    endMode2d();
    _draw.endDrawing();
}

void Core::unloadGame()
{
    for (std::size_t i = 0; i < _projectiles.size(); i++)
        _projectiles.at(i)->getObjectComp()->unloadTexture();
    for (std::size_t i = 0; i < _ennemy.size(); i++)
        unloadTexture(_ennemy.at(i)->getObjectComp()->getTexture());
    unloadTexture(_heart->getObjectComp()->getTexture());
    unloadTexture(_players.at(0)->getObjectComp()->getTexture());

    _audio.unloadShotSound();
}

void Core::deleteProjectiles(std::vector<Projectiles *> &projectiles)
{
    for (std::size_t i = 0; i < projectiles.size(); i++)
    {
        if (projectiles.at(i)->getPositionComp()->getPosition().x >= _screenSize.width || projectiles.at(i)->getPositionComp()->getPosition().y >= _screenSize.height)
        {
            projectiles.at(i)->getObjectComp()->unloadTexture();
            projectiles.erase(projectiles.begin() + i);
        }
    }
}

void Core::setFps(int fps)
{
    _fps = fps;
    SetTargetFPS(_fps);
};

bool Core::windowShouldClose()
{
    if (WindowShouldClose())
        _gameState = CLOSE;
    return WindowShouldClose();
}

ScreenSize Core::getScreenSize()
{
    return _screenSize;
}

void Core::closeWindow()
{
    CloseWindow();
}

void Core::loadTexture(std::string imagePath)
{
    LoadTexture(imagePath.c_str());
}

void Core::unloadTexture(Texture2D texture)
{
    UnloadTexture(texture);
}

void Core::closeAudioDevice()
{
    CloseAudioDevice();
}

void Core::endMode2d()
{
    EndMode2D();
}

void Core::initAudioDevice()
{
    InitAudioDevice();
}

void Core::beginMode2d(Camera2D &camera)
{
    BeginMode2D(camera);
}

int Core::getMonitorHeight(int monitor)
{
    return GetMonitorHeight(monitor);
}

int Core::getMonitorWidth(int monitor)
{
    return GetMonitorWidth(monitor);
}

void Core::setWindowSize(int width, int height)
{
    SetWindowSize(width, height);
}

bool Core::isWindowFullscreen()
{
    return IsWindowFullscreen();
}

int Core::getCurrentMonitor()
{
    return GetCurrentMonitor();
}

void Core::initWindow(std::string name)
{
    InitWindow(_screenSize.width, _screenSize.height, name.c_str());
}

void Core::setConfigFlags(ConfigFlags configFlags)
{
    SetConfigFlags(configFlags);
}

void Core::toggleFullscreen()
{
    ToggleFullscreen();
}

// void Core::createMenuButton(float x, float y)
// {
//     Sound fxButton = LoadSound("./assets/buttonfx.wav");           // Load button sound
//     Texture2D button = LoadTexture("./assets/Buttons/button.png"); // Load button texture
//     float frameHeight = (float)button.height / NUM_FRAMES;
//     // Define frame rectangle for drawing

//     Rectangle sourceRec = {0, 0, (float)button.width, frameHeight};
//     Rectangle btnBounds = {x, y, (float)button.width, frameHeight};
//     int btnState = 0; // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
//     bool btnAction = false;
//     bool nextScreen = false;
//     Vector2 mousePoint = {0.0f, 0.0f};
//     mousePoint = _input.getMousePosition();

//     // Check button state
//     if (_input.checkCollisionPointRec(mousePoint, btnBounds))
//     {
//         if (_input.isMouseButtonDown(MOUSE_BUTTON_LEFT))
//             btnState = 2;
//         else
//             btnState = 1;

//         if (_input.isMouseButtonReleased(MOUSE_BUTTON_LEFT))
//         {
//             btnAction = true;
//             nextScreen = true;
//         }
//     }
//     else
//         btnState = 0;
//     if (btnAction)
//         PlaySound(fxButton);

//     if (nextScreen)
//     {
//         _gameState = MENU_SERVER_CONNECTION;
//         serveurConnection();
//     }

//     sourceRec.y = btnState * frameHeight;
//     DrawTextureRec(button, sourceRec, {btnBounds.x, btnBounds.y}, WHITE);
// }

// void Core::welcomeToYourSpaceship()
// {
//     _welcomeToYourSpaceshipMenu = LoadTexture("./assets/Menus/WTYS.png");

//     while (!windowShouldClose() && _gameState == WELCOME_SPACESHIP)
//     {
//         _draw.beginDrawing();
//         _draw.clearBackground(RAYWHITE);
//         _draw.drawTexture(_welcomeToYourSpaceshipMenu, {0, 0}, WHITE);
//         createMenuButton(500, 775);
//         _draw.endDrawing();
//     }
// }

// void Core::serveurConnection()
// {
//     int letterCountServerIp = 0;
//     int letterCountUsername = 0;
//     char Username[MAX_INPUT_CHARS + 1] = "\0";
//     char ServerIp[MAX_INPUT_CHARS + 1] = "\0";

//     Rectangle UsernameBox = {300, 500, 500, 50};
//     Rectangle ServerIpBox = {300, 870, 600, 50};
//     bool mouseOnTexUsernameBox = false;
//     bool mouseOnServerIpBox = false;
//     _serveurConnection = LoadTexture("./assets/Menus/ServeurConnectionBg-2.png");

//     while (!windowShouldClose() && _gameState == MENU_SERVER_CONNECTION)
//     {
//         _draw.beginDrawing();
//         _draw.drawTexture(_serveurConnection, {-350, -100}, WHITE);

//         // USERNAME
//         if (_input.checkCollisionPointRec(_input.getMousePosition(), UsernameBox))
//             mouseOnTexUsernameBox = true;
//         else
//             mouseOnTexUsernameBox = false;

//         // ServerIP
//         if (_input.checkCollisionPointRec(_input.getMousePosition(), ServerIpBox))
//             mouseOnServerIpBox = true;
//         else
//             mouseOnServerIpBox = false;

//         if (mouseOnServerIpBox)
//         {
//             _input.setMouseCursor(MOUSE_CURSOR_IBEAM);
//             int key = _input.getCharPressed();
//             while (key > 0)
//             {
//                 if ((key >= 32) && (key <= 125) && (letterCountServerIp < MAX_INPUT_CHARS))
//                 {
//                     ServerIp[letterCountServerIp] = (char)key;
//                     ServerIp[letterCountServerIp + 1] = '\0';
//                     letterCountServerIp++;
//                 }
//                 key = _input.getCharPressed();
//             }
//             if (_input.isKeyPressed(KEY_BACKSPACE))
//             {
//                 letterCountServerIp--;

//                 if (letterCountServerIp < 0)
//                     letterCountServerIp = 0;
//                 ServerIp[letterCountServerIp] = '\0';
//             }
//         }
//         else
//             _input.setMouseCursor(MOUSE_CURSOR_DEFAULT);

//         if (mouseOnTexUsernameBox)
//         {
//             _input.setMouseCursor(MOUSE_CURSOR_IBEAM);
//             int key = GetCharPressed();
//             while (key > 0)
//             {
//                 if ((key >= 32) && (key <= 125) && (letterCountUsername < MAX_INPUT_CHARS))
//                 {
//                     Username[letterCountUsername] = (char)key;
//                     Username[letterCountUsername + 1] = '\0';
//                     letterCountUsername++;
//                 }
//                 key = _input.getCharPressed();
//             }
//             if (_input.isKeyPressed(KEY_BACKSPACE))
//             {
//                 letterCountUsername--;

//                 if (letterCountUsername < 0)
//                     letterCountUsername = 0;
//                 Username[letterCountUsername] = '\0';
//             }
//         }
//         else
//             _input.setMouseCursor(MOUSE_CURSOR_DEFAULT);

//         _draw.clearBackground(RAYWHITE);

//         _draw.drawRectangleRec(UsernameBox, BLUE);
//         _draw.drawRectangleRec(ServerIpBox, BLUE);

//         if (mouseOnServerIpBox)
//             _draw.drawRectangleLines({(int)ServerIpBox.x, (int)ServerIpBox.y}, (int)ServerIpBox.width, (int)ServerIpBox.height, YELLOW);
//         else
//             _draw.drawRectangleLines({(int)ServerIpBox.x, (int)ServerIpBox.y}, (int)ServerIpBox.width, (int)ServerIpBox.height, DARKBLUE);

//         if (mouseOnTexUsernameBox)
//             _draw.drawRectangleLines({(int)UsernameBox.x, (int)UsernameBox.y}, (int)UsernameBox.width, (int)UsernameBox.height, YELLOW);
//         else
//             _draw.drawRectangleLines({(int)UsernameBox.x, (int)UsernameBox.y}, (int)UsernameBox.width, (int)UsernameBox.height, DARKBLUE);

//         _draw.drawText(Username, {(int)UsernameBox.x + 5, (int)UsernameBox.y + 8}, 40, WHITE);
//         _draw.drawText(ServerIp, {(int)ServerIpBox.x + 5, (int)ServerIpBox.y + 8}, 40, WHITE);

//         _draw.endDrawing();
//     }
// }