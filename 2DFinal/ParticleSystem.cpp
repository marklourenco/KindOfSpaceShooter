#include "ParticleSystem.h"

void ParticleSystem::AddParticle(Vector2 position, Vector2 velocity, float size, float lifeTime, Color color) {
    particles.emplace_back(position, velocity, size, lifeTime, color);
}

void ParticleSystem::Update(float deltaTime) {
    for (auto it = particles.begin(); it != particles.end();) {
        it->Update(deltaTime);

        if (!it->IsAlive()) {
            it = particles.erase(it);
        }
        else {
            ++it;
        }
    }
}

void ParticleSystem::Draw() const {
    for (const Particle& particle : particles) {
        particle.Draw();
    }
}