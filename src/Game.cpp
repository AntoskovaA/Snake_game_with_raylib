

#include <raylib.h>
#include <raymath.h>
#include <deque>
#include "../include/Config.h"
#include "../include/Snake.h"
#include "../include/Food.h"
#include "../include/Game.h"

bool Game::eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

void Game::DrawSmile()
{
    float startX = GetScreenWidth() / 2 + 170;
    float startY = GetScreenHeight() / 2.0f - 50;
    float thickness = 3.5f;

    DrawLineEx({startX, startY}, {startX, startY + 50}, thickness, BLACK);
    DrawLineEx({startX + 60, startY}, {startX + 60, startY + 50}, thickness, BLACK);

    Vector2 mouthTop = {startX + 30, startY + 70};

    DrawLineEx(mouthTop, {startX, startY + 100}, thickness, BLACK);

    DrawLineEx(mouthTop, {startX + 60, startY + 100}, thickness, BLACK);
}

void Game::DrawWorld()
{
    ClearBackground({236, 255, 220, 255});
    DrawRectangleLinesEx(Rectangle{float(Config::offset) - 5, float(Config::offset) - 5, float(Config::cellSize) * Config::cellCount + 10, float(Config::cellSize) * Config::cellCount + 10}, 5, BLACK);
    for (int i = 0; i < Config::foodCount; i++)
    {
        foods[i].Draw();
    }
    snake.Draw();
}

void Game::DrawGameOver()
{
    ClearBackground({144, 238, 144, 255});
    DrawText("Game Over...", GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 - 25, 50, BLACK);
    DrawSmile();
}

void Game::DrawUI()
{
    DrawTextEx(mainFont, "Snake Game", {float(Config::offset - 5), float(20)},65, 5, BLACK);
    DrawTextEx(mainFont, "Snake Game", {float(Config::offset - 4), float(20)},65, 5, BLACK);
    DrawTextEx(mainFont, "Snake Game", {float(Config::offset - 6), float(20)},65, 5, BLACK);

    DrawTextEx(mainFont, TextFormat("%i", score), {float(Config::offset - 5), float(Config::offset + Config::cellSize * Config::cellCount + 10)}, 50, 4, BLACK);
    DrawTextEx(mainFont, TextFormat("%i", score), {float(Config::offset - 4), float(Config::offset + Config::cellSize * Config::cellCount + 10)}, 50, 4, BLACK);
    DrawTextEx(mainFont, TextFormat("%i", score), {float(Config::offset - 6), float(Config::offset + Config::cellSize * Config::cellCount + 10)}, 50, 4, BLACK);
}

void Game::Update()
{

    if (eventTriggered(Config::updateInterval) && !start && running)
    {
        snake.Update();
        CheckCollisions();
    }
}

void Game::CheckCollisions()
{
    CheckCollisionWithFood();
    CheckColisionWithEdges();
    CheckColisionWithBody();
}

void Game::CheckCollisionWithFood()
{
    for (int i = 0; i < Config::foodCount; i++)
    {
        if (Vector2Equals(snake.body[0], foods[i].position))
        {
            foods[i].position = foods[i].GenerateRandomPos(snake.body, foods);
            snake.addSegment = true;
            score++;
            break;
        }
    }
}

void Game::CheckColisionWithEdges()
{
    if (snake.body[0].x == Config::cellCount || snake.body[0].x == -1)
    {
        GameOver();
    }
    if (snake.body[0].y == Config::cellCount || snake.body[0].y == -1)
    {
        GameOver();
    }
}

void Game::CheckColisionWithBody()
{
    for (unsigned int i = 1; i < snake.body.size(); i++)
    {
        if (Vector2Equals(snake.body[0], snake.body[i]))
        {
            GameOver();
        }
    }
}

void Game::GameOver()
{
    snake.Reset();
    for (int i = 0; i < Config::foodCount; i++)
    {
        foods[i].GenerateRandomPos(snake.body, foods);
    }
    running = false;
    score = 0;
    isOver = true;
}

void Game::DrawStartPage()
{
    ClearBackground(Config::BrightGreen());
    const char *text = "SIMPLE SNAKE";
    int fontSize = 80;

    int textWidth = MeasureText(text, fontSize);

    int posX = GetScreenWidth() / 2 - textWidth / 2;
    int posY = GetScreenHeight() / 2 - 100;

    DrawTextEx(mainFont, text, { (float)posX, (float)posY }, fontSize, 8, WHITE);
    DrawTextEx(mainFont, text, { (float)posX + 1, (float)posY }, fontSize, 8, WHITE);
    DrawTextEx(mainFont, text, { (float)posX - 1, (float)posY }, fontSize, 8, WHITE);
    front_page_snake.Draw();
    DrawTextEx(mainFont, "Press 'space' to start palying", {float(posX), float (GetScreenHeight() / 2 + 130)}, 30, 2, BLACK);
}

void Game::HandleInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        if (start)
        {
            start = false;
            running = true;
        }
        if (isOver)
        {
            isOver = false;
        }
    }
    if (IsKeyPressed(KEY_UP) && snake.direction.y != 1)
    {
        snake.direction = {0, -1};
        if (!start)
            running = true;
    }
    if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1)
    {
        snake.direction = {0, 1};
        if (!start)
            running = true;
    }
    if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1)
    {
        snake.direction = {1, 0};
        if (!start)
            running = true;
    }

    if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1)
    {
        snake.direction = {-1, 0};
        if (!start)
            running = true;
    }
}

Game::Game()
{
    mainFont = LoadFontEx("my_font.ttf", 128, 0, 0);
    Image image = LoadImage("Graphics/mousee.png");
    foodTexture = LoadTextureFromImage(image);
    UnloadImage(image);

    for (int i = 0; i < Config::foodCount; i++)
    {
        Food newFood(snake.body);
        newFood.SetTexture(foodTexture);
        foods.push_back(newFood);
        foods[i].position = foods[i].GenerateRandomPos(snake.body, foods);
    }
}

Game::~Game()
{
    UnloadTexture(foodTexture);
    UnloadFont(mainFont);
}