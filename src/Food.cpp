#include "Food.h"
#include <raymath.h>
Food::Food(std::deque<Vector2> snakeBody) {
    Image image = LoadImage("Graphics/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    position = GenerateRandomCell(); 
}


void Food::Draw() {
    Vector2 pixelPos = Config::GetPixelPos(position);
    DrawTexture(texture, pixelPos.x, pixelPos.y, WHITE);
}

Vector2 Food::GenerateRandomCell() {
    return Vector2{(float)GetRandomValue(0, Config::cellCount - 1), (float)GetRandomValue(0, Config::cellCount - 1)};
}

Vector2 Food::GenerateRandomPos(std::deque<Vector2>& snakeBody, const std::vector<Food>& allFood) {
    Vector2 newPos;
    bool badPosition = true;

    while (badPosition) {
        newPos = GenerateRandomCell();
        badPosition = false;

        if (Config::ElementInDeque(newPos, snakeBody)) {
            badPosition = true;
            continue;
        }

        for (const auto& f : allFood) {
            if (&f != this && Vector2Equals(newPos, f.position)) {
                badPosition = true;
                break;
            }
        }
    }
    return newPos;
}