# Space Shooter Game

## Overview
"Space Shooter" is a 2D arcade-style space shooting game where players control a spaceship and shoot at asteroids while avoiding obstacles. The game features power-ups, particle effects, and a variety of gameplay mechanics such as speed boosts and multi-shot capabilities. Players can shoot at asteroids and collect power-ups to enhance their abilities, all while protecting their lives from collisions and asteroid impacts.

<p align="center">
<img width="598" alt="Menu" src="https://github.com/user-attachments/assets/91e4e3e3-7f00-45ce-8c26-dd8a68946863" />
</p>

![KindOfSpaceShooterDemo](https://github.com/user-attachments/assets/95d78da1-a7d3-47ed-a87e-36533b055154)

## Features
- **Player Control**: Move the spaceship in 2D space with keyboard inputs, and shoot projectiles with the mouse.
- **Asteroid Collision**: Asteroids spawn and move through space, and players must shoot them before they collide with the ship or Earth.
- **Particle Effects**: Explosions are generated when asteroids are destroyed.
- **Power-ups**: Collect power-ups like speed boosts, multi-shot, and screen clears to empower your gameplay.
- **Lives System**: The player and Earth starts with a set number of lives and loses them when hit by asteroids.
- **Stars**: A starry background to enhance the visual appeal of the game.

## Technologies Used
- **C++**: The game is built using C++.
- **raylib**: The game uses the raylib library for graphics and input handling. It provides simple, easy-to-use functions for drawing shapes and handling window events.

## Installation

### Prerequisites
Make sure you have the following installed on your machine:
1. **C++ Compiler**: Ensure you have a C++ compiler like GCC or Clang.
2. **raylib**: You will need to install the raylib library.

#### raylib Installation
Follow the official [raylib installation guide](https://github.com/raysan5/raylib) to install it on your system.

### Clone the Repository
```bash
git clone https://github.com/yourusername/space-shooter.git
cd space-shooter
```

### Compile and Run
Once you have raylib installed and the repository cloned, you can compile and run the game using your preferred method, such as:

1. **Using CMake** (Recommended):
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ./space_shooter
    ```

2. **Manually Compile**:
    ```bash
    g++ -o space_shooter main.cpp Player.cpp Asteroid.cpp Particle.cpp ParticleSystem.cpp PowerUp.cpp Menu.cpp -lraylib -lm -lpthread -ldl -lrt -lX11
    ./space_shooter
    ```

## Gameplay

### Controls
- **W/S**: Move the spaceship forward and backward.
- **A/D**: Rotate the spaceship left and right.
- **Left Mouse Button**: Shoot bullets at asteroids.
- **Collect Power-ups**: Collect power-ups to increase your abilities (SpeedBoost, MultiShot, ScreenClear).
- **Lives**: Your ship starts with a set number of lives. Avoid hitting asteroids to survive!

### Objective
- Protect Earth from dying to asteroids.
- Destroy asteroids before they collide with your spaceship.
- Collect power-ups to increase your abilities and survive longer.
- Survive as long as possible to get the highest score.

## Power-ups

- **SpeedBoost**: Temporarily increases the speed of the player's ship.
- **MultiShot**: Allows the player to shoot multiple bullets at once.
- **ScreenClear**: Shoots all on-screen asteroids.

## File Structure

```
/space-shooter
|-- /src
|   |-- main.cpp          # Main entry point of the game
|   |-- Player.cpp        # Player class logic
|   |-- Asteroid.cpp      # Asteroid class logic
|   |-- Particle.cpp      # Particle logic for explosions
|   |-- ParticleSystem.cpp # Handles particle effects
|   |-- PowerUp.cpp       # Logic for power-ups
|   |-- Menu.cpp          # Game menu logic
|
|-- /assets
|   |-- (Game assets like images and sounds)
|
|-- CMakeLists.txt        # CMake build configuration
|-- README.md             # Project description (this file)
```

## Contributions

If you'd like to contribute to the project, feel free to fork the repository, create a branch for your feature or fix, and then submit a pull request. We welcome all contributions, whether it's bug fixes, new features, or improvements!

### Reporting Issues
If you encounter any bugs or have feature requests, please create an issue on the [Issues](https://github.com/yourusername/space-shooter/issues) page.

## Contact Info
**Gmail**: markjlourencor@gmail.com
**LinkedIn**: https://www.linkedin.com/in/mark-lourenco-0482b3267/

## License
This project is licensed under the MIT License

---
