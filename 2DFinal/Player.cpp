#include "Player.h"
#include "raylib.h"
#include "Earth.h"
#include <cmath>

Player::Player(Vector2 startPosition, float startRotation, float moveSpeed, int startLives)
    : position(startPosition), rotation(startRotation), speed(moveSpeed), baseSpeed(moveSpeed),
    speedBoostDuration(0.0f), lives(startLives) {}

void Player::Update(const Earth& earth, float deltaTime) {
    // Move forward/backward with W/S (up/down)
    if (IsKeyDown(KEY_W)) {
        Vector2 newPosition = position;
        newPosition.x += speed * sinf(rotation);  // Move horizontally
        newPosition.y -= speed * cosf(rotation);  // Move vertically

        // Check if the new position is inside the earth circle
        float distX = newPosition.x - earth.position.x;
        float distY = newPosition.y - earth.position.y;
        float distance = sqrt(distX * distX + distY * distY);

        // If the distance between player and earth is greater than earth's radius plus player's radius, move
        if (distance > (earth.radius + 20)) {
            position = newPosition;  // Update position only if not colliding with earth
        }
    }

    if (IsKeyDown(KEY_S)) {
        Vector2 newPosition = position;
        newPosition.x -= speed * sinf(rotation);  // Move horizontally
        newPosition.y += speed * cosf(rotation);  // Move vertically

        // Check if the new position is inside the earth circle
        float distX = newPosition.x - earth.position.x;
        float distY = newPosition.y - earth.position.y;
        float distance = sqrt(distX * distX + distY * distY);

        // If the distance between player and earth is greater than earth's radius plus player's radius, move
        if (distance > (earth.radius + 20)) {
            position = newPosition;  // Update position only if not colliding with earth
        }
    }

    // Rotate left/right with A/D (left/right)
    if (IsKeyDown(KEY_A)) {
        rotation -= 0.06f;  // Rotate counterclockwise
    }
    if (IsKeyDown(KEY_D)) {
        rotation += 0.06f;  // Rotate clockwise
    }

    // Adjust to allow a margin of 10 pixels around the screen edges
    const int margin = 20;

    if (position.x < margin) position.x = margin;  // Clamp left
    if (position.x > screenWidth - margin) position.x = screenWidth - margin;  // Clamp right
    if (position.y < margin) position.y = margin;  // Clamp top
    if (position.y > screenHeight - margin) position.y = screenHeight - margin;  // Clamp bottom

    // Shoot a bullet when left click is pressed
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        ShootBullet();
    }

    // Update each bullet in the vector
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        (*it)->Update();

        // Remove bullet if it's off-screen
        if ((*it)->IsOffScreen()) {
            delete* it;  // Free memory
            it = bullets.erase(it);  // Remove from vector
        }
        else {
            ++it;  // Move to next bullet
        }
    }

    // Update the speed boost timer
    UpdateSpeedBoost(GetFrameTime()); // Pass the time elapsed since the last frame

    UpdateMultiShot(deltaTime);
}


void Player::LoseLife() {
    if (lives > 0) {
        lives--;
    }
}

Vector2 RotateVector2(Vector2 point, float angle) {
    // Applying the 2D rotation matrix to the point
    Vector2 rotatedPoint;
    rotatedPoint.x = point.x * cosf(angle) - point.y * sinf(angle);
    rotatedPoint.y = point.x * sinf(angle) + point.y * cosf(angle);
    return rotatedPoint;
}

void Player::Draw() {
    // Define the points of the triangle relative to the player's position
    Vector2 points[3] = {
        {0, -20},   // Top vertex of the triangle (relative to the center, pointing upwards)
        {-20, 20},  // Bottom-left vertex
        {20, 20}    // Bottom-right vertex
    };

    // Rotate points based on the player's rotation angle
    for (int i = 0; i < 3; i++) {
        // Rotate the points relative to the player's center (position)
        Vector2 offset = { points[i].x, points[i].y };  // Use the points as offsets from center
        Vector2 rotatedPoint = RotateVector2(offset, rotation);
        points[i].x = rotatedPoint.x + position.x;  // Add position back
        points[i].y = rotatedPoint.y + position.y;  // Add position back
    }

    // Draw the triangle using the rotated points
    DrawTriangle(points[0], points[1], points[2], WHITE);

    DrawLives();
}

int Player::GetLives() const {
    return lives;
}

// Draw lives on the bottom-left corner of the screen
void Player::DrawLives() const {
    DrawText("LIVES: ", 12, screenHeight - 55, 20, WHITE);

    // Draw the player's remaining lives as squares
    const int squareSize = 20;
    for (int i = 0; i < lives; i++) {
        DrawRectangle(10 + (i * (squareSize + 5)), screenHeight - 30, squareSize, squareSize, WHITE);
    }
}

void Player::ShootBullet() {
    float bulletSpeed = 10.0f;
    float bulletSize = 5.0f;

    // Main bullet
    Vector2 direction = { sinf(rotation), -cosf(rotation) };
    Bullet* newBullet = new Bullet(position, direction, bulletSpeed, bulletSize);
    bullets.push_back(newBullet);

    // Extra bullets if MultiShot is active
    if (multiShotActive) {
        float angleOffset = 0.2f;  // Angle offset for extra bullets

        // Left bullet
        Vector2 leftDirection = { sinf(rotation - angleOffset), -cosf(rotation - angleOffset) }; // Adjust direction
        Bullet* leftBullet = new Bullet(position, leftDirection, bulletSpeed, bulletSize);
        bullets.push_back(leftBullet);

        // Right bullet
        Vector2 rightDirection = { sinf(rotation + angleOffset), -cosf(rotation + angleOffset) }; // Adjust direction
        Bullet* rightBullet = new Bullet(position, rightDirection, bulletSpeed, bulletSize);
        bullets.push_back(rightBullet);
    }
}


void Player::IncreaseSpeed(float amount, float duration) {
    speed += amount;
    speedBoostDuration = duration;
}

void Player::UpdateSpeedBoost(float deltaTime) {
    if (speedBoostDuration > 0) {
        speedBoostDuration -= deltaTime;
        if (speedBoostDuration <= 0) {
            speed = baseSpeed; // Reset speed to base value
            speedBoostDuration = 0.0f;
        }
    }
}

void Player::UpdateMultiShot(float deltaTime) {
    if (multiShotActive) {
        multiShotTimer -= deltaTime;
        if (multiShotTimer <= 0) {
            multiShotActive = false;  // Deactivate multi-shot effect
        }
    }
}
