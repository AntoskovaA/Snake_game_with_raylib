#pragma once

#include <raylib.h>
#include <deque>
#include "../include/Config.h"

class Snake
{
public:
    std::deque<Vector2> body;
    Vector2 direction = {1, 0};
    bool addSegment = false;

    Snake(Vector2 start, int size);
    Snake(std::deque<Vector2> customBody);

    void Draw();
    void DrawHead();
    void Update();
    void Reset();
};