#pragma once

#include "GameState.h"

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <string>

namespace GameUI
{
class Renderer
{
public:
    Renderer(sf::RenderWindow& window);

    void render(const GameLogic::GameState& gameState);
    void renderMainMenu();
    void renderGameOverMenu(int score);
    void renderYouWinMenu(int score);
    void updateBackground(float deltaTime);

private:
    void renderPlayer(const GameLogic::Player& player);
    void renderAliens(const std::vector<GameLogic::Alien>& aliens);
    void renderBullets(const std::vector<GameLogic::Bullet>& bullets);
    void renderScore(int score);
    void renderBackground();

    void renderEndScreen(const sf::Text& titleText, int score);

    void initFonts();
    void initSprites();
    void initBackground();

    void loadTexture(sf::Texture& texture, const std::string& path);
    void setupSprite(sf::Sprite& sprite, sf::Texture& texture, sf::IntRect rect);
    void setupText(sf::Text& text, const std::string& str, int size, sf::Color color, float yPos);

    sf::RenderWindow& m_window;
    sf::Font m_font;

    sf::Texture m_shipSpriteSheet;
    sf::Texture m_projectileSpriteSheet;
    sf::Texture m_alienSpriteSheet;
    sf::Texture m_backgroundTexture;

    sf::Sprite m_playerSprite;
    sf::Sprite m_alienSprite;
    sf::Sprite m_bulletSprite;
    sf::Sprite m_backgroundSprite;
    sf::Sprite m_backgroundSprite2;

    sf::Text m_scoreText;
    sf::Text m_titleText;
    sf::Text m_playText;
    sf::Text m_exitText;
    sf::Text m_restartText;
    sf::Text m_gameOverText;
    sf::Text m_youWinText;
};
} // namespace GameUI
