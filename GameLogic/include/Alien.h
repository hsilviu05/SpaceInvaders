#pragma once

#include "Entity.h"
#include "IObserver.h"
#include "Subject.h"

#include <algorithm>
#include <vector>

namespace GameLogic
{
class Alien : public Entity, public Subject
{
public:
    Alien(Vector2D position, Vector2D size);

    void moveDown(float amount);
    void moveHorizontal(float direction, float modifier, float deltaTime);
    void update(float deltaTime) override;

    void die();

    float getSpeed() const noexcept;
    void setSpeed(float speed);

private:
    float m_speed;
};
} // namespace GameLogic
