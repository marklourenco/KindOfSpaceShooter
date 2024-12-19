#ifndef POWERUP_H
#define POWERUP_H

#include "raylib.h"

enum class PowerUpType {
    SpeedBoost,
    MultiShot,
    ScreenClear
};

class PowerUp {
public:
    Vector2 position;
    float radius;
    PowerUpType type;
    Color color;

    PowerUp(Vector2 pos, PowerUpType t)
        : position(pos), radius(10.0f), type(t), color(ORANGE) {}

    void Draw() const;
};


#endif
