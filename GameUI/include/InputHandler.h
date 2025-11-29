#pragma once

#include "GameState.h"

#include <SFML/Window.hpp>

namespace GameUI
{
class InputHandler
{
public:
    InputHandler() = default;

    void handleInput(GameLogic::GameState& gameState, float deltaTime);

private:
    bool m_spaceWasPressed = false;
};
} // namespace GameUI
