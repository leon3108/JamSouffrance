#ifndef _INPUT_
#define _INPUT_

#include <raylib.h>
#include <iostream>
#include "../Components/IComponent.hpp"
#include "../Factory/ProjectilesFactory.hpp"
#include "../Entity/Projectiles.hpp"
#include "../Entity/Player.hpp"
#include "./ScreenSize.hpp"
#include "./Audio.hpp"
#include "./Keys.hpp"

class Input
{
private:
public:
    Input(/* args */);
    ~Input();
    bool isInRect(Rectangle rect);
    bool isClicked(Rectangle rect);
    bool checkCollisionPointRec(Vector2 point, Rectangle rec);
    bool isMouseButtonPressed(int button);
    void setMouseCursor(int cursor);
    bool isMouseButtonReleased(int button);
    bool isMouseButtonDown(int button);
    bool isKeyPressed(int key);
    bool isKeyDown(int key);
    Vector2 getMousePosition();
    int getCharPressed();
};

#endif