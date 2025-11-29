#include "GameState.h"

#include "GameConstants.h"

#include <algorithm>

namespace GameLogic
{
GameState::GameState()
    : m_player{Vector2D{GameConstants::PLAYER_START_X, GameConstants::PLAYER_START_Y},
               Vector2D{GameConstants::PLAYER_WIDTH, GameConstants::PLAYER_HEIGHT}},
      m_scoreManager{std::make_unique<ScoreManager>()}, m_gameOver{false}, m_gameWon{false},
      m_alienDirection{GameConstants::DIRECTION_RIGHT}, m_alienMoveTimer{0.f}
{
    initializeAliens();
}

void GameState::initializeAliens()
{
    m_aliens.clear();

    for (int row = 0; row < GameConstants::ALIEN_ROWS; ++row)
    {
        for (int col = 0; col < GameConstants::ALIEN_COLUMNS; ++col)
        {
            float x = GameConstants::ALIEN_START_X + col * GameConstants::ALIEN_SPACING_X;
            float y = GameConstants::ALIEN_START_Y + row * GameConstants::ALIEN_SPACING_Y;

            Alien new_alien(Vector2D{x, y}, Vector2D{GameConstants::ALIEN_WIDTH, GameConstants::ALIEN_HEIGHT});
            new_alien.addObserver(m_scoreManager.get());
            m_aliens.push_back(new_alien);
        }
    }
}

void GameState::update(float deltaTime)
{
    if (m_gameOver || m_gameWon)
        return;

    m_player.update(deltaTime);

    for (auto& bullet : m_bullets)
    {
        if (bullet.isActive())
            bullet.update(deltaTime);
    }

    for (auto& alien : m_aliens)
    {
        if (alien.isActive())
            alien.update(deltaTime);
    }

    updateAlienFormation(deltaTime);
    checkCollisions();
    removeInactiveEntities();

    // Check win condition
    if (std::none_of(m_aliens.begin(), m_aliens.end(), [](const Alien& a) { return a.isActive(); }))
    {
        m_gameWon = true;
        return;
    }

    // Check if alien reaches bottom
    for (const auto& alien : m_aliens)
    {
        if (alien.isActive() && alien.getPosition().y > GameConstants::ALIEN_GAME_OVER_Y)
        {
            m_gameOver = true;
            break;
        }
    }
}

void GameState::updateAlienFormation(float deltaTime)
{
    m_alienMoveTimer += deltaTime;

    if (m_alienMoveTimer >= GameConstants::ALIEN_MOVE_INTERVAL)
    {
        m_alienMoveTimer = 0.f;

        // Check if any alien hits the edge
        bool hitEdge = false;
        for (const auto& alien : m_aliens)
        {
            if (!alien.isActive())
                continue;

            float nextX = alien.getPosition().x + m_alienDirection * GameConstants::ALIEN_HORIZONTAL_STEP;
            if (nextX < GameConstants::SCREEN_LEFT || nextX + alien.getSize().x > GameConstants::SCREEN_WIDTH)
            {
                hitEdge = true;
                break;
            }
        }

        if (hitEdge)
        {
            // Move down and reverse direction
            for (auto& alien : m_aliens)
            {
                if (alien.isActive())
                    alien.moveDown(GameConstants::ALIEN_VERTICAL_STEP);
            }
            m_alienDirection *= GameConstants::DIRECTION_LEFT;
        }
        else
        {
            // Move horizontally
            for (auto& alien : m_aliens)
            {
                if (alien.isActive())
                    alien.moveHorizontal(m_alienDirection, GameConstants::ALIEN_HORIZONTAL_SPEED_MULTIPLIER);
            }
        }
    }
}

void GameState::handlePlayerMoveLeft(float deltaTime)
{
    m_player.moveLeft(deltaTime);
}

void GameState::handlePlayerMoveRight(float deltaTime)
{
    m_player.moveRight(deltaTime);
}

void GameState::handlePlayerShoot()
{
    if (m_player.canShoot())
    {
        m_player.shoot();
        Vector2D bulletPos{
            m_player.getPosition() +
            Vector2D{m_player.getSize().x / 2.f - GameConstants::BULLET_OFFSET_X, GameConstants::BULLET_OFFSET_Y}};
        m_bullets.emplace_back(bulletPos, Vector2D{GameConstants::BULLET_WIDTH, GameConstants::BULLET_HEIGHT});
    }
}

void GameState::checkCollisions()
{
    // Bullet-alien collisions
    for (auto& bullet : m_bullets)
    {
        if (!bullet.isActive())
            continue;

        for (auto& alien : m_aliens)
        {
            if (!alien.isActive())
                continue;

            if (bullet.checkCollision(alien))
            {
                bullet.setActive(false);
                alien.die();
                alien.setActive(false);
                break;
            }
        }
    }

    for (const auto& alien : m_aliens)
    {
        if (alien.isActive() && m_player.checkCollision(alien))
        {
            m_gameOver = true;
            break;
        }
    }
}

void GameState::removeInactiveEntities()
{
    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), [](const Bullet& b) { return !b.isActive(); }),
                    m_bullets.end());
}

void GameState::reset()
{
    m_player = Player{Vector2D{GameConstants::PLAYER_START_X, GameConstants::PLAYER_START_Y},
                      Vector2D{GameConstants::PLAYER_WIDTH, GameConstants::PLAYER_HEIGHT}};
    m_bullets.clear();
    initializeAliens();
    m_scoreManager->resetScore();
    m_gameOver = false;
    m_gameWon = false;
    m_alienDirection = GameConstants::DIRECTION_RIGHT;
    m_alienMoveTimer = 0.f;
}

Player& GameState::getPlayer()
{
    return m_player;
}

const Player& GameState::getPlayer() const noexcept
{
    return m_player;
}

const std::vector<Alien>& GameState::getAliens() const noexcept
{
    return m_aliens;
}

const std::vector<Bullet>& GameState::getBullets() const noexcept
{
    return m_bullets;
}

int GameState::getScore() const noexcept
{
    return m_scoreManager->getScore();
}

bool GameState::isGameOver() const noexcept
{
    return m_gameOver;
}

bool GameState::isGameWon() const noexcept
{
    return m_gameWon;
}
} // namespace GameLogic
