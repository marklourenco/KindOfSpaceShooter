#include "Earth.h"
#include "raylib.h"

Earth::Earth(Vector2 startPosition, float size, int health, Color color)
    : position(startPosition), radius(size), health(health), color(color) {}

void Earth::Draw() {
    // Draw Earth as a circle in the center
    DrawCircleV(position, radius, color);

    // Create a rectangle to hold the portion of the texture we want to display
    // Rectangle sourceRect = { 0.0f, 0.0f, (float)earthTexture.width, (float)earthTexture.height };

    // The destination rectangle (where to draw the texture)
    // Rectangle destRect = { position.x - radius, position.y - radius, radius * 2, radius * 2 };

    // Draw the image inside the destination rectangle
    // DrawTexturePro(earthTexture, sourceRect, destRect, Vector2{ 0, 0 }, 0.0f, WHITE);

    const int barWidth = 500;  // Width of the health bar
    const int barHeight = 20;  // Height of the health bar
    const int rectWidth = barWidth / 10;  // Width of each health rectangle

    // Draw the health bar at the bottom of the screen
    for (int i = 0; i < 10; i++) {
        Color color = (i < health) ? GREEN : DARKGRAY;  // Green if health is intact, dark gray if destroyed
        DrawRectangle(100 + i * rectWidth, GetScreenHeight() - barHeight - 10, rectWidth, barHeight, color);
    }
}

void Earth::LoseLife() {
    if (health > 0) {
        health--;
        color.a -= 25;
    }
    else {
        color.a = 0;
    }
}

bool Earth::IsAlive() const {
    return health > 0;
}
