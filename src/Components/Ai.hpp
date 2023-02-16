#ifndef _AI_
#define _AI_

#include "./IComponent.hpp"
#include "./Position.hpp"
#include "./Movements.hpp"
#include "./Animation.hpp"

namespace Components
{
    class Ai : public IComponent
    {
    private:
        Direction _direction;
        int _framesCounter;
        int _framesSpeed;
    public:
        Ai(int framesSpeed);
        ~Ai();
        void play(std::shared_ptr<Components::Position> pos, std::shared_ptr<Components::Movements> movement, std::shared_ptr<Components::Animation> animation, int fps);
    };
}

#endif