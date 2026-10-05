# Snake Game
A classic Snake Game built with C++ and SFML (Simple and Fast Multimedia Library).
The game supports both Single Player and 2 Player modes, with different difficulty levels.

## Features
- Single Player and 2 Players mode
- Medium and Hard difficulty levels
- Snake movement and growth
- Food spawning and collection
- Score tracking
- Self-collision detection
- Collision with another snake
- Edge-of-board collision detection
- Game Over screen
- Play Again option

## Controls
### Single Player
| Key   | Action     |
| ----- | ---------- |
| W or ↑ | Move Up    |
| S or ↓ | Move Down  |
| A or ← | Move Left  |
| D or → | Move Right |

### 2 Players
**Player 1**
| Key | Action     |
| --- | ---------- |
| ↑   | Move Up    |
| ↓   | Move Down  |
| ←   | Move Left  |
| →   | Move Right |

**Player 2**
| Key | Action     |
| --- | ---------- |
| W   | Move Up    |
| S   | Move Down  |
| A   | Move Left  |
| D   | Move Right |

## Technologies
* C++
* SFML
* GNU/Linux
* Make


## Installation
### 1. Install the compiler and Make
sudo apt update
sudo apt install g++ make

### 2. Install SFML
sudo apt install libsfml-dev

## Run
make
./snake

## Clean
make clean

## Gameplay
When the game starts, choose between:

- Single — play against yourself and collect food to increase your score
- 2 players control separate snakes and compete on the same board
After selecting the game mode, choose a difficulty level and start playing
The game ends when a snake:
* Hits itself
* Hits the edge of the window
* Hits the other snake in PVP mode
After Game Over, the player can choose to play again or exit