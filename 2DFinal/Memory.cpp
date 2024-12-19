#include "Memory.h"
#include "raylib.h"
#include "Player.h"
#include "Asteroid.h"
#include "Earth.h"
#include "Bullet.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void Memory::Main() {
    Start(); // Initialize player and settings

    InitWindow(screenWidth, screenHeight, "Kind Of Space Shooter Game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        BeginDrawing();
        ClearBackground(BLACK);

        Update(deltaTime); // Update all game objects
        Draw();   // Draw all game objects
        EndDrawing();
    }

    // Free memory before closing window
    delete player;
    for (auto& circle : asteroids) {
        delete circle;
    }
    CloseWindow();
}

void Memory::Start() {
    // Initialize the player and earth with 3 lives
    player = new Player({ 400, 400 }, 0.0f, 5.0f, 3); // pos, rot, speed, lives
    earth = new Earth({ screenWidth / 2, screenHeight / 2 }, 50, 10, GREEN);  // pos, size, lives, color
    lastSpawnTime = 0.0f; // keep track of the last time a circle was spawned, to spawn a new one
    totalSpawnedAsteroids = 0; 
    srand(time(0));  // Seed random number generator
    InitializeStars(200); // stars for the background
}

void Memory::Update(float deltaTime) {

    // Update stars (light flicker)
    UpdateStars();

    float currentTime = GetTime();

	// Game state
    switch (state)
    {
    case Intro:
        // Menu check if button pressed
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(GetMousePosition(), menu.asteroidGame)) {
                state = Game;
            }
            if (CheckCollisionPointRec(GetMousePosition(), menu.exit)) {
                state = GameOver;
            }
        }
        break;
    case Game:
		// Update the particle system
        particleSystem.Update(deltaTime);

        // Update the player's state (movement, rotation)
        player->Update(*earth, deltaTime);

        // Update and check for the spawning of circles
        if (currentTime - lastSpawnTime >= 1.0f && totalSpawnedAsteroids < 100) {
            SpawnAsteroid();
            lastSpawnTime = currentTime;
        }

        // Update each asteroid's position
        for (auto& asteroid : asteroids) {
            asteroid->Update();
        }

        // Check for collisions between the player and asteroids
        CheckCollisionWithAsteroids();
        // Check for collisions between the earth and asteroids
        CheckCollisionWithEarth();
        // Check for collisions between the player and powerups
        CheckPowerUpCollisions();
        // Check for collisions between bullets and asteroids
        CheckCollisionWithBullets();
        // Check for collisions between asteroids
        CheckCollisionBetweenAsteroids();

		// Check if all asteroids have been destroyed
        if (asteroidCount == 0) {
			state = GameOver;
		}
        break;
    case GameOver:
        break;
    }
}

