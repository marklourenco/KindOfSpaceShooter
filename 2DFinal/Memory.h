#pragma once

#include "raylib.h"
#include <vector>
#include "Player.h"
#include "Asteroid.h"  // Include the circle class header
#include "Earth.h"  // Include Earth class
#include "Bullet.h"
#include "Menu.h"
#include "ParticleSystem.h"

#ifndef MEMORY_H
#define MEMORY_H

using namespace std;

struct Star {
    Vector2 position;  // Position of the star
    float size;        // Size of the star
    Color color;       // Color of the star
};


enum GameState {
    Intro, Game, GameOver
};

class Memory
{
public:
    static const int screenWidth = 1200; // w and h of canvas
    static const int screenHeight = 800;

    Player* player;           // Pointer to the Player object
    Earth* earth;             // Pointer to the Earth object
    vector<Asteroid*> asteroids; // List of all circles in the game
    vector<PowerUp*> powerUps;
    vector<Star> stars;
    ParticleSystem particleSystem;
    Menu menu;
    GameState state = GameState::Intro;
    int asteroidCount = 100;

    float lastSpawnTime;      // Timer to track spawn delay
    int totalSpawnedAsteroids;  // Count of asteroids spawned

    void Main();
    void Start();
    void Update(float deltaTime);
    void Draw();

    void SpawnAsteroid();
    void CheckCollisionWithAsteroids();
    void CheckCollisionWithEarth();
    void CheckPowerUpCollisions();
    void CheckCollisionWithBullets();
    void CheckCollisionBetweenAsteroids();
    void InitializeStars(int numStars);
    void DrawStars();
    void UpdateStars();
    void FireAtAllAsteroids();

};

#endif
