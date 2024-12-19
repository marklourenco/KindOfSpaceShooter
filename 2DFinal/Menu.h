#pragma once

#include "raylib.h"

#ifndef MENU_H
#define MENU_H


class Menu
{
public:
    int x = (float)GetScreenWidth() + 400;
    int y = (float)GetScreenHeight() + 400;
    float width = 350;
    float height = 100;

    Vector2 txtPos = Vector2{};
    int fontSize = height / 2.2;
    Color txtColor = BLACK;

    Rectangle asteroidGame = { (float)x, (float)y, width, height };
    Rectangle exit = { (float)x, (float)y + 120, width, height };

    void Draw();
};

#endif