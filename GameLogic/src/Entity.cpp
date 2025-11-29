#include "Entity.h"

namespace GameLogic
{
Entity::Entity(Vector2D position, Vector2D size, EntityType type)
    : m_position{position}, m_size{size}, m_type{type}, m_active{true}
{
}

Rectangle Entity::getBounds() const
{
    return Rectangle{m_position.x, m_position.y, m_size.x, m_size.y};
}

bool Entity::checkCollision(const ICollidable& other) const
{
    return getBounds().intersects(other.getBounds());
}

Vector2D Entity::getPosition() const noexcept
{
    return m_position;
}

Vector2D Entity::getSize() const noexcept
{
    return m_size;
}

EntityType Entity::getType() const noexcept
{
    return m_type;
}

bool Entity::isActive() const noexcept
{
    return m_active;
}

void Entity::setPosition(const Vector2D& position)
{
    m_position = position;
}

void Entity::setActive(bool active)
{
    m_active = active;
}
} // namespace GameLogic
