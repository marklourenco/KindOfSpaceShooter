#pragma once

#include "raylib.h"
#include "Bullet.h"
#include "Earth.h"
#include "iostream"
#include <vector>

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    static const int screenWidth = 1200; // w and h of canvas
    static const int screenHeight = 800;

    Vector2 position;
    float rotation;
    float speed;
    float speedBoostDuration;
    float baseSpeed;
    bool multiShotActive = false;
    float multiShotTimer = 0.0f;
    int lives;
    vector<Bullet*> bullets;

    Player(Vector2 startPosition, float startRotation, float moveSpeed, int initialLives);
    void Update(const Earth& earth, float deltaTime);
    void Draw();
    void LoseLife();
    int GetLives() const;
    void DrawLives() const;
    void ShootBullet();
    void IncreaseSpeed(float amount, float duration);
    void UpdateSpeedBoost(float deltaTime);
    void UpdateMultiShot(float deltaTime);
};

#endif
