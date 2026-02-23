#include "Food.h"
#include <raymath.h>
Food::Food(std::deque<Vector2> snakeBody) {
    Image image = LoadImage("Graphics/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    // При першому створенні передаємо пустий вектор, щоб не було помилки
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

        // Перевірка 1: Чи не на змії?
        if (Config::ElementInDeque(newPos, snakeBody)) {
            badPosition = true;
            continue;
        }

        // Перевірка 2: Чи не на іншій їжі?
        for (const auto& f : allFood) {
            // Перевіряємо, чи позиція збігається з іншою їжею (крім себе самої за адресою)
            if (&f != this && Vector2Equals(newPos, f.position)) {
                badPosition = true;
                break;
            }
        }
    }
    return newPos;
}