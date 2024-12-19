#include "Bullet.h"
#include "raylib.h"
#include <cmath> // For sin and cos functions

Bullet::Bullet(Vector2 startPosition, Vector2 direction, float speed, float size)
    : position(startPosition), velocity({ direction.x * speed, direction.y * speed }), radius(size) {}


void Bullet::Update() {
    // Move the bullet
    position.x += velocity.x;
    position.y += velocity.y;
}

void Bullet::Draw() {
    // Draw the bullet as a small circle
    DrawCircleV(position, radius, WHITE);
}

bool Bullet::IsOffScreen() {
    // Check if the bullet has moved off the screen
    return position.x < 0 || position.x > GetScreenWidth() || position.y < 0 || position.y > GetScreenHeight();
}
