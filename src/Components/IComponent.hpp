#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include "raylib.h"
#include <string>

enum ComponentTypes
{
    AI,
    ANIMATION,
    CAMERACOMP,
    COLLISION,
    HEALTH,
    MOVEMENTS,
    OBJECT,
    POSITION,
    TEXT,
};

namespace Components
{
    class IComponent
    {
    protected:
        enum ComponentTypes _componentType;

    public:
        enum ComponentTypes getComponentType() const { return _componentType; };
    };
}

#endif