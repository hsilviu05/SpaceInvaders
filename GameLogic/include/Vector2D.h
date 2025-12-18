#pragma once

namespace GameLogic
{
/**
 * @struct Vector2D
 * @brief Reprezintă un vector 2D pentru poziții și dimensiuni
 * 
 * Structură simplă pentru coordonate 2D cu operații matematice de bază.
 * Folosită pentru poziționarea entităților și calcularea coliziunilor.
 */
struct Vector2D
{
    float x{}; ///< Coordonata X
    float y{}; ///< Coordonata Y

    /**
     * @brief Constructor implicit (inițializează cu 0, 0)
     */
    constexpr Vector2D() = default;
    
    /**
     * @brief Constructor cu parametri
     * @param xVal Coordonata X
     * @param yVal Coordonata Y
     */
    constexpr Vector2D(float xVal, float yVal) : x{xVal}, y{yVal} {}

    /**
     * @brief Operator de adunare
     * @param other Celălalt vector
     * @return Vector2D Suma vectorilor
     */
    constexpr Vector2D operator+(const Vector2D& other) const
    {
        return Vector2D{x + other.x, y + other.y};
    }

    /**
     * @brief Operator de scădere
     * @param other Celălalt vector
     * @return Vector2D Diferența vectorilor
     */
    constexpr Vector2D operator-(const Vector2D& other) const
    {
        return Vector2D{x - other.x, y - other.y};
    }

    /**
     * @brief Operator de înmulțire cu scalar
     * @param scalar Scalarul
     * @return Vector2D Vectorul înmulțit cu scalar
     */
    constexpr Vector2D operator*(float scalar) const
    {
        return Vector2D{x * scalar, y * scalar};
    }
};
} // namespace GameLogic
