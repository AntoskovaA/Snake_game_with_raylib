#include <raylib.h>
#include <deque>
#include <raymath.h>
#include <iostream>
#include <string>
#include "../include/Food.h"
#include "../include/Game.h"
#include "../include/Snake.h"


int main()
{
    InitWindow(Config::cellSize * Config::cellCount + 2 * Config::offset, Config::cellSize * Config::cellCount + 2 * Config::offset, "Snake game");
    SetTargetFPS(60);

    Game game;

    while (WindowShouldClose() == false)
    {
        game.Update();
        game.HandleInput();

        BeginDrawing();

        if (game.start)
        {
            game.DrawStartPage();
        }
        else if(game.isOver)
        {
            game.DrawGameOver();
        }
        else
        {
            game.DrawWorld();
            game.DrawUI();
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}