#pragma once

#include "Alien.h"
#include "Bullet.h"
#include "Player.h"
#include "ScoreManager.h"

#include <memory>
#include <vector>

namespace GameLogic
{
class GameState
{
public:
    GameState();

    void update(float deltaTime);
    void handlePlayerMoveLeft(float deltaTime);
    void handlePlayerMoveRight(float deltaTime);
    void handlePlayerShoot();

    void checkCollisions();
    void removeInactiveEntities();

    Player& getPlayer();
    const Player& getPlayer() const noexcept;
    const std::vector<Alien>& getAliens() const noexcept;
    const std::vector<Bullet>& getBullets() const noexcept;

    int getScore() const noexcept;
    bool isGameOver() const noexcept;
    bool isGameWon() const noexcept;

    void reset();

private:
    void initializeAliens();
    void updateAlienFormation(float deltaTime);

    Player m_player;
    std::vector<Alien> m_aliens;
    std::vector<Bullet> m_bullets;

    std::unique_ptr<ScoreManager> m_scoreManager;

    bool m_gameOver;
    bool m_gameWon;

    float m_alienDirection;
    float m_alienMoveTimer;
};
} // namespace GameLogic
