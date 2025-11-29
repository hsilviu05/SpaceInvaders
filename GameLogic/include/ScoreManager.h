#pragma once

#include "IObserver.h"
#include "GameConstants.h"

namespace GameLogic
{
class ScoreManager : public IObserver
{
public:
    ScoreManager();
    ~ScoreManager();

    void onNotify(Event event) override;
    void increaseScore();
    void resetScore();
    int getScore() const noexcept;

private:
    int m_score;
};
} // namespace GameLogic