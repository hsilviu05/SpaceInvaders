#pragma once

#include "ICommand.h"
#include "GameState.h"

namespace GameLogic
{
class MoveLeftCommand : public ICommand
{
public:
    void execute(GameState& gameState, float deltaTime) override
    {
        gameState.handlePlayerMoveLeft(deltaTime);
    }
};

class MoveRightCommand : public ICommand
{
public:
    void execute(GameState& gameState, float deltaTime) override
    {
        gameState.handlePlayerMoveRight(deltaTime);
    }
};

class ShootCommand : public ICommand
{
public:
    void execute(GameState& gameState, float deltaTime) override
    {
        gameState.handlePlayerShoot();
    }
};

class DoNothingCommand : public ICommand
{
public:
    void execute(GameState& gameState, float deltaTime) override
    {
        // No operation
    }
};
} // namespace GameLogic