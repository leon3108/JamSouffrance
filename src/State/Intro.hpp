#ifndef _INTRO_
#define _INTRO_

#include <raylib.h>

class Intro
{
private:
    Texture2D _texture;
    int _framesCounter;
    unsigned char _alpha;
public:
    Intro(/* args */);
    ~Intro();
    void incrementFramesCounter();
    int getFramesCounter();
    void incrementAlpha();
    int getAlpha();
    Texture2D getTexture();
    void setIntro();
    void unloadIntro();

};

#endif