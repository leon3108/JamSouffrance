#ifndef _HEALTH_
#define _HEALTH_

#include "./IComponent.hpp"

namespace Components
{
    class Health : public IComponent
    {
    private:
        int _hp;
        int _maxHp;
        bool _isHit;
        int _framesCounter;
        int _framesSpeed;

    public:
        Health(int maxHp);
        ~Health();
        int getHp();
        void setHp(int hp);
        void setMaxHp(int maxHp);
        void setIsHit(bool isHit);
        bool IsHit();
        void handleInvicibility(int fps);
        int getFramesCounter();
    };
}

#endif