#pragma once
#include <raylib.h>
#include <raymath.h>
#include <deque>
#include <vector>

struct Config {
    static const int cellSize = 35;
    static const int cellCount = 25;
    static const int offset = 75;
    static const int foodCount = 5;

    static Color BrightGreen() { return Color{144, 238, 144, 255};; }
    static Color DarkGreen() { return Color{80, 200, 120, 255}; }
    static constexpr double updateInterval = 0.26;

    static Vector2 GetPixelPos(Vector2 gridPos);
    static bool ElementInDeque(Vector2 element, std::deque<Vector2> deque);
};