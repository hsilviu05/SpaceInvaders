#pragma once

namespace GameLogic
{
enum class Event
{
    ENEMY_DIED
};

class IObserver
{
public:
    virtual ~IObserver() {}
    virtual void onNotify(Event event) = 0;
};
} // namespace GameLogic