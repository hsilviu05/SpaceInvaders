#pragma once

#include "GameState.h"
#include "InputHandler.h"
#include "Renderer.h"

#include <SFML/Graphics.hpp>

namespace GameUI
{
enum class GameStatus
{
    MainMenu,
    Playing,
    GameOver,
    YouWin
};

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    sf::RenderWindow m_window;
    GameLogic::GameState m_gameState;
    Renderer m_renderer;
    InputHandler m_inputHandler;
    sf::Clock m_clock;

    GameStatus m_gameStatus;
};
} // namespace GameUI
