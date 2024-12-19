#include "Asteroid.h"
#include "raylib.h"
#include "PowerUp.h"
#include <cstdlib>
#include <ctime>

Asteroid::Asteroid(Vector2 startPosition, float moveSpeed, float size, int health, Color color)
    : position(startPosition), speed(moveSpeed), radius(size), health(health), color(color) {

    if (position.y == 0) {  // Spawned at the top
        velocity = { 0, speed };  // Move downward
    }
    else if (position.y == GetScreenHeight()) {  // Spawned at the bottom
        velocity = { 0, -speed };  // Move upward
    }
    else if (position.x == 0) {  // Spawned at the left
        velocity = { speed, 0 };  // Move right
    }
    else if (position.x == GetScreenWidth()) {  // Spawned at the right
        velocity = { -speed, 0 };  // Move left
    }

    // Randomize the curvature factor for slight random movement
    curvatureFactor = (float)(rand() % 5) / 500.0f;  // Random curvature factor
    curvatureDirection = rand() % 2 == 0 ? 1 : -1;  // Randomize the direction of the curvature (clockwise or counter-clockwise)
}

void Asteroid::Update() {

    // Add a slight curve to the movement by adjusting the angle over time
    // Small random change in velocity direction based on curvature factor
    float angleChange = curvatureFactor * curvatureDirection;

    // Update velocity by rotating it slightly each frame
    float angle = atan2(velocity.y, velocity.x) + angleChange;
    velocity.x = speed * cos(angle);
    velocity.y = speed * sin(angle);

    // Update the position based on velocity
    position.x += velocity.x;
    position.y += velocity.y;

    // Check if the circle has hit the border and loop to the opposite side
    if (position.x < 0) {
        position.x = GetScreenWidth();  // Loop left to right
        position = { (float)screenWidth, (float)(rand() % screenHeight) };
    }
    if (position.x > GetScreenWidth()) {
        position.x = 0;  // Loop right to left
        position = { 0, (float)(rand() % screenHeight) };
    }
    if (position.y < 0) {
        position.y = GetScreenHeight();  // Loop top to bottom
        position = { (float)(rand() % screenWidth), (float)screenHeight };
    }
    if (position.y > GetScreenHeight()) {
        position.y = 0;  // Loop bottom to top
        position = { (float)(rand() % screenWidth), 0 };
    }
}

void Asteroid::Draw() {
    // Draw the circle at its current position with its radius and health
    // Color color = (health == 3) ? RED : (health == 2) ? ORANGE : GREEN;  // Color based on health
    DrawCircleV(position, radius, color);
}

bool Asteroid::IsAlive() {
    return health > 0;
}