void Memory::Draw() {

    // Draw background stars
    DrawStars();

    switch (state)
    {
    case Intro:
        // Draw Menu
        menu.Draw();
        break;
    case Game:
        // Draw particles
        particleSystem.Draw();
        // Draw all power-ups
        for (PowerUp* powerUp : powerUps) {
            powerUp->Draw();
        }
        // Draw all asteroids
        for (auto& asteroid : asteroids) {
            asteroid->Draw();
        }
        // Draw all bullets
        for (auto& bullet : player->bullets) {
            bullet->Draw();
        }
        // Draw earth and its life bar
        earth->Draw();
        // Draw the player and its lives
        player->Draw();
        break;
    case GameOver:
        break;
    }

    // Draw asteroid count
    if (state == Game) {
        // Asteroid Count
        string asteroidCountTxt = "Asteroid Count: " + to_string(asteroidCount);
        int xAsteroid = 500;
        int yAsteroid = 20;
        float widthAsteroid = 200;
        float heightAsteroid = 20;

        Vector2 txtPosAsteroid = Vector2{};
        int fontSizeAsteroid = (heightAsteroid / 2.2) + 10;
        Color txtColorAsteroid = BLACK;

        Rectangle gameOver = { (float)xAsteroid, (float)yAsteroid, widthAsteroid, heightAsteroid };

        DrawRectangle(gameOver.x, gameOver.y, gameOver.width, gameOver.height, WHITE);

        float txtWidthAsteroid = MeasureText(asteroidCountTxt.c_str(), fontSizeAsteroid);
        txtPosAsteroid = { gameOver.x + gameOver.width / 2 - txtWidthAsteroid / 2,
                   gameOver.y + gameOver.height / 2 - fontSizeAsteroid / 2 };
        DrawText(asteroidCountTxt.c_str(), txtPosAsteroid.x, txtPosAsteroid.y, fontSizeAsteroid, txtColorAsteroid);
    }
    // Draw game over
    if (state == GameOver) {
        string gameOverTxt;
        if (player->lives <= 0 || earth->health <= 0) {
            gameOverTxt = "GAME OVER";
        }
        else {
            gameOverTxt = "YOU WIN";
        }
        int x = 425;
        int y = 350;
        float width = 350;
        float height = 100;

        Vector2 txtPos = Vector2{};
        int fontSize = height / 2.2;
        Color txtColor = BLACK;

        Rectangle gameOver = { (float)x, (float)y, width, height };

        DrawRectangle(gameOver.x, gameOver.y, gameOver.width, gameOver.height, WHITE);

        float txtWidth = MeasureText(gameOverTxt.c_str(), fontSize);
        txtPos = { gameOver.x + gameOver.width / 2 - txtWidth / 2,
                   gameOver.y + gameOver.height / 2 - fontSize / 2 };
        DrawText(gameOverTxt.c_str(), txtPos.x, txtPos.y, fontSize, txtColor);
    }
}

void Memory::SpawnAsteroid() {
    if (totalSpawnedAsteroids >= 100) return;

    // Randomly choose between 3 types of asteroids
    int randomType = rand() % 3;  // Randomly choose between 0, 1, or 2

    float size, speed;
    int health;
    Vector2 spawnPosition;

    // Assign properties based on type
    if (randomType == 0) {  // Small, fast, 1 health
        size = 10;
        speed = 4.5f;
        health = 1;
    }
    else if (randomType == 1) {  // Medium, normal speed, 2 health
        size = 20;
        speed = 3.0f;
        health = 2;
    }
    else {  // Big, slow, 3 health
        size = 30;
        speed = 1.5f;
        health = 3;
    }

    // Spawn the circle at a random edge
    int edge = rand() % 4;
    if (edge == 0) {  // Top edge
        spawnPosition = { (float)(rand() % screenWidth), 0 };
    }
    else if (edge == 1) {  // Bottom edge
        spawnPosition = { (float)(rand() % screenWidth), (float)screenHeight };
    }
    else if (edge == 2) {  // Left edge
        spawnPosition = { 0, (float)(rand() % screenHeight) };
    }
    else {  // Right edge
        spawnPosition = { (float)screenWidth, (float)(rand() % screenHeight) };
    }

    // Create the asteroid and add it to the list
    Asteroid* newAsteroid = new Asteroid(spawnPosition, speed, size, health, GRAY);
    asteroids.push_back(newAsteroid);

    totalSpawnedAsteroids++;
}

