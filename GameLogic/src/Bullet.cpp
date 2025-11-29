#include "Bullet.h"

#include "GameConstants.h"

namespace GameLogic
{
Bullet::Bullet(Vector2D position, Vector2D size)
    : Entity{position, size, EntityType::Bullet}, m_speed{GameConstants::BULLET_SPEED}
{
}

void Bullet::moveUp(float deltaTime)
{
    m_position.y -= m_speed * deltaTime;

    if (m_position.y + m_size.y < GameConstants::SCREEN_TOP)
    {
        m_active = false;
    }
}

void Bullet::update(float deltaTime)
{
    moveUp(deltaTime);
}

float Bullet::getSpeed() const
{
    return m_speed;
}

void Bullet::setSpeed(float speed)
{
    m_speed = speed;
}
} // namespace GameLogic
