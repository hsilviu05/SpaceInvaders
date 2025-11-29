#include "Player.h"

#include "GameConstants.h"

namespace GameLogic
{
Player::Player(Vector2D position, Vector2D size)
    : Entity{position, size, EntityType::Player}, m_speed{GameConstants::PLAYER_SPEED}, m_shootCooldown{0.f}
{
}

void Player::moveLeft(float deltaTime)
{
    m_position.x -= m_speed * deltaTime;

    // Clamp to screen bounds
    if (m_position.x < GameConstants::SCREEN_LEFT)
        m_position.x = GameConstants::SCREEN_LEFT;
}

void Player::moveRight(float deltaTime)
{
    m_position.x += m_speed * deltaTime;

    // Clamp to screen bounds
    if (m_position.x + m_size.x > GameConstants::SCREEN_WIDTH)
        m_position.x = GameConstants::SCREEN_WIDTH - m_size.x;
}

void Player::update(float deltaTime)
{
    if (m_shootCooldown > 0.f)
    {
        m_shootCooldown -= deltaTime;
        if (m_shootCooldown < 0.f)
            m_shootCooldown = 0.f;
    }
}

bool Player::canShoot() const noexcept
{
    return m_shootCooldown <= 0.f;
}

void Player::shoot()
{
    if (canShoot())
    {
        m_shootCooldown = GameConstants::PLAYER_SHOOT_COOLDOWN;
    }
}

void Player::resetShootCooldown()
{
    m_shootCooldown = 0.f;
}

float Player::getSpeed() const noexcept
{
    return m_speed;
}

void Player::setSpeed(float speed)
{
    m_speed = speed;
}
} // namespace GameLogic
