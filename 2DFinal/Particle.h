#pragma once

#include "raylib.h"
#include <iostream>

using namespace std;

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
public:
    Vector2 position;
    Vector2 velocity; // Movement direction and speed
    float size= 100;
    float lifeTime;
    float maxLifeTime;
    Color color = RED;

    Particle(Vector2 pos, Vector2 vel, float s, float life, Color c)
        : position(pos), velocity(vel), size(s), lifeTime(life), maxLifeTime(life), color(c) {}

    void Update(float deltaTime);

    void Draw() const;

    bool IsAlive() const;
};

#endif