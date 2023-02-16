#include "./Health.hpp"

Components::Health::Health(int maxHp)
{
    _componentType = HEALTH;
    _maxHp = maxHp;
    _hp = _maxHp;
    _isHit = false;
    _framesCounter = 0;
    _framesSpeed = 10;
}

Components::Health::~Health()
{
}

int Components::Health::getHp()
{
    return _hp;
}

void Components::Health::setHp(int hp)
{
    if (hp >= 0)
        _hp = hp;
}

void Components::Health::setMaxHp(int maxHp)
{
    _maxHp -= maxHp;
}

void Components::Health::setIsHit(bool isHit)
{
    _isHit = isHit;
}

bool Components::Health::IsHit()
{
    return _isHit;
}

int Components::Health::getFramesCounter()
{
    return _framesCounter;
}

void Components::Health::handleInvicibility(int fps)
{
    if (_isHit) {
        _framesCounter++;
        if( _framesCounter >= (fps / _framesSpeed) * 10)
            _isHit = false;
    } else 
        _framesCounter = 0;
}