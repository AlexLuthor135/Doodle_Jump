# Doodle Jump

This project is a clone of the popular game **Doodle Jump**, implemented in C++. The game features dynamic gameplay, including platforms, enemies, abilities, and bullets, with scalable graphics and responsive controls.

## Features

### Core Gameplay
- **Player Movement**: Move left or right using arrow keys to land on platforms and avoid falling.
- **Jumping Mechanics**: The player automatically jumps, with gravity affecting the vertical movement.
- **Platforms**: Platforms are dynamically generated, some of which move vertically.
- **Enemies**: Enemies appear on platforms and must be avoided, defeated using bullets or stomped.
- **Abilities**: Special abilities like rockets and autoshoot can be picked up to enhance gameplay.
- **Lives**: Player gets 5 lives which can be lost after falling or touching an enemy (except from above).

### Graphics and Rendering
- **Dynamic Scaling**: All game elements (player, platforms, enemies, bullets, abilities) scale dynamically based on the window size.
- **Customizable Sprites**: Includes multiple player costumes and enemy types.

### Controls
- **Keyboard**: Use arrow keys to move left or right, as well as choose costumes
- **Mouse**: Click to shoot bullets at enemies.

### Game States
- **Menu**: Select player costume and start the game.
- **Game**: Core gameplay with platforms, enemies, and abilities.
- **End Game**: View score and restart the game.

### Abilities
- **Rocket**: Boost the player vertically to avoid falling.
- **Autoshoot**: Automatically shoot bullets at enemies for a limited duration (20 seconds).

### Collision Detection
- **Player-Platform Collision**: Detect when the player lands on a platform.
- **Player-Enemy Collision**: Detect when the player collides with an enemy.
- **Bullet-Enemy Collision**: Detect when bullets hit enemies.
- **Player-Ability Collision**: Detect when the player picks up an ability.

### Scoring
- **Platforms Passed**: Tracks the number of platforms passed by the player.
- **Distance**: Tracks the total vertical distance traveled by the player.

### Fullscreen and Window Resizing
- **Fullscreen Mode**: Start the game in fullscreen mode.
- **Dynamic Resizing**: Adjust all game elements when the window size changes.

### Key Components

#### Managers
- **GameManager**: Handles player movement, gravity, and game state.
- **PlatformManager**: Manages platform generation and movement.
- **EnemyManager**: Handles enemy generation and movement.
- **BulletManager**: Manages bullets fired by the player.
- **AbilityManager**: Handles abilities like rockets and autoshoot.
- **CollisionManager**: Detects collisions between game elements.

## How to Build and Run

### Prerequisites
- **CMake**: Version 3.16 or higher.
- **SDL3**: Installed on your system.
- **SDL3_image**: Installed on your system.

### Build Instructions
1. Clone the repository:
  ```bash
  https://github.com/AlexLuthor135/Doodle_Jump.git
  cd Doodle_Jump
  ```

2. Build the Project:
  ```bash
  cd Project
  mkdir build
  cd build
  cmake ..
  make
  ```
3. Run instructions

To run the game in a windowed mode with custom dimensions:
```bash
./Project -window WIDTHxHEIGHT
```
Example:
```bash
./Project -window 800x600
```
