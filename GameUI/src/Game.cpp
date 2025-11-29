#include "Game.h"

#include "GameConstants.h"

namespace GameUI
{
Game::Game()
    : m_window{sf::VideoMode{{static_cast<unsigned int>(GameLogic::GameConstants::SCREEN_WIDTH),
                              static_cast<unsigned int>(GameLogic::GameConstants::SCREEN_HEIGHT)}},
               "Space Invaders"},
      m_renderer{m_window}, m_gameStatus{GameStatus::MainMenu}
{
    m_window.setFramerateLimit(60);
}

void Game::run()
{
    while (m_window.isOpen())
    {
        float deltaTime = m_clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    while (std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
            return;
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                m_window.close();
                return;
            }

            switch (m_gameStatus)
            {
            case GameStatus::MainMenu:
                if (keyPressed->scancode == sf::Keyboard::Scancode::P)
                {
                    m_gameStatus = GameStatus::Playing;
                }
                break;

            case GameStatus::GameOver:
            case GameStatus::YouWin:
                if (keyPressed->scancode == sf::Keyboard::Scancode::R)
                {
                    m_gameState.reset();
                    m_gameStatus = GameStatus::Playing;
                }
                break;

            default:
                break;
            }
        }
    }
}

void Game::update(float deltaTime)
{
    m_renderer.updateBackground(deltaTime);

    if (m_gameStatus == GameStatus::Playing)
    {
        if (!m_gameState.isGameOver() && !m_gameState.isGameWon())
        {
            m_inputHandler.handleInput(m_gameState, deltaTime);
            m_gameState.update(deltaTime);
        }
        else if (m_gameState.isGameWon())
        {
            m_gameStatus = GameStatus::YouWin;
        }
        else
        {
            m_gameStatus = GameStatus::GameOver;
        }
    }
}

void Game::render()
{
    switch (m_gameStatus)
    {
    case GameStatus::MainMenu:
        m_renderer.renderMainMenu();
        break;
    case GameStatus::Playing:
        m_renderer.render(m_gameState);
        break;
    case GameStatus::GameOver:
        m_renderer.renderGameOverMenu(m_gameState.getScore());
        break;
    case GameStatus::YouWin:
        m_renderer.renderYouWinMenu(m_gameState.getScore());
        break;
    }
}
} // namespace GameUI
