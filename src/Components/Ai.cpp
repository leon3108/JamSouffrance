#include "./Ai.hpp"

Components::Ai::Ai(int framesSpeed)
{
    _componentType = AI;
    _direction = LEFT;
    _framesCounter = 0;
    _framesSpeed = framesSpeed;
}

Components::Ai::~Ai()
{
}

void Components::Ai::play(std::shared_ptr<Components::Position> pos, std::shared_ptr<Components::Movements> movement, std::shared_ptr<Components::Animation> animation, int fps)
{

    _framesCounter++;
    if (_framesCounter >= (fps / _framesSpeed))
    {
        _framesCounter = 0;

        if (pos->getPosition().x < 1000)
            _direction = RIGHT;
        else if (pos->getPosition().x > 1600) //mettre la taille de l'écran - genre 1/10 de la taille de l'écran
            _direction = LEFT;
        movement->move(pos, _direction);
    }


}