#pragma once

#include "raylib.h"
#include "Particle.h"
#include <iostream>
#include <vector>

using namespace std;

#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

class ParticleSystem {
public:
    vector<Particle> particles;

    void AddParticle(Vector2 position, Vector2 velocity, float size, float lifeTime, Color color);

    void Update(float deltaTime);

    void Draw() const;
};


#endif