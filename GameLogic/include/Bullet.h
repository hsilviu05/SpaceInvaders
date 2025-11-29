#pragma once

#include "Entity.h"

namespace GameLogic
{
class Bullet : public Entity
{
public:
    Bullet(Vector2D position, Vector2D size);

    void moveUp(float deltaTime);
    void update(float deltaTime) override;

    float getSpeed() const;
    void setSpeed(float speed);

private:
    float m_speed;
};
} // namespace GameLogic
