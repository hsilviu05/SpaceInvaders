#pragma once

#include "Entity.h"

namespace GameLogic
{
/**
 * @class Player
 * @brief Reprezintă jucătorul controlat de utilizator
 * 
 * Clasa Player gestionează:
 * - Mișcarea stânga/dreapta
 * - Sistemul de tragere cu cooldown
 * - Viteza de mișcare
 * 
 * @extends Entity
 */
class Player : public Entity
{
public:
    /**
     * @brief Constructor pentru Player
     * @param position Poziția inițială
     * @param size Dimensiunea jucătorului
     */
    Player(Vector2D position, Vector2D size);

    /**
     * @brief Mută jucătorul spre stânga
     * @param deltaTime Timpul scurs de la ultimul frame
     */
    void moveLeft(float deltaTime);
    
    /**
     * @brief Mută jucătorul spre dreapta
     * @param deltaTime Timpul scurs de la ultimul frame
     */
    void moveRight(float deltaTime);
    
    /**
     * @brief Actualizează starea jucătorului
     * @param deltaTime Timpul scurs de la ultimul frame
     */
    void update(float deltaTime) override;

    /**
     * @brief Verifică dacă jucătorul poate trage
     * @return bool true dacă cooldown-ul a expirat
     */
    bool canShoot() const noexcept;
    
    /**
     * @brief Declanșează tragerea (resetează cooldown-ul)
     */
    void shoot();
    
    /**
     * @brief Resetează cooldown-ul de tragere
     */
    void resetShootCooldown();

    /**
     * @brief Obține viteza jucătorului
     * @return float Viteza în pixeli/secundă
     */
    float getSpeed() const noexcept;
    
    /**
     * @brief Setează viteza jucătorului
     * @param speed Noua viteză în pixeli/secundă
     */
    void setSpeed(float speed);

private:
    float m_speed;         ///< Viteza de mișcare (pixeli/secundă)
    float m_shootCooldown; ///< Timpul rămas până la următoarea tragere permisă
};
} // namespace GameLogic
