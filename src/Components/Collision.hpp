#ifndef _COLLISION_
#define _COLLISION_

#include "./IComponent.hpp"
#include <memory>

namespace Components
{
    class Collision : public IComponent
    {
    private:
        Rectangle _collisionRect;
        bool _isColliding;
    public:
        Collision(/* args */);
        ~Collision();
        void setCollisionRect(Rectangle collisionRect);
        Rectangle getCollisionRect();
        void setIsColliding(bool isColliding);
        bool getIsColliding();
        bool checkCollision(std::shared_ptr<Components::Collision> collision);
    };
}

#endif