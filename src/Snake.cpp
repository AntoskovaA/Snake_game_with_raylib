#include <raylib.h>
#include <raymath.h>
#include <deque>
#include "../include/Config.h"
#include "../include/Snake.h"

Snake::Snake(Vector2 start, int size)
{
    for (int i = 0; i < size; i++)
    {
        body.push_back(start);
        start.x--;
    }
}

Snake::Snake(std::deque<Vector2> customBody)
{
    this->body = customBody;
}

void Snake::Draw()
{
    DrawHead();
    for (unsigned int i = 1; i < body.size(); i++)
    {
        Vector2 Pos = Config::GetPixelPos(body[i]);
        Rectangle segment = {Pos.x, Pos.y, (float)Config::cellSize, (float)Config::cellSize};
        DrawRectangleRounded(segment, 0.8, 7, Config::DarkGreen());
    }
}

void Snake::DrawHead()
{
    Vector2 pos = Config::GetPixelPos(body[0]);
    float x = pos.x;
    float y = pos.y;

    Rectangle head = {x, y, (float)Config::cellSize, (float)Config::cellSize};
    DrawRectangleRounded(head, 0.8, 7, Config::DarkGreen());

    float eyeSize = 5;
    float offset = 7;
    Vector2 leftEyePos, rightEyePos;

    if (direction.x == 1)
    {
        leftEyePos = {x + Config::cellSize - offset, y + offset};
        rightEyePos = {x + Config::cellSize - offset, y + Config::cellSize - offset};
    }
    else if (direction.x == -1)
    {
        leftEyePos = {x + offset, y + offset};
        rightEyePos = {x + offset, y + Config::cellSize - offset};
    }
    else if (direction.y == -1)
    {
        leftEyePos = {x + offset, y + offset};
        rightEyePos = {x + Config::cellSize - offset, y + offset};
    }
    else
    {
        leftEyePos = {x + offset, y + Config::cellSize - offset};
        rightEyePos = {x + Config::cellSize - offset, y + Config::cellSize - offset};
    }
    DrawCircleV(leftEyePos, eyeSize, BLACK);
    DrawCircleV(rightEyePos, eyeSize, BLACK);
}

void Snake::Update()
{

    body.push_front(Vector2Add(body[0], direction));
    if (addSegment == true)
    {
        addSegment = false;
    }
    else
    {
        body.pop_back();
    }
}

void Snake::Reset()
{
    body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    direction = Vector2{1, 0};
}