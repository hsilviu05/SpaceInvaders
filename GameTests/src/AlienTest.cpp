#include "Alien.h"
#include "GameConstants.h"
#include "IObserver.h"

#include <gtest/gtest.h>

class MockScoreManager : public GameLogic::IObserver
{
public:
    bool eventReceived = false;
    GameLogic::Event lastReceivedEvent;

    void onNotify(GameLogic::Event event) override
    {
        eventReceived = true;
        lastReceivedEvent = event;
    }
};

class AlienTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        startPos = {100.f, 200.f};
        alienSize = {32.f, 32.f};
        alien = new GameLogic::Alien(startPos, alienSize);
    }

    void TearDown() override
    {
        delete alien;
    }

    GameLogic::Vector2D startPos;
    GameLogic::Vector2D alienSize;
    GameLogic::Alien* alien;
};

TEST_F(AlienTest, InitializationIsCorrect)
{
    EXPECT_FLOAT_EQ(alien->getPosition().x, 100.f);
    EXPECT_FLOAT_EQ(alien->getPosition().y, 200.f);
    EXPECT_FLOAT_EQ(alien->getSize().x, 32.f);
    EXPECT_FLOAT_EQ(alien->getSize().y, 32.f);
    EXPECT_EQ(alien->getType(), GameLogic::EntityType::Alien);
    EXPECT_FLOAT_EQ(alien->getSpeed(), GameLogic::GameConstants::ALIEN_SPEED);
}

TEST_F(AlienTest, MoveDownUpdatesPositionCorrectly)
{
    float moveAmount = 10.f;

    alien->moveDown(moveAmount);

    EXPECT_FLOAT_EQ(alien->getPosition().y, 200.f + moveAmount);
    EXPECT_FLOAT_EQ(alien->getPosition().x, 100.f);
}

TEST_F(AlienTest, MoveHorizontalCalculatesCorrectly)
{
    float direction = 1.f;
    float deltaTime = 0.5f;
    float currentSpeed = alien->getSpeed();

    alien->moveHorizontal(direction, deltaTime);

    float expectedX = 100.f + (direction * currentSpeed * deltaTime);
    EXPECT_FLOAT_EQ(alien->getPosition().x, expectedX);
}

TEST_F(AlienTest, SetSpeedUpdatesMovementLogic)
{
    float newSpeed = 500.f;
    alien->setSpeed(newSpeed);

    EXPECT_FLOAT_EQ(alien->getSpeed(), newSpeed);

    float direction = -1.f;
    float deltaTime = 1.0f;

    alien->moveHorizontal(direction, deltaTime);

    float expectedX = 100.f - 500.f;
    EXPECT_FLOAT_EQ(alien->getPosition().x, expectedX);
}

TEST_F(AlienTest, DieNotifiesObservers)
{
    MockScoreManager mockObserver;
    alien->addObserver(&mockObserver);

    ASSERT_FALSE(mockObserver.eventReceived);

    alien->die();

    EXPECT_TRUE(mockObserver.eventReceived);
    EXPECT_EQ(mockObserver.lastReceivedEvent, GameLogic::Event::ENEMY_DIED);
}
