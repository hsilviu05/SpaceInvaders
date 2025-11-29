#include "ScoreManager.h"

#include "GameConstants.h"

#include <gtest/gtest.h>

TEST(ScoreManagerTest, InitializationIsCorrect)
{
    GameLogic::ScoreManager scoreManager;
    EXPECT_EQ(scoreManager.getScore(), 0);
}

TEST(ScoreManagerTest, IncreaseScoreAddsCorrectPoints)
{
    GameLogic::ScoreManager scoreManager;
    scoreManager.increaseScore();

    EXPECT_EQ(scoreManager.getScore(), GameLogic::GameConstants::POINTS_PER_ALIEN);
}

TEST(ScoreManagerTest, ResetScoreSetsScoreToZero)
{
    GameLogic::ScoreManager scoreManager;
    scoreManager.increaseScore();
    scoreManager.increaseScore();

    ASSERT_GT(scoreManager.getScore(), 0);

    scoreManager.resetScore();

    EXPECT_EQ(scoreManager.getScore(), 0);
}

TEST(ScoreManagerTest, OnNotifyEnemyDiedIncreasesScore)
{
    GameLogic::ScoreManager scoreManager;

    scoreManager.onNotify(GameLogic::Event::ENEMY_DIED);

    EXPECT_EQ(scoreManager.getScore(), GameLogic::GameConstants::POINTS_PER_ALIEN);
}

TEST(ScoreManagerTest, ScoreAccumulatesOverMultipleEvents)
{
    GameLogic::ScoreManager scoreManager;

    scoreManager.onNotify(GameLogic::Event::ENEMY_DIED);
    scoreManager.onNotify(GameLogic::Event::ENEMY_DIED);
    scoreManager.increaseScore();

    int expectedScore = GameLogic::GameConstants::POINTS_PER_ALIEN * 3;
    EXPECT_EQ(scoreManager.getScore(), expectedScore);
}
