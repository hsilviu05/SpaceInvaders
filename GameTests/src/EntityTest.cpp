#include "Entity.h"

#include <gtest/gtest.h>

// --- Helper Class ---
// We define a simple concrete class to test the abstract Entity base class
class ConcreteEntity : public GameLogic::Entity
{
public:
    ConcreteEntity(GameLogic::Vector2D position, GameLogic::Vector2D size, GameLogic::EntityType type)
        : GameLogic::Entity(position, size, type)
    {
    }

    // Implement the pure virtual function so we can instantiate this class
    void update(float deltaTime) override
    {
        // No operation needed for base entity tests
    }
};

// --- Tests ---

TEST(EntityTest, InitializationIsCorrect)
{
    GameLogic::Vector2D pos{10.f, 20.f};
    GameLogic::Vector2D size{32.f, 32.f};

    ConcreteEntity entity(pos, size, GameLogic::EntityType::Player);

    EXPECT_FLOAT_EQ(entity.getPosition().x, 10.f);
    EXPECT_FLOAT_EQ(entity.getPosition().y, 20.f);
    EXPECT_FLOAT_EQ(entity.getSize().x, 32.f);
    EXPECT_FLOAT_EQ(entity.getSize().y, 32.f);
    EXPECT_EQ(entity.getType(), GameLogic::EntityType::Player);

    // Entities should be active by default
    EXPECT_TRUE(entity.isActive());
}

TEST(EntityTest, SetPositionUpdatesCoordinates)
{
    ConcreteEntity entity({0.f, 0.f}, {10.f, 10.f}, GameLogic::EntityType::Alien);

    GameLogic::Vector2D newPos{100.f, 200.f};
    entity.setPosition(newPos);

    EXPECT_FLOAT_EQ(entity.getPosition().x, 100.f);
    EXPECT_FLOAT_EQ(entity.getPosition().y, 200.f);
}

TEST(EntityTest, SetActiveUpdatesState)
{
    ConcreteEntity entity({0.f, 0.f}, {10.f, 10.f}, GameLogic::EntityType::Bullet);

    entity.setActive(false);
    EXPECT_FALSE(entity.isActive());

    entity.setActive(true);
    EXPECT_TRUE(entity.isActive());
}

TEST(EntityTest, GetBoundsReturnsCorrectRectangle)
{
    // Pos(10, 10), Size(20, 30)
    ConcreteEntity entity({10.f, 10.f}, {20.f, 30.f}, GameLogic::EntityType::Player);

    auto bounds = entity.getBounds();
    EXPECT_FLOAT_EQ(bounds.width, 20.f);
    EXPECT_FLOAT_EQ(bounds.height, 30.f);
}

TEST(EntityTest, CheckCollisionDetectsOverlaps)
{
    // Entity 1 at (0,0) size (10,10) -> Box is 0-10, 0-10
    ConcreteEntity e1({0.f, 0.f}, {10.f, 10.f}, GameLogic::EntityType::Player);

    // Entity 2 at (5,5) size (10,10) -> Box is 5-15, 5-15 (Overlaps)
    ConcreteEntity e2({5.f, 5.f}, {10.f, 10.f}, GameLogic::EntityType::Alien);

    // Entity 3 at (20,20) size (10,10) -> Box is 20-30, 20-30 (No overlap)
    ConcreteEntity e3({20.f, 20.f}, {10.f, 10.f}, GameLogic::EntityType::Alien);

    EXPECT_TRUE(e1.checkCollision(e2));
    EXPECT_FALSE(e1.checkCollision(e3));
}
