#include "Renderer.h"

#include "GameConstants.h"

#include <iostream>
#include <sstream>

namespace GameUI
{

Renderer::Renderer(sf::RenderWindow& window)
    : m_window(window), m_shipSpriteSheet(), m_projectileSpriteSheet(), m_alienSpriteSheet(),
      m_playerSprite(m_shipSpriteSheet), m_alienSprite(m_alienSpriteSheet), m_bulletSprite(m_projectileSpriteSheet),
      m_backgroundSprite(m_backgroundTexture), m_backgroundSprite2(m_backgroundTexture), m_scoreText(m_font),
      m_titleText(m_font), m_playText(m_font), m_exitText(m_font), m_gameOverText(m_font), m_restartText(m_font),
      m_youWinText(m_font)
{
    initFonts();
    initSprites();
    initBackground();
}

void Renderer::initFonts()
{
    const std::vector<std::string> candidates = {
        "./Assets/Fonts/ARCADECLASSIC.TTF",            // workspace root
        "Assets/Fonts/ARCADECLASSIC.TTF",             // fallback
        "../Assets/Fonts/ARCADECLASSIC.TTF",          // if cwd is GameUI/
        "./GameUI/Assets/Fonts/ARCADECLASSIC.TTF"     // copied Assets
    };

    std::string chosen;
    for (const auto& p : candidates)
    {
        if (std::filesystem::exists(p))
        {
            chosen = p;
            break;
        }
    }

    if (chosen.empty() || !m_font.openFromFile(chosen))
    {
        std::cerr << "Failed to load font. Checked paths:\n";
        for (const auto& p : candidates)
            std::cerr << "  " << std::filesystem::absolute(p).string() << "\n";
        throw std::runtime_error("Failed to load font: ARCADECLASSIC.TTF");
    }

    // Initialize all text objects
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition(sf::Vector2f(10.f, 10.f));

    setupText(m_titleText, "SPACE INVADERS", 64, sf::Color::White, 150.f);
    setupText(m_playText, "PLAY   P", 32, sf::Color::Green, 300.f);
    setupText(m_exitText, "EXIT   ESC", 32, sf::Color::White, 350.f);

    m_gameOverText.setFont(m_font);
    m_gameOverText.setString("GAME OVER");
    m_gameOverText.setCharacterSize(64);
    m_gameOverText.setFillColor(sf::Color::Red);
    float gameOverWidth = m_gameOverText.getLocalBounds().size.x;
    m_gameOverText.setPosition(sf::Vector2f((GameLogic::GameConstants::SCREEN_WIDTH - gameOverWidth) / 2.f, 150.f));

    setupText(m_restartText, "RESTART   R", 32, sf::Color::Green, 300.f);

    m_youWinText.setFont(m_font);
    m_youWinText.setString("YOU WIN");
    m_youWinText.setCharacterSize(64);
    m_youWinText.setFillColor(sf::Color::Green);
    float youWinWidth = m_youWinText.getLocalBounds().size.x;
    m_youWinText.setPosition(sf::Vector2f((GameLogic::GameConstants::SCREEN_WIDTH - youWinWidth) / 2.f, 150.f));
}

void Renderer::loadTexture(sf::Texture& texture, const std::string& path)
{
    std::vector<std::string> candidates = {
        path,
        "." + path.substr(1),  // Remove leading ./
        "./GameUI" + path.substr(1)  // Try GameUI prefix
    };

    bool loaded = false;
    for (const auto& p : candidates)
    {
        if (std::filesystem::exists(p) && texture.loadFromFile(p))
        {
            loaded = true;
            break;
        }
    }

    if (!loaded)
    {
        std::cerr << "Failed to load texture. Checked paths:\n";
        for (const auto& p : candidates)
            std::cerr << "  " << std::filesystem::absolute(p).string() << "\n";
        throw std::runtime_error("Failed to load texture: " + path);
    }
    texture.setSmooth(false);
}

void Renderer::setupSprite(sf::Sprite& sprite, sf::Texture& texture, sf::IntRect rect)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
}

void Renderer::setupText(sf::Text& text, const std::string& str, int size, sf::Color color, float yPos)
{
    text.setFont(m_font);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setString(str);

    float width = text.getLocalBounds().size.length();
    text.setPosition(sf::Vector2f((GameLogic::GameConstants::SCREEN_WIDTH - width) / 2.f, yPos));
}

void Renderer::initSprites()
{
    loadTexture(m_shipSpriteSheet, "./Assets/Sprites/SpaceShooterAssetPack_Ships.png");
    loadTexture(m_projectileSpriteSheet, "./Assets/Sprites/SpaceShooterAssetPack_Projectiles.png");
    loadTexture(m_alienSpriteSheet, "./Assets/Sprites/SpaceShooterAssetPack_Ships.png");

    setupSprite(m_playerSprite, m_shipSpriteSheet, sf::IntRect(sf::Vector2i(72, 24), sf::Vector2i(8, 8)));
    setupSprite(m_bulletSprite, m_projectileSpriteSheet, sf::IntRect(sf::Vector2i(8, 16), sf::Vector2i(8, 8)));
    setupSprite(m_alienSprite, m_alienSpriteSheet, sf::IntRect(sf::Vector2i(40, 16), sf::Vector2i(8, 8)));
}

