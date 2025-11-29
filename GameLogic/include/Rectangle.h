#pragma once

namespace GameLogic
{
struct Rectangle
{
    float left{};
    float top{};
    float width{};
    float height{};

    constexpr Rectangle() = default;
    constexpr Rectangle(float l, float t, float w, float h) : left{l}, top{t}, width{w}, height{h} {}

    [[nodiscard]] constexpr bool intersects(const Rectangle& other) const
    {
        return !(left + width < other.left || left > other.left + other.width || top + height < other.top ||
                 top > other.top + other.height);
    }

    [[nodiscard]] constexpr float right() const
    {
        return left + width;
    }

    [[nodiscard]] constexpr float bottom() const
    {
        return top + height;
    }
};
} // namespace GameLogic
