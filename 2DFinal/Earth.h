#pragma once

#include "raylib.h"

#ifndef EARTH_H
#define EARTH_H

class Earth {
public:
    Vector2 position;
    Color color;
    float radius;
    int health;
    // Texture2D earthTexture = LoadTexture("Images\earth.png");

    Earth(Vector2 startPosition, float size, int health, Color color);
    void Draw();
    void LoseLife();
    bool IsAlive() const;
};

#endif
