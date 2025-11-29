#include "GameState.h"

#include "GameConstants.h"

#include <gtest/gtest.h>

class GameStateTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        gameState = new GameLogic::GameState();
    }

    void TearDown() override
    {
        delete gameState;
    }

    GameLogic::GameState* gameState;
};

TEST_F(GameStateTest, InitializationIsCorrect)
{
    const auto& player = gameState->getPlayer();
    EXPECT_FLOAT_EQ(player.getPosition().x, GameLogic::GameConstants::PLAYER_START_X);
    EXPECT_FLOAT_EQ(player.getPosition().y, GameLogic::GameConstants::PLAYER_START_Y);

    int expectedAliens = GameLogic::GameConstants::ALIEN_ROWS * GameLogic::GameConstants::ALIEN_COLUMNS;
    EXPECT_EQ(gameState->getAliens().size(), expectedAliens);

    EXPECT_TRUE(gameState->getBullets().empty());

    EXPECT_FALSE(gameState->isGameOver());
    EXPECT_FALSE(gameState->isGameWon());
    EXPECT_EQ(gameState->getScore(), 0);
}

TEST_F(GameStateTest, HandlePlayerMoveUpdatesPosition)
{
    auto& player = gameState->getPlayer();
    float startX = player.getPosition().x;
    float deltaTime = 0.1f;

    gameState->handlePlayerMoveLeft(deltaTime);

    EXPECT_LT(player.getPosition().x, startX);
}

TEST_F(GameStateTest, HandlePlayerShootCreatesBullet)
{
    EXPECT_TRUE(gameState->getBullets().empty());

    gameState->handlePlayerShoot();

    const auto& bullets = gameState->getBullets();

    ASSERT_EQ(bullets.size(), 1);

    const auto& player = gameState->getPlayer();
    const auto& bullet = bullets[0];

    EXPECT_LE(bullet.getPosition().y, player.getPosition().y);
}

TEST_F(GameStateTest, UpdateMovesBullets)
{
    gameState->handlePlayerShoot();
    const auto& bullets = gameState->getBullets();
    ASSERT_EQ(bullets.size(), 1);

    float startY = bullets[0].getPosition().y;

    gameState->update(0.05f);

    ASSERT_FALSE(bullets.empty()) << "Bullet was deleted during update!";

    EXPECT_LT(bullets[0].getPosition().y, startY);
}

TEST_F(GameStateTest, ResetRestoresInitialState)
{
    gameState->handlePlayerMoveRight(1.0f);
    gameState->handlePlayerShoot();

    EXPECT_NE(gameState->getPlayer().getPosition().x, GameLogic::GameConstants::PLAYER_START_X);

    gameState->reset();

    EXPECT_FLOAT_EQ(gameState->getPlayer().getPosition().x, GameLogic::GameConstants::PLAYER_START_X);
    EXPECT_TRUE(gameState->getBullets().empty());

    int expectedAliens = GameLogic::GameConstants::ALIEN_ROWS * GameLogic::GameConstants::ALIEN_COLUMNS;
    EXPECT_EQ(gameState->getAliens().size(), expectedAliens);
}
