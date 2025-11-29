#pragma once

namespace GameLogic
{
struct Vector2D
{
    float x{};
    float y{};

    constexpr Vector2D() = default;
    constexpr Vector2D(float xVal, float yVal) : x{xVal}, y{yVal} {}

    constexpr Vector2D operator+(const Vector2D& other) const
    {
        return Vector2D{x + other.x, y + other.y};
    }

    constexpr Vector2D operator-(const Vector2D& other) const
    {
        return Vector2D{x - other.x, y - other.y};
    }

    constexpr Vector2D operator*(float scalar) const
    {
        return Vector2D{x * scalar, y * scalar};
    }
};
} // namespace GameLogic