void Memory::CheckCollisionWithAsteroids() {
    // Check for collision between the player and each asteroid
    for (auto it = asteroids.begin(); it != asteroids.end(); ) {
        Asteroid* asteroid = *it;

        // Check if the player's position is close enough to the circle
        float distX = player->position.x - asteroid->position.x;
        float distY = player->position.y - asteroid->position.y;
        float distance = sqrt(distX * distX * 1.5 + distY * distY * 1.5);

        // If the distance is less than the sum of the player's radius and the circle's radius, it's a collision
        if (distance < 20 + asteroid->radius) {
            // Player loses 1 life
            player->LoseLife();

            // Remove the collided asteroid
            it = asteroids.erase(it);

            // 10% chance of dropping a powerup
            if ((rand() % 10) < 1) {
                PowerUpType type;

                int randomChoice = rand() % 3; // Randomly choose between 0, 1, or 2
                if (randomChoice == 0) {
                    type = PowerUpType::SpeedBoost;
                }
                else if (randomChoice == 1) {
                    type = PowerUpType::MultiShot;
                }
                else {
                    type = PowerUpType::ScreenClear; // New powerup
                }

                powerUps.push_back(new PowerUp(asteroid->position, type));
            }

            asteroidCount--;

            // Create fire particles at asteroid's position
            for (int i = 0; i < 20; i++) {
                Vector2 velocity = {
                    (float)(rand() % 200 - 100) / 100.0f, // Random X direction
                    (float)(rand() % 200 - 100) / 100.0f  // Random Y direction
                };
                particleSystem.AddParticle(
                    asteroid->position,
                    velocity,
                    (float)(rand() % (int)asteroid->radius + (int)asteroid->radius - 5), // Random size between 1 and 3
                    1.0f,                   // Lifetime in seconds
                    RED                    // Smoke color
                );
            }

            // Stop the loop if player has no lives left
            if (player->GetLives() <= 0) {
                // Handle game over
                state = GameOver;
                break;
            }
        }
        else {
            ++it; // Move to next asteroid if no collision
        }
    }
}

void Memory::CheckCollisionWithEarth() {
    // Check for collisions between asteroids and earth
    for (auto it = asteroids.begin(); it != asteroids.end(); ) {
        Asteroid* asteroid = *it;

        float distX = earth->position.x - asteroid->position.x;
        float distY = earth->position.y - asteroid->position.y;
        float distance = sqrt(distX * distX + distY * distY);

        // If the distance is less than the sum of Earth and circle's radius, it's a collision
        if (distance < earth->radius + asteroid->radius) {
            // Earth loses 1 life
            earth->LoseLife();

            asteroidCount--;

            // Remove the collided asteroid
            it = asteroids.erase(it);

            // Create fire particles at asteroid's position
            for (int i = 0; i < 20; i++) {
                Vector2 velocity = {
                    (float)(rand() % 200 - 100) / 100.0f, // Random X direction
                    (float)(rand() % 200 - 100) / 100.0f  // Random Y direction
                };
                particleSystem.AddParticle(
                    asteroid->position,
                    velocity,
                    (float)(rand() % (int)asteroid->radius + (int)asteroid->radius - 5), // Random size between 1 and 3
                    1.0f,                   // Lifetime in seconds
                    RED                    // Smoke color
                );
            }

            // Stop the loop if Earth has no lives left
            if (!earth->IsAlive()) {
                // Handle game over
                state = GameOver;
                break;
            }
        }
        else {
            ++it;  // Move to next circle if no collision
        }
    }
}

