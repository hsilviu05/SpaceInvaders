#pragma once

namespace GameLogic
{
namespace GameConstants
{
// Screen dimensions
constexpr float SCREEN_WIDTH = 800.f;
constexpr float SCREEN_HEIGHT = 600.f;
constexpr float SCREEN_TOP = 0.f;
constexpr float SCREEN_LEFT = 0.f;

constexpr float BACKGROUND_SCROLL_SPEED = 25.f;

// Base size for all 8x8 sprites
constexpr float SPRITE_BASE_SIZE = 8.f;

// Player constants
constexpr float PLAYER_WIDTH = 48.f;
constexpr float PLAYER_HEIGHT = 48.f;
constexpr float PLAYER_START_X = 376.f;
constexpr float PLAYER_START_Y = 544.f;
constexpr float PLAYER_SPEED = 300.f;
constexpr float PLAYER_SHOOT_COOLDOWN = 0.5f;

// Alien constants
constexpr int ALIEN_ROWS = 3;
constexpr int ALIEN_COLUMNS = 5;
constexpr float ALIEN_WIDTH = 48.f;
constexpr float ALIEN_HEIGHT = 48.f;
constexpr float ALIEN_SPACING_X = 64.f;
constexpr float ALIEN_SPACING_Y = 64.f;
constexpr float ALIEN_START_X = 248.f;
constexpr float ALIEN_START_Y = 48.f;
constexpr float ALIEN_SPEED = 1.f;
constexpr float ALIEN_MOVE_INTERVAL = 0.f;
constexpr float ALIEN_HORIZONTAL_STEP = 16.f;
constexpr float ALIEN_VERTICAL_STEP = 32.f;
constexpr float ALIEN_HORIZONTAL_SPEED_MULTIPLIER = 0.4f;
constexpr float ALIEN_GAME_OVER_Y = 504.f;

// Bullet constants
constexpr float BULLET_WIDTH = 40.f;
constexpr float BULLET_HEIGHT = 40.f;
constexpr float BULLET_SPEED = 400.f;
constexpr float BULLET_OFFSET_X = 16.f;
constexpr float BULLET_OFFSET_Y = -16.f;

// Scoring
constexpr int POINTS_PER_ALIEN = 100;

// Physics/Movement
constexpr float DIRECTION_LEFT = -1.f;
constexpr float DIRECTION_RIGHT = 1.f;
} // namespace GameConstants
} // namespace GameLogic
