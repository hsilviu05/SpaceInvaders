#pragma once

#include "IObserver.h"

#include <algorithm>
#include <vector>

namespace GameLogic
{
class Subject
{
public:
    virtual ~Subject() {}

    void addObserver(IObserver* observer)
    {
        observers.push_back(observer);
    }

    void removeObserver(IObserver* observer)
    {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end())
        {
            observers.erase(it);
        }
    }

protected:
    void notify(Event event)
    {
        for (IObserver* observer : observers)
        {
            observer->onNotify(event);
        }
    }

private:
    std::vector<IObserver*> observers;
};
} // namespace GameLogic