void Memory::CheckPowerUpCollisions() {
    for (auto it = powerUps.begin(); it != powerUps.end(); ) {
        PowerUp* powerUp = *it;

        float distX = player->position.x - powerUp->position.x;
        float distY = player->position.y - powerUp->position.y;
        float distance = sqrt(distX * distX + distY * distY);

        if (distance < 20 + powerUp->radius) {
            // Apply powerup effect
            if (powerUp->type == PowerUpType::SpeedBoost) {
                player->IncreaseSpeed(5.0f, 5);  // 5 seconds of speed boost
            }
            else if (powerUp->type == PowerUpType::MultiShot) {
                player->multiShotActive = true;
                player->multiShotTimer = 10.0f;  // 10 seconds of multi-shot
            }
            else if (powerUp->type == PowerUpType::ScreenClear) {
                FireAtAllAsteroids(); // Fire at all asteroids
            }

            // Remove the powerup
            delete powerUp;
            it = powerUps.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Memory::CheckCollisionWithBullets() {
    for (auto& bullet : player->bullets) {
        for (auto it = asteroids.begin(); it != asteroids.end(); ) {
            bool bulletDestroyed = false;
            Asteroid* asteroid = *it;

            // Check for collision between bullet and circle
            float distX = bullet->position.x - asteroid->position.x;
            float distY = bullet->position.y - asteroid->position.y;
            float distance = sqrt(distX * distX + distY * distY);

            // If the distance is less than the sum of the bullet radius and circle's radius, it's a collision
            if (distance < bullet->radius + asteroid->radius) {
                // Deal damage to the asteroid (circle)
                asteroid->health--;
                asteroid->color.a -= 50;

                // Check if the asteroid is destroyed
                if (asteroid->health <= 0) {
                    asteroidCount--;
                    it = asteroids.erase(it); // Destroy the asteroid
                    // 10% chance of dropping a powerup
                    if ((rand() % 10) < 1) {
                        PowerUpType type;

                        int randomChoice = rand() % 3; // Randomly choose between 0, 1, or 2
                        if (randomChoice == 0) {
                            type = PowerUpType::SpeedBoost;
                        }
                        else if (randomChoice == 1) {
                            type = PowerUpType::MultiShot;
                        }
                        else {
                            type = PowerUpType::ScreenClear; // New powerup
                        }

                        powerUps.push_back(new PowerUp(asteroid->position, type));
                    }

                    // Create fire particles at asteroid's position
                    for (int i = 0; i < 20; i++) {
                        Vector2 velocity = {
                            (float)(rand() % 200 - 100) / 100.0f, // Random X direction
                            (float)(rand() % 200 - 100) / 100.0f  // Random Y direction
                        };
                        particleSystem.AddParticle(
                            asteroid->position,
                            velocity,
                            (float)(rand() % (int)asteroid->radius + (int)asteroid->radius - 5), // Random size between 1 and 3
                            1.0f,                   // Lifetime in seconds
                            RED                    // Smoke color
                        );
                    }
                }
                else {
                    ++it; // Continue to the next circle if it's not destroyed
                }

                // Remove the bullet after collision
                player->bullets.erase(remove(player->bullets.begin(), player->bullets.end(), bullet), player->bullets.end());

                break; // Exit the loop after dealing with the collision
            }
            else {
                ++it; // Move to the next asteroid if no collision
            }
        }
    }
}

void Memory::CheckCollisionBetweenAsteroids() {
    for (auto it1 = asteroids.begin(); it1 != asteroids.end(); ++it1) {
        Asteroid* asteroid1 = *it1;

        // Compare it with every other asteroid (to check all pairs)
        for (auto it2 = next(it1); it2 != asteroids.end(); ++it2) {
            Asteroid* asteroid2 = *it2;

            // Check for collision between asteroid1 and asteroid2
            float distX = asteroid1->position.x - asteroid2->position.x;
            float distY = asteroid1->position.y - asteroid2->position.y;
            float distance = sqrt(distX * distX + distY * distY);

            // If the distance between the centers is less than the sum of the radii, there's a collision
            if (distance < asteroid1->radius + asteroid2->radius) {

                // 10% chance of dropping a powerup
                if ((rand() % 10) < 1) {
                    PowerUpType type;

                    int randomChoice = rand() % 3; // Randomly choose between 0, 1, or 2
                    if (randomChoice == 0) {
                        type = PowerUpType::SpeedBoost;
                    }
                    else if (randomChoice == 1) {
                        type = PowerUpType::MultiShot;
                    }
                    else {
                        type = PowerUpType::ScreenClear; // New powerup
                    }

                    powerUps.push_back(new PowerUp(asteroid1->position, type));
                }
                // 10% chance of dropping a powerup
                if ((rand() % 10) < 1) {
                    PowerUpType type;

                    int randomChoice = rand() % 3; // Randomly choose between 0, 1, or 2
                    if (randomChoice == 0) {
                        type = PowerUpType::SpeedBoost;
                    }
                    else if (randomChoice == 1) {
                        type = PowerUpType::MultiShot;
                    }
                    else {
                        type = PowerUpType::ScreenClear; // New powerup
                    }

                    powerUps.push_back(new PowerUp(asteroid2->position, type));
                }

                asteroidCount -= 2;

                // Create fire particles at asteroid's position
                for (int i = 0; i < 20; i++) {
                    Vector2 velocity = {
                        (float)(rand() % 200 - 100) / 100.0f, // Random X direction
                        (float)(rand() % 200 - 100) / 100.0f  // Random Y direction
                    };
                    particleSystem.AddParticle(
                        asteroid1->position,
                        velocity,
                        (float)(rand() % (int)asteroid1->radius + (int)asteroid1->radius - 5), // Random size between 1 and 3
                        1.0f,                   // Lifetime in seconds
                        RED                    // Smoke color
                    );
                }
                // Create fire particles at asteroid's position
                for (int i = 0; i < 20; i++) {
                    Vector2 velocity = {
                        (float)(rand() % 200 - 100) / 100.0f, // Random X direction
                        (float)(rand() % 200 - 100) / 100.0f  // Random Y direction
                    };
                    particleSystem.AddParticle(
                        asteroid2->position,
                        velocity,
                        (float)(rand() % (int)asteroid2->radius + (int)asteroid2->radius - 5), // Random size between 1 and 3
                        1.0f,                   // Lifetime in seconds
                        RED                    // Smoke color
                    );
                }

                // Destroy both asteroids
                delete asteroid1;  // Free memory
                delete asteroid2;  // Free memory

                // Remove them from the vector
                it2 = asteroids.erase(it2); // Erase asteroid2

                // Erase circle1
                it1 = asteroids.erase(it1);

                // break the loop
                break;
            }
        }

        // After erasing, we need to check if the outer loop iterator is valid and adjust it
        if (it1 == asteroids.end()) {
            break;  // Exit the outer loop if the iterator is at the end
        }
    }
}

void Memory::InitializeStars(int numStars) {
    for (int i = 0; i < numStars; i++) {
        Star star;
        star.position = { (float)(rand() % screenWidth), (float)(rand() % screenHeight) };
        star.size = (float)(rand() % 3 + 1);  // Random size between 1 and 3
        int brightness = rand() % 156 + 100; // Random brightness between 100 and 255
        star.color = { (unsigned char)brightness, (unsigned char)brightness, (unsigned char)brightness, 255 }; // Grayish white
        stars.push_back(star);
    }
}

void Memory::DrawStars() {
    for (const Star& star : stars) {
        DrawCircleV(star.position, star.size, star.color);
    }
}

void Memory::UpdateStars() {
    for (Star& star : stars) {
        // Randomly adjust brightness by -5, 0, or +5
        int delta = (rand() % 3 - 1) * 5;
        int newBrightness = star.color.r + delta;

        // Clamp brightness between 100 and 255
        newBrightness = max(100, min(255, newBrightness)); // Don't drop below 100

        // Apply the new brightness to the star's color
        star.color = { (unsigned char)newBrightness, (unsigned char)newBrightness, (unsigned char)newBrightness, 255 };
    }
}

void Memory::FireAtAllAsteroids() {
    for (Asteroid* asteroid : asteroids) {
        // Calculate direction vector from the player's position to the asteroid's position
        Vector2 direction = {
            asteroid->position.x - player->position.x,
            asteroid->position.y - player->position.y
        };

        // Normalize the direction vector
        float magnitude = sqrtf(direction.x * direction.x + direction.y * direction.y);
        if (magnitude > 0) {
            direction.x /= magnitude;
            direction.y /= magnitude;
        }

		float bulletSpeed = 30.0f;
		float bulletSize = 10.0f;

        // Create a new bullet aimed at the asteroid
        Bullet* trackingBullet = new Bullet(player->position, direction, bulletSpeed, bulletSize);
        player->bullets.push_back(trackingBullet);
    }
}