void Renderer::initBackground()
{
    loadTexture(m_backgroundTexture, "./Assets/Sprites/background.png");

    sf::IntRect backgroundRect(sf::Vector2i(0, 0), sf::Vector2i(800, 600));

    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setTextureRect(backgroundRect);

    m_backgroundSprite2.setTexture(m_backgroundTexture);
    m_backgroundSprite2.setTextureRect(backgroundRect);
    m_backgroundSprite2.setPosition(sf::Vector2f(0.f, -GameLogic::GameConstants::SCREEN_HEIGHT));
}

void Renderer::updateBackground(float deltaTime)
{
    float scrollAmount = GameLogic::GameConstants::BACKGROUND_SCROLL_SPEED * deltaTime;
    sf::Vector2f moveVector(0.f, scrollAmount);

    m_backgroundSprite.move(moveVector);
    m_backgroundSprite2.move(moveVector);

    const float screenHeight = GameLogic::GameConstants::SCREEN_HEIGHT;

    if (m_backgroundSprite.getPosition().y >= screenHeight)
        m_backgroundSprite.setPosition(sf::Vector2f(0.f, m_backgroundSprite2.getPosition().y - screenHeight));

    if (m_backgroundSprite2.getPosition().y >= screenHeight)
        m_backgroundSprite2.setPosition(sf::Vector2f(0.f, m_backgroundSprite.getPosition().y - screenHeight));
}

void Renderer::renderBackground()
{
    m_window.clear();
    m_window.draw(m_backgroundSprite);
    m_window.draw(m_backgroundSprite2);
}

void Renderer::render(const GameLogic::GameState& gameState)
{
    renderBackground();

    renderPlayer(gameState.getPlayer());
    renderAliens(gameState.getAliens());
    renderBullets(gameState.getBullets());
    renderScore(gameState.getScore());

    if (gameState.isGameOver())
        renderGameOverMenu(gameState.getScore());

    m_window.display();
}

void Renderer::renderMainMenu()
{
    renderBackground();
    m_window.draw(m_titleText);
    m_window.draw(m_playText);
    m_window.draw(m_exitText);
    m_window.display();
}

void Renderer::renderEndScreen(const sf::Text& titleText, int score)
{
    renderBackground();
    m_window.draw(titleText);

    std::ostringstream oss;
    oss << "FINAL SCORE   " << score;
    m_scoreText.setString(oss.str());

    float width = m_scoreText.getLocalBounds().size.x;
    m_scoreText.setPosition(sf::Vector2f((GameLogic::GameConstants::SCREEN_WIDTH - width) / 2.f, 250.f));

    m_window.draw(m_scoreText);
    m_window.draw(m_restartText);
    m_window.draw(m_exitText);

    m_window.display();
}

void Renderer::renderGameOverMenu(int score)
{
    renderEndScreen(m_gameOverText, score);
}

void Renderer::renderYouWinMenu(int score)
{
    renderEndScreen(m_youWinText, score);
}

void Renderer::renderPlayer(const GameLogic::Player& player)
{
    if (!player.isActive())
        return;
    auto pos = player.getPosition();
    auto size = player.getSize();
    m_playerSprite.setPosition(sf::Vector2f(pos.x, pos.y));
    m_playerSprite.setScale(sf::Vector2f(size.x / GameLogic::GameConstants::SPRITE_BASE_SIZE,
                                         size.y / GameLogic::GameConstants::SPRITE_BASE_SIZE));
    m_window.draw(m_playerSprite);
}

void Renderer::renderAliens(const std::vector<GameLogic::Alien>& aliens)
{
    for (const auto& alien : aliens)
    {
        if (!alien.isActive())
            continue;
        auto pos = alien.getPosition();
        auto size = alien.getSize();
        m_alienSprite.setPosition(sf::Vector2f(pos.x, pos.y));
        m_alienSprite.setScale(sf::Vector2f(size.x / GameLogic::GameConstants::SPRITE_BASE_SIZE,
                                            size.y / GameLogic::GameConstants::SPRITE_BASE_SIZE));
        m_window.draw(m_alienSprite);
    }
}

void Renderer::renderBullets(const std::vector<GameLogic::Bullet>& bullets)
{
    for (const auto& bullet : bullets)
    {
        if (!bullet.isActive())
            continue;
        auto pos = bullet.getPosition();
        auto size = bullet.getSize();
        m_bulletSprite.setPosition(sf::Vector2f(pos.x, pos.y));
        m_bulletSprite.setScale(sf::Vector2f(size.x / GameLogic::GameConstants::SPRITE_BASE_SIZE,
                                             size.y / GameLogic::GameConstants::SPRITE_BASE_SIZE));
        m_window.draw(m_bulletSprite);
    }
}

void Renderer::renderScore(int score)
{
    std::ostringstream oss;
    oss << "Score   " << score;
    m_scoreText.setString(oss.str());
    m_scoreText.setPosition(sf::Vector2f(10.f, 10.f));
    m_window.draw(m_scoreText);
}

} // namespace GameUI
