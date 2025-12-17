#include "Alien.h"
#include "GameConstants.h"

namespace GameLogic
{
Alien::Alien(Vector2D position, Vector2D size)
    : Entity{position, size, EntityType::Alien}, m_speed{GameConstants::ALIEN_SPEED}
{
}

void Alien::moveDown(float amount)
{
    m_position.y += amount;
}

void Alien::moveHorizontal(float direction, float modifier, float deltaTime)
{
    m_position.x += direction * (m_speed*modifier) *deltaTime;
}

void Alien::update(float deltaTime)
{
    // empty for now
}

void Alien::die()
{
    notify(Event::ENEMY_DIED);
}

float Alien::getSpeed() const noexcept
{
    return m_speed;
}

void Alien::setSpeed(float speed)
{
    m_speed = speed;
}
} // namespace GameLogic
