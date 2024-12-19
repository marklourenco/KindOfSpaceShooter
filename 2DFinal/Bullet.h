#pragma once

#include "raylib.h"

#ifndef BULLET_H
#define BULLET_H

#define DEG2RAD (3.14159f / 180.0f)  // 90 degrees to radians

class Bullet {
public:
    Vector2 position;  // Current position of the bullet
    Vector2 velocity;  // Velocity based on direction
    float radius;      // Radius of the bullet
    bool isActive;     // Whether the bullet is active or not

    Bullet(Vector2 startPosition, Vector2 direction, float speed, float size);
    void Update();
    void Draw();
    bool IsOffScreen();
};

#endif
