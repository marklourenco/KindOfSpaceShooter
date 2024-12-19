#include "Particle.h"

void Particle::Update(float deltaTime) {
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    lifeTime -= deltaTime;

    // Fade out the particle as it nears the end of its life
    float alpha = lifeTime / maxLifeTime;
    color.a = (unsigned char)(255 * alpha);
}

void Particle::Draw() const {
    DrawCircleV(position, size, color);
}

bool Particle::IsAlive() const {
    return lifeTime > 0;
}