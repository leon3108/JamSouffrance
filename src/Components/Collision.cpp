#include "./Collision.hpp"

Components::Collision::Collision(/* args */)
{
    _componentType = COLLISION;
    _collisionRect = {0, 0, 0, 0};
}

Components::Collision::~Collision()
{
}

void Components::Collision::setCollisionRect(Rectangle collisionRect)
{
    _collisionRect = collisionRect;
}

Rectangle Components::Collision::getCollisionRect()
{
    return _collisionRect;
}

void Components::Collision::setIsColliding(bool isColliding)
{
    _isColliding = isColliding;
}

bool Components::Collision::getIsColliding()
{
    return _isColliding;
}

bool Components::Collision::checkCollision(std::shared_ptr<Components::Collision> collision)
{
    return CheckCollisionRecs(_collisionRect, collision->getCollisionRect());
}