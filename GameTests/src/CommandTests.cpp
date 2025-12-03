#include "PlayerCommands.h"
#include "GameState.h"
#include "GameConstants.h"

#include <gtest/gtest.h>

using namespace GameLogic;

class CommandTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        gameState = std::make_unique<GameState>();
    }

    std::unique_ptr<GameState> gameState;
};

TEST_F(CommandTest, MoveLeftCommandExecutes)
{
    MoveLeftCommand cmd;
    float initialX = gameState->getPlayer().getPosition().x;
    
    cmd.execute(*gameState, 0.1f);
    
    EXPECT_LT(gameState->getPlayer().getPosition().x, initialX);
}

TEST_F(CommandTest, MoveRightCommandExecutes)
{
    MoveRightCommand cmd;
    float initialX = gameState->getPlayer().getPosition().x;
    
    cmd.execute(*gameState, 0.1f);
    
    EXPECT_GT(gameState->getPlayer().getPosition().x, initialX);
}

TEST_F(CommandTest, ShootCommandExecutes)
{
    ShootCommand cmd;
    
    EXPECT_TRUE(gameState->getPlayer().canShoot());
    
    cmd.execute(*gameState, 0.1f);
    
    EXPECT_FALSE(gameState->getPlayer().canShoot());
}

TEST_F(CommandTest, DoNothingCommandDoesNothing)
{
    DoNothingCommand cmd;
    float initialX = gameState->getPlayer().getPosition().x;
    bool canShoot = gameState->getPlayer().canShoot();
    
    cmd.execute(*gameState, 0.1f);
    
    EXPECT_EQ(gameState->getPlayer().getPosition().x, initialX);
    EXPECT_EQ(gameState->getPlayer().canShoot(), canShoot);
}