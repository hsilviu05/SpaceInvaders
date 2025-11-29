#pragma once

#include "Entity.h"

namespace GameLogic
{
class Player : public Entity
{
public:
    Player(Vector2D position, Vector2D size);

    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void update(float deltaTime) override;

    bool canShoot() const noexcept;
    void shoot();
    void resetShootCooldown();

    float getSpeed() const noexcept;
    void setSpeed(float speed);

private:
    float m_speed;
    float m_shootCooldown;
};
} // namespace GameLogic
