#include "./Input.hpp"
#include "../Factory/ProjectilesFactory.hpp"

Input::Input(/* args */)
{
}

Input::~Input()
{
}

bool Input::isKeyPressed(int key)
{
    return IsKeyPressed(key);
}

void Input::setMouseCursor(int cursor)
{
    SetMouseCursor(cursor);
}

bool Input::isMouseButtonReleased(int button)
{
    return IsMouseButtonReleased(button);
}

bool Input::isMouseButtonDown(int button)
{
    return IsMouseButtonDown(button);
}

bool Input::isKeyDown(int key)
{
    return IsKeyDown(key);
}

bool Input::checkCollisionPointRec(Vector2 point, Rectangle rec)
{
    return CheckCollisionPointRec(point, rec);
}

Vector2 Input::getMousePosition()
{
    return GetMousePosition();   
}

bool Input::isMouseButtonPressed(int button)
{
    return IsMouseButtonPressed(button);
}

bool Input::isInRect(Rectangle rect)
{
    if (checkCollisionPointRec(getMousePosition(), rect))
        return true;
    return false;
}

bool Input::isClicked(Rectangle rect)
{
    if (checkCollisionPointRec(getMousePosition(), rect) && isMouseButtonPressed(R_TYPE_MOUSE_LEFT))
        return true;
    return false;
}

int Input::getCharPressed()
{
    return (GetCharPressed());
}
