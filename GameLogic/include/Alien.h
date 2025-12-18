#pragma once

#include "Entity.h"
#include "IObserver.h"
#include "Subject.h"

#include <algorithm>
#include <vector>

namespace GameLogic
{
/**
 * @class Alien
 * @brief Reprezintă un inamic în joc
 * 
 * Clasa Alien gestionează:
 * - Mișcarea orizontală și verticală
 * - Sistemul de notificare (Observer pattern)
 * - Distrugerea inamicului
 * 
 * @extends Entity
 * @extends Subject
 */
class Alien : public Entity, public Subject
{
public:
    /**
     * @brief Constructor pentru Alien
     * @param position Poziția inițială
     * @param size Dimensiunea inamicului
     */
    Alien(Vector2D position, Vector2D size);

    /**
     * @brief Mută inamicul în jos
     * @param amount Cantitatea de mișcare în pixeli
     */
    void moveDown(float amount);
    
    /**
     * @brief Mută inamicul orizontal
     * @param direction Direcția de mișcare (-1 pentru stânga, 1 pentru dreapta)
     * @param modifier Modificator de viteză
     * @param deltaTime Timpul scurs de la ultimul frame
     */
    void moveHorizontal(float direction, float modifier, float deltaTime);
    
    /**
     * @brief Actualizează starea inamicului
     * @param deltaTime Timpul scurs de la ultimul frame
     */
    void update(float deltaTime) override;

    /**
     * @brief Distruge inamicul (setează ca inactiv și notifică observatorii)
     */
    void die();

    /**
     * @brief Obține viteza inamicului
     * @return float Viteza în pixeli/secundă
     */
    float getSpeed() const noexcept;
    
    /**
     * @brief Setează viteza inamicului
     * @param speed Noua viteză în pixeli/secundă
     */
    void setSpeed(float speed);

private:
    float m_speed; ///< Viteza de mișcare (pixeli/secundă)
};
} // namespace GameLogic
