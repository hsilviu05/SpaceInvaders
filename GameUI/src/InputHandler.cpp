#include "InputHandler.h"

namespace GameUI
{
InputHandler::InputHandler() : m_doNothingCommand{std::make_unique<GameLogic::DoNothingCommand>()}
{
    // Set up default key bindings
    bindKey(sf::Keyboard::Key::Left, std::make_unique<GameLogic::MoveLeftCommand>());
    bindKey(sf::Keyboard::Key::A, std::make_unique<GameLogic::MoveLeftCommand>());
    bindKey(sf::Keyboard::Key::Right, std::make_unique<GameLogic::MoveRightCommand>());
    bindKey(sf::Keyboard::Key::D, std::make_unique<GameLogic::MoveRightCommand>());
    bindKey(sf::Keyboard::Key::Space, std::make_unique<GameLogic::ShootCommand>());
}

void InputHandler::bindKey(sf::Keyboard::Key key, std::unique_ptr<GameLogic::ICommand> command)
{
    m_keyBindings[key] = std::move(command);
}

GameLogic::ICommand* InputHandler::handleInput() const
{
    for (const auto& [key, command] : m_keyBindings)
    {
        if (sf::Keyboard::isKeyPressed(key))
        {
            return command.get();
        }
    }
    return m_doNothingCommand.get();
}
} // namespace GameUI