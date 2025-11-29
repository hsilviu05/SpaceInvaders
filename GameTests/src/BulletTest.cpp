#include "Bullet.h"

#include "GameConstants.h"

#include <gtest/gtest.h>

class BulletTest : public ::testing::Test
{
protected:
    GameLogic::Vector2D startPos{400.f, 500.f};
    GameLogic::Vector2D size{8.f, 8.f};
    GameLogic::Bullet bullet{startPos, size};
};

TEST_F(BulletTest, InitializationIsCorrect)
{
    EXPECT_FLOAT_EQ(bullet.getPosition().x, 400.f);
    EXPECT_FLOAT_EQ(bullet.getPosition().y, 500.f);
    EXPECT_FLOAT_EQ(bullet.getSize().x, 8.f);
    EXPECT_FLOAT_EQ(bullet.getSize().y, 8.f);
    EXPECT_EQ(bullet.getType(), GameLogic::EntityType::Bullet);
    EXPECT_TRUE(bullet.isActive());
    EXPECT_FLOAT_EQ(bullet.getSpeed(), GameLogic::GameConstants::BULLET_SPEED);
}

TEST_F(BulletTest, MoveUpUpdatesPositionCorrectly)
{
    float deltaTime = 0.1f;
    float currentSpeed = bullet.getSpeed();

    bullet.update(deltaTime);

    float expectedY = 500.f - (currentSpeed * deltaTime);
    EXPECT_FLOAT_EQ(bullet.getPosition().y, expectedY);
    EXPECT_FLOAT_EQ(bullet.getPosition().x, 400.f);
}

TEST_F(BulletTest, SetSpeedUpdatesMovementLogic)
{
    float newSpeed = 1000.f;
    bullet.setSpeed(newSpeed);

    EXPECT_FLOAT_EQ(bullet.getSpeed(), newSpeed);

    float deltaTime = 1.0f;
    bullet.update(deltaTime);

    float expectedY = 500.f - newSpeed;
    EXPECT_FLOAT_EQ(bullet.getPosition().y, expectedY);
}

TEST_F(BulletTest, DeactivatesWhenOffScreen)
{
    GameLogic::Vector2D nearTopPos{400.f, 5.f};
    GameLogic::Bullet edgeBullet{nearTopPos, size};

    float deltaTime = 1.0f;
    edgeBullet.setSpeed(100.f);

    edgeBullet.update(deltaTime);

    EXPECT_FALSE(edgeBullet.isActive());
}
