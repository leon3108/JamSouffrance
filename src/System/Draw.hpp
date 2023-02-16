#ifndef _DRAW_
#define _DRAW_

#include "raylib.h"
#include <string>

class Draw
{
private:
    /* data */
public:
    Draw(/* args */);
    ~Draw();
    void clearBackground(Color color);
    void beginDrawing();
    void endDrawing();
    void drawRectangle(Vector2 pos, int width, int height, Color color);
    void drawRectangleRec(Rectangle rec, Color color);
    void drawRectangleLines(Vector2 pos, int width, int height, Color color);
    void drawText(std::string text, Vector2 pos, int fontSize, Color color);
    void drawTexture(Texture2D texture, Vector2 pos, Color tint);
    void drawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint);
    void drawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);
    void drawTextureEx(Texture2D texture, Vector2 pos,float rotation, float scale, Color tint);
};

#endif