#pragma once

namespace GameLogic
{
class GameState;

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void execute(GameState& gameState, float deltaTime) = 0;
};
} // namespace GameLogic