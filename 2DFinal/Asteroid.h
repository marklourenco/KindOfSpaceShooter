#pragma once

#include "raylib.h"
#include "PowerUp.h"
#include <vector>

using namespace std;

#ifndef ASTEROID_H
#define ASTEROID_H

class Asteroid {
public:
    static const int screenWidth = 1200; // w and h of canvas
    static const int screenHeight = 800;

    Vector2 position = { 100, 100 };
    Vector2 velocity;    // Direction and speed of movement
    Color color;
    float radius;        // Size of the asteroid
    int health;
    float speed;

    float curvatureFactor, curvatureDirection, angleChange;

    Asteroid(Vector2 startPosition, float moveSpeed, float size, int health, Color color);
    void Update();
    void Draw();
    bool IsAlive();
};

#endif
