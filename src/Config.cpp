
#include <raylib.h>
#include <deque>
//#include <raymath.h>
#include "../include/Config.h"

Vector2 Config::GetPixelPos(Vector2 gridPos) 
{
    float x = Config::offset + gridPos.x * Config::cellSize;
    float y = Config::offset + gridPos.y * Config::cellSize;
    return Vector2{x, y};
}

bool Config::ElementInDeque(Vector2 element, std::deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i], element))
        {
            return true;
        }
    }
    return false;
}