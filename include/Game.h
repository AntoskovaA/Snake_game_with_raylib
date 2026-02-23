#pragma once

#include <raylib.h>
#include <deque>
#include <vector>
#include "../include/Config.h"
#include "../include/Snake.h"
#include "../include/Food.h"

class Game
{
    double lastUpdateTime = 0;
    bool eventTriggered(double interval);
    Texture2D foodTexture;
    Font mainFont;
    Texture2D gameOver;

public:
    Snake snake = Snake({6, 9}, 3);
    Snake front_page_snake = Snake({Vector2{18, 13}, Vector2{17, 13}, Vector2{16, 13}, Vector2{15, 13}, Vector2{15, 14}, Vector2{15, 15}, Vector2{14, 15}});
    std::vector<Food> foods;
    bool start = true;
    bool running = true;
    int score = 0;
    bool isOver = false;

    void DrawSmile();
    void DrawWorld();
    void DrawUI();
    void DrawStartPage();
    void DrawGameOver();

    void Update();
    void HandleInput();

    void CheckCollisions();
    void CheckCollisionWithFood();
    void CheckColisionWithEdges();
    void CheckColisionWithBody();

    void GameOver();

    Game();

    ~Game();
};