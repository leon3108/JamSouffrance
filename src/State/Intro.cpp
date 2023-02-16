#include "./Intro.hpp"

#include <iostream>

Intro::Intro(/* args */)
{
}

Intro::~Intro()
{
}

void Intro::incrementFramesCounter()
{
    _framesCounter ++;
}

int Intro::getFramesCounter()
{
    return _framesCounter;
}

void Intro::incrementAlpha()
{
    _alpha ++;
}

int Intro::getAlpha()
{
    return _alpha;
}

Texture2D Intro::getTexture()
{
    return _texture;
}

void Intro::setIntro()
{
    _texture = LoadTexture("./assets/Intro/R-Type_Logo.png");
    _framesCounter = 0;
    _alpha = 20;

}

void Intro::unloadIntro()
{
    UnloadTexture(_texture);
}