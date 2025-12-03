#pragma once

#include "GameState.h"
#include "PlayerCommands.h"
#include "ICommand.h"

#include <SFML/Window.hpp>

#include <memory>
#include <unordered_map>

namespace GameUI
{
class InputHandler
{
public:
    InputHandler();

    void bindKey(sf::Keyboard::Key key, std::unique_ptr<GameLogic::ICommand> command);
    GameLogic::ICommand* handleInput() const;

private:
    std::unordered_map<sf::Keyboard::Key, std::unique_ptr<GameLogic::ICommand>> m_keyBindings;
    std::unique_ptr<GameLogic::ICommand> m_doNothingCommand;
};
} // namespace GameUI