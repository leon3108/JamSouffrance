#ifndef _CORE_
#define _CORE_

#include <string>
#include <raylib.h>
#include <vector>
#include <memory>
#include "./Draw.hpp"
#include "./Input.hpp"
#include "../Entity/Player.hpp"
#include "./ScreenSize.hpp"
#include "./Audio.hpp"
#include "../Factory/PlayerFactory.hpp"
#include "../Factory/ProjectilesFactory.hpp"
#include "../Factory/EnnemyFactory.hpp"
#include "../Factory/CameraFactory.hpp"
#include "../Factory/HeartFactory.hpp"
#include "../Factory/ButtonFactory.hpp"
#include "../Factory/BackgroundFactory.hpp"
#include "../Components/CameraComp.hpp"
#include "../Components/Ai.hpp"
#include "../Components/Health.hpp"
#include "../Components/Collision.hpp"
#include "../State/Intro.hpp"
// #include "../Network/client.hpp"

#define BACKGROUND_MENU "./assets/Menus/WelcomeBg.png"
#define BACKGROUND_GAME "./assets/GamePlay/background/Stars.png"
#define MENU_MUSIC "./assets/sound/SpaceEngineers-Solar_Wind.ogg"

enum gameState
{
    INTRO,
    CLOSE,
    MENU,
    OPTION,
    WELCOME_SPACESHIP,
    MENU_SERVER_CONNECTION,
    SPACESHIP_CHOISE,
    GAME,
};

class Core
{
private:
    // UdpClient _client;
    Intro _intro;
    ScreenSize _screenSize;
    int _fps;
    std::string _name;
    Draw _draw;
    Input _input;
    Audio _audio;
    gameState _gameState;
    Button *_btnNext;
    Button *_btnReturn;
    Button *_btnCreate;
    Button *_btnJoin;
    Background *_backgroundMenu;
    std::unique_ptr<Factory> _playerFactory;
    std::unique_ptr<Factory> _projectileFactory;
    std::unique_ptr<Factory> _ennemyFactory;
    std::unique_ptr<Factory> _cameraFactory;
    std::unique_ptr<Factory> _heartFactory;
    std::unique_ptr<Factory> _buttonFactory;
    std::unique_ptr<Factory> _backgroundFactory;
    std::vector<Ennemy *> _ennemy;
    rTypeCamera *_camera;
    std::vector<Projectiles *> _projectiles;
    Heart *_heart;
    Background *_background;
    float _scrollingBack;
    Sound _musicMenu;
    Texture2D _welcomeMenu;
    Texture2D _gameScreen;
    // Data _data;
    // std::vector<Data> _dataReceived;
    int _spaceShipColorIndex;
    // Texture2D _welcomeToYourSpaceshipMenu;
    // Texture2D _serveurConnection;
    // Texture2D _serveurConnectionButton;

protected:
    std::vector<Player *> _players;

public:
    ~Core();
    Core(ScreenSize screenSize, std::string name, int fps);
    void intro();
    void menu();
    void initGame();
    void game();
    void inputGame();
    void drawGame();
    void unloadGame();
    void option();
    void spaceShipChoise();
    void handleState();
    void drawSpaceShipChoise();
    void initSpaceShipChoise();
    void inputSpaceShipChoise();
    void deleteProjectiles(std::vector<Projectiles *> &projectiles);

    void beginMode2d(Camera2D &camera);
    void endMode2d();
    
    void setFps(int fps);
    
    void initWindow(std::string name);
    void initAudioDevice();
    void setConfigFlags(ConfigFlags configFlags);
    void closeWindow();
    void closeAudioDevice();
    bool windowShouldClose();
    
    void loadTexture(std::string imagePath);
    void unloadTexture(Texture2D texture);

    bool isWindowFullscreen();
    void setWindowSize(int width, int height);
    
    ScreenSize getScreenSize();
    int getCurrentMonitor();
    int getMonitorWidth(int monitor);
    int getMonitorHeight(int monitor);
    
    void toggleFullscreen();
    void setWindowifResized(void);
    // void welcomeToYourSpaceship();
    // void createMenuButton(float x, float y);
    // void serveurConnection();

};

#endif