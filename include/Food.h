#pragma once
#include <raylib.h>
#include <deque>
#include <vector>
#include "Config.h"

class Food {
public:
    Vector2 position;
    Texture2D texture;

    Food(std::deque<Vector2> snakeBody); // Для початкового створення

    void Draw();
    void SetTexture(Texture2D tex) { texture = tex; }
    Vector2 GenerateRandomCell();
    // Тепер приймає і змію, і список іншої їжі
    Vector2 GenerateRandomPos(std::deque<Vector2>& snakeBody, const std::vector<Food>& allFood);
};