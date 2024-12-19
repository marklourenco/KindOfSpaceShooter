#include "PowerUp.h"

void PowerUp::Draw() const {
    // Choose color based on powerup type
    Color drawColor;
    if (type == PowerUpType::SpeedBoost) {
        drawColor = YELLOW;  // SpeedBoost powerup is yellow
    }
    else if (type == PowerUpType::MultiShot) {
        drawColor = ORANGE;  // MultiShot powerup is orange
    }
    else if (type == PowerUpType::ScreenClear) {
        drawColor = SKYBLUE;  // ScreenClear powerup is skyblue
    }

    // Draw the powerup with the chosen color
    DrawCircleV(position, radius, drawColor);
}