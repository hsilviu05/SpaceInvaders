#pragma once

#include "ICollidable.h"
#include "Vector2D.h"

namespace GameLogic
{
enum class EntityType
{
    Player,
    Alien,
    Bullet
};

class Entity : public ICollidable
{
public:
    virtual ~Entity() = default;

    Vector2D getPosition() const noexcept;
    Vector2D getSize() const noexcept;
    EntityType getType() const noexcept;
    bool isActive() const noexcept;

    void setPosition(const Vector2D& position);
    void setActive(bool active);

    virtual void update(float deltaTime) = 0;

    Rectangle getBounds() const override;
    bool checkCollision(const ICollidable& other) const override;

protected:
    Entity(Vector2D position, Vector2D size, EntityType type);

    Vector2D m_position;
    Vector2D m_size;
    EntityType m_type;
    bool m_active;
};
} // namespace GameLogic
