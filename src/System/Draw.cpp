#include "./Draw.hpp"

Draw::Draw(/* args */)
{
}

Draw::~Draw()
{
}

void Draw::clearBackground(Color color)
{
    ClearBackground(color);
}

void Draw::beginDrawing()
{
    BeginDrawing();
}

void Draw::endDrawing()
{
    EndDrawing();
}

void Draw::drawRectangle(Vector2 pos, int width, int height, Color color)
{
    DrawRectangle(pos.x, pos.y, width, height, color);
}

void Draw::drawRectangleRec(Rectangle rec, Color color)
{
    DrawRectangleRec(rec, color);
}

void Draw::drawRectangleLines(Vector2 pos, int width, int height, Color color)
{
    DrawRectangleLines(pos.x, pos.y, width, height, color);
}

void Draw::drawText(std::string text, Vector2 pos, int fontSize, Color color)
{
    DrawText(text.c_str(), pos.x, pos.y, fontSize, color);
}

void Draw::drawTexture(Texture2D texture, Vector2 pos, Color tint)
{
    DrawTexture(texture, pos.x, pos.y, tint);
}

void Draw::drawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint)
{
    DrawTextureRec(texture, source, {(float)position.x, (float)position.y}, tint);
}

void Draw::drawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint)
{
    DrawTexturePro(texture, source, dest, origin, rotation, tint);
}

void Draw::drawTextureEx(Texture2D texture, Vector2 pos, float rotation, float scale, Color tint)
{
    DrawTextureEx(texture, pos, rotation, scale, tint);
}