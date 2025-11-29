#pragma once

#include "Rectangle.h"

namespace GameLogic
{
class ICollidable
{
public:
    virtual ~ICollidable() = default;
    virtual Rectangle getBounds() const = 0;
    virtual bool checkCollision(const ICollidable& other) const = 0;
};
} // namespace GameLogic
