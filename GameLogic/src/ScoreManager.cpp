#include "ScoreManager.h"

#include <iostream>

namespace GameLogic
{
ScoreManager::ScoreManager() : m_score(0) {}

ScoreManager::~ScoreManager() {}

void ScoreManager::onNotify(Event event)
{
    if (event == Event::ENEMY_DIED)
    {
        this->increaseScore();
    }
}

void ScoreManager::increaseScore()
{
    m_score += GameConstants::POINTS_PER_ALIEN;
}

void ScoreManager::resetScore()
{
    m_score = 0;
}

int ScoreManager::getScore() const noexcept
{
    return m_score;
}
} // namespace GameLogic