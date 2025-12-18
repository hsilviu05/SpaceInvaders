#pragma once

#include "ICollidable.h"
#include "Vector2D.h"

namespace GameLogic
{
/**
 * @enum EntityType
 * @brief Tipurile de entități din joc
 */
enum class EntityType
{
    Player,  ///< Entitatea jucătorului
    Alien,   ///< Entitatea inamicului
    Bullet   ///< Entitatea proiectilului
};

/**
 * @class Entity
 * @brief Clasă de bază abstractă pentru toate entitățile din joc
 * 
 * Această clasă oferă funcționalitatea de bază pentru entități:
 * - Poziție și dimensiune
 * - Sistem de coliziuni
 * - Stare activă/inactivă
 * 
 * @see ICollidable
 * @see Player
 * @see Alien
 * @see Bullet
 */
class Entity : public ICollidable
{
public:
    virtual ~Entity() = default;

    /**
     * @brief Obține poziția entității
     * @return Vector2D Poziția curentă
     */
    Vector2D getPosition() const noexcept;
    
    /**
     * @brief Obține dimensiunea entității
     * @return Vector2D Dimensiunea (lățime, înălțime)
     */
    Vector2D getSize() const noexcept;
    
    /**
     * @brief Obține tipul entității
     * @return EntityType Tipul entității
     */
    EntityType getType() const noexcept;
    
    /**
     * @brief Verifică dacă entitatea este activă
     * @return bool true dacă entitatea este activă, false altfel
     */
    bool isActive() const noexcept;

    /**
     * @brief Setează poziția entității
     * @param position Noua poziție
     */
    void setPosition(const Vector2D& position);
    
    /**
     * @brief Setează starea activă/inactivă a entității
     * @param active true pentru activ, false pentru inactiv
     */
    void setActive(bool active);

    /**
     * @brief Actualizează entitatea
     * @param deltaTime Timpul scurs de la ultimul frame (în secunde)
     * 
     * Metodă virtuală pură care trebuie implementată de clasele derivate.
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Obține dreptunghiul de coliziune
     * @return Rectangle Dreptunghiul de coliziune
     */
    Rectangle getBounds() const override;
    
    /**
     * @brief Verifică coliziunea cu o altă entitate
     * @param other Cealaltă entitate colizibilă
     * @return bool true dacă există coliziune, false altfel
     */
    bool checkCollision(const ICollidable& other) const override;

protected:
    /**
     * @brief Constructor protejat pentru clasele derivate
     * @param position Poziția inițială
     * @param size Dimensiunea entității
     * @param type Tipul entității
     */
    Entity(Vector2D position, Vector2D size, EntityType type);

    Vector2D m_position;  ///< Poziția entității în spațiu
    Vector2D m_size;      ///< Dimensiunea entității (lățime, înălțime)
    EntityType m_type;    ///< Tipul entității
    bool m_active;        ///< Starea activă/inactivă
};
} // namespace GameLogic
