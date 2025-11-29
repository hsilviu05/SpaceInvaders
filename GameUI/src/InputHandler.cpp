#include "InputHandler.h"

namespace GameUI
{
void InputHandler::handleInput(GameLogic::GameState& gameState, float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        gameState.handlePlayerMoveLeft(deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        gameState.handlePlayerMoveRight(deltaTime);
    }

    bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    if (spacePressed && !m_spaceWasPressed)
    {
        gameState.handlePlayerShoot();
    }
    m_spaceWasPressed = spacePressed;
}
} // namespace GameUI
