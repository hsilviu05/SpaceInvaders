#include <gtest/gtest.h>
#include "Player.h"
#include "GameConstants.h"

using namespace GameLogic;

class PlayerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Create a player at a known position
        player = new Player(Vector2D{400.f, 500.f}, Vector2D{48.f, 48.f});
    }

    void TearDown() override
    {
        delete player;
    }

    Player* player;
};

// Constructor and Initialization Tests
TEST_F(PlayerTest, ConstructorInitializesCorrectly)
{
    Vector2D expectedPos{400.f, 500.f};
    Vector2D expectedSize{48.f, 48.f};

    EXPECT_EQ(player->getPosition().x, expectedPos.x);
    EXPECT_EQ(player->getPosition().y, expectedPos.y);
    EXPECT_EQ(player->getSize().x, expectedSize.x);
    EXPECT_EQ(player->getSize().y, expectedSize.y);
    EXPECT_EQ(player->getType(), EntityType::Player);
    EXPECT_TRUE(player->isActive());
}

TEST_F(PlayerTest, InitialSpeedIsCorrect)
{
    EXPECT_EQ(player->getSpeed(), GameConstants::PLAYER_SPEED);
}

// Movement Tests
TEST_F(PlayerTest, MoveLeftDecreasesXPosition)
{
    float initialX = player->getPosition().x;
    float deltaTime = 0.1f;

    player->moveLeft(deltaTime);

    float expectedX = initialX - GameConstants::PLAYER_SPEED * deltaTime;
    EXPECT_FLOAT_EQ(player->getPosition().x, expectedX);
}

TEST_F(PlayerTest, MoveRightIncreasesXPosition)
{
    float initialX = player->getPosition().x;
    float deltaTime = 0.1f;

    player->moveRight(deltaTime);

    float expectedX = initialX + GameConstants::PLAYER_SPEED * deltaTime;
    EXPECT_FLOAT_EQ(player->getPosition().x, expectedX);
}

TEST_F(PlayerTest, MoveLeftClampsToLeftBoundary)
{
    // Move player far left
    for (int i = 0; i < 100; ++i)
    {
        player->moveLeft(0.1f);
    }

    EXPECT_EQ(player->getPosition().x, GameConstants::SCREEN_LEFT);
}

TEST_F(PlayerTest, MoveRightClampsToRightBoundary)
{
    // Move player far right
    for (int i = 0; i < 100; ++i)
    {
        player->moveRight(0.1f);
    }

    float expectedMaxX = GameConstants::SCREEN_WIDTH - player->getSize().x;
    EXPECT_EQ(player->getPosition().x, expectedMaxX);
}

// Shooting Tests
TEST_F(PlayerTest, CanShootInitially)
{
    EXPECT_TRUE(player->canShoot());
}

TEST_F(PlayerTest, CannotShootImmediatelyAfterShooting)
{
    player->shoot();
    EXPECT_FALSE(player->canShoot());
}

TEST_F(PlayerTest, CanShootAfterCooldownExpires)
{
    player->shoot();
    EXPECT_FALSE(player->canShoot());

    // Update for longer than cooldown duration
    float totalTime = GameConstants::PLAYER_SHOOT_COOLDOWN + 0.1f;
    player->update(totalTime);

    EXPECT_TRUE(player->canShoot());
}

TEST_F(PlayerTest, CooldownDecreasesOverTime)
{
    player->shoot();
    EXPECT_FALSE(player->canShoot());

    // Update for half the cooldown
    player->update(GameConstants::PLAYER_SHOOT_COOLDOWN / 2.f);
    EXPECT_FALSE(player->canShoot());

    // Update for remaining cooldown
    player->update(GameConstants::PLAYER_SHOOT_COOLDOWN / 2.f);
    EXPECT_TRUE(player->canShoot());
}

TEST_F(PlayerTest, ResetShootCooldownAllowsImmediateShooting)
{
    player->shoot();
    EXPECT_FALSE(player->canShoot());

    player->resetShootCooldown();
    EXPECT_TRUE(player->canShoot());
}

TEST_F(PlayerTest, ShootDoesNothingWhenOnCooldown)
{
    player->shoot();
    player->update(0.1f); // Small update

    // Try to shoot again while on cooldown
    player->shoot();
    player->update(0.1f);

    // Should still be on cooldown
    EXPECT_FALSE(player->canShoot());
}

// Speed Tests
TEST_F(PlayerTest, SetSpeedChangesSpeed)
{
    float newSpeed = 500.f;
    player->setSpeed(newSpeed);

    EXPECT_EQ(player->getSpeed(), newSpeed);
}

TEST_F(PlayerTest, MovementUsesUpdatedSpeed)
{
    float newSpeed = 500.f;
    player->setSpeed(newSpeed);

    float initialX = player->getPosition().x;
    float deltaTime = 0.1f;

    player->moveRight(deltaTime);

    float expectedX = initialX + newSpeed * deltaTime;
    EXPECT_FLOAT_EQ(player->getPosition().x, expectedX);
}

// Update Tests
TEST_F(PlayerTest, UpdateWithZeroDeltaTimeDoesNothing)
{
    player->shoot();
    EXPECT_FALSE(player->canShoot());

    player->update(0.f);

    EXPECT_FALSE(player->canShoot());
}

TEST_F(PlayerTest, CooldownDoesNotGoBelowZero)
{
    player->shoot();
    
    // Update for much longer than cooldown
    player->update(GameConstants::PLAYER_SHOOT_COOLDOWN * 10.f);

    EXPECT_TRUE(player->canShoot());
    
    // Update again should not cause issues
    player->update(1.f);
    EXPECT_TRUE(player->canShoot());
}

// Edge Case Tests
TEST_F(PlayerTest, MultipleMovementsWork)
{
    float initialX = player->getPosition().x;
    float deltaTime = 0.1f;

    player->moveLeft(deltaTime);
    player->moveLeft(deltaTime);
    player->moveRight(deltaTime);

    float expectedX = initialX - GameConstants::PLAYER_SPEED * deltaTime;
    EXPECT_FLOAT_EQ(player->getPosition().x, expectedX);
}

TEST_F(PlayerTest, YPositionRemainsConstantDuringMovement)
{
    float initialY = player->getPosition().y;

    player->moveLeft(0.1f);
    EXPECT_EQ(player->getPosition().y, initialY);

    player->moveRight(0.1f);
    EXPECT_EQ(player->getPosition().y, initialY);
}