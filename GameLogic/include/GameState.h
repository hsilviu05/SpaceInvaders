#pragma once

#include "Alien.h"
#include "Bullet.h"
#include "Player.h"
#include "ScoreManager.h"

#include <memory>
#include <vector>

namespace GameLogic
{
/**
 * @class GameState
 * @brief Gestionează starea principală a jocului
 * 
 * Clasa GameState este responsabilă pentru:
 * - Gestionarea tuturor entităților (Player, Aliens, Bullets)
 * - Verificarea coliziunilor
 * - Actualizarea logicii jocului
 * - Gestionarea scorului și stării jocului (Game Over, You Win)
 * 
 * @see Player
 * @see Alien
 * @see Bullet
 * @see ScoreManager
 */
class GameState
{
public:
    /**
     * @brief Constructor pentru GameState
     * Inițializează jocul cu jucătorul și inamicii
     */
    GameState();

    /**
     * @brief Actualizează starea jocului
     * @param deltaTime Timpul scurs de la ultimul frame
     */
    void update(float deltaTime);
    
    /**
     * @brief Gestionează mișcarea jucătorului spre stânga
     * @param deltaTime Timpul scurs de la ultimul frame
     */
    void handlePlayerMoveLeft(float deltaTime);
    
    /**
     * @brief Gestionează mișcarea jucătorului spre dreapta
     * @param deltaTime Timpul scurs de la ultimul frame
     */
    void handlePlayerMoveRight(float deltaTime);
    
    /**
     * @brief Gestionează tragerea jucătorului
     */
    void handlePlayerShoot();

    /**
     * @brief Verifică coliziunile între toate entitățile
     */
    void checkCollisions();
    
    /**
     * @brief Elimină entitățile inactive din joc
     */
    void removeInactiveEntities();

    /**
     * @brief Obține referința la jucător
     * @return Player& Referință la jucător
     */
    Player& getPlayer();
    
    /**
     * @brief Obține referința constantă la jucător
     * @return const Player& Referință constantă la jucător
     */
    const Player& getPlayer() const noexcept;
    
    /**
     * @brief Obține vectorul de inamici
     * @return const std::vector<Alien>& Vectorul de inamici
     */
    const std::vector<Alien>& getAliens() const noexcept;
    
    /**
     * @brief Obține vectorul de proiectile
     * @return const std::vector<Bullet>& Vectorul de proiectile
     */
    const std::vector<Bullet>& getBullets() const noexcept;

    /**
     * @brief Obține scorul curent
     * @return int Scorul curent
     */
    int getScore() const noexcept;
    
    /**
     * @brief Verifică dacă jocul s-a terminat (Game Over)
     * @return bool true dacă jocul s-a terminat, false altfel
     */
    bool isGameOver() const noexcept;
    
    /**
     * @brief Verifică dacă jucătorul a câștigat
     * @return bool true dacă jucătorul a câștigat, false altfel
     */
    bool isGameWon() const noexcept;

    /**
     * @brief Resetează jocul la starea inițială
     */
    void reset();

private:
    /**
     * @brief Inițializează inamicii în formație
     */
    void initializeAliens();
    
    /**
     * @brief Actualizează formația de inamici
     * @param deltaTime Timpul scurs de la ultimul frame
     */
    void updateAlienFormation(float deltaTime);

    Player m_player;                    ///< Jucătorul
    std::vector<Alien> m_aliens;       ///< Vectorul de inamici
    std::vector<Bullet> m_bullets;     ///< Vectorul de proiectile

    std::unique_ptr<ScoreManager> m_scoreManager; ///< Managerul de scor

    bool m_gameOver;       ///< Flag pentru Game Over
    bool m_gameWon;        ///< Flag pentru You Win

    float m_alienDirection; ///< Direcția curentă de mișcare a inamicilor (-1 sau 1)
};
} // namespace GameLogic
