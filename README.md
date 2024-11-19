# 2048
2048 Console Version is a C++ implementation of the classic 2048 puzzle game. Players merge numbered tiles by sliding them across the grid to achieve the highest possible score. This console-based game offers features such as adjustable grid sizes, leaderboard rankings, and a save/resume option.

Features
Classic Gameplay: Move tiles in four directions (up, down, left, right) to combine numbers.
Dynamic Grid Sizes:
4x4 grid: Default starting size.
6x6 grid: Unlocked at 512 points.
8x8 grid: Unlocked at 1024 points.
Leaderboard: Tracks the top 10 players based on their scores.
Save & Resume: Pause the game and return to your progress later.
Dynamic Scoring: Calculates your score based on tile merges.

How to Play
Controls:

Arrow Keys: Slide tiles in the corresponding direction.
ESC: Pause or return to the main menu.
N: Start a new game.
C: Continue a paused game.
L: View the leaderboard.
Objective:

Merge tiles with the same value to create larger numbers.
Achieve the highest score possible before the board fills up.
Game Over:

The game ends when no more moves are possible.
Installation and Compilation
Prerequisites:

A C++ compiler supporting C++11 or higher (e.g., GCC, MSVC).
Windows OS (uses <conio.h> and <windows.h>).
Steps:

Clone or download the project files.
Open a terminal/IDE and compile the code using:
g++ -o Game2048 Game2048.cpp

Files and Functions
Main Components:

Game structure: Manages the board, grid size, and scoreboard.
movement(): Handles player input for tile sliding.
rand_generator(): Adds new random tiles to the board after moves.
highest(): Updates the highest score dynamically.
board(): Displays the current board state.
pausepage() and GOpage(): Provide pause and game-over screens.
Leaderboard:

ranklist(): Displays the top 10 players.
leaderboard(): Updates and sorts players by score.
Customization
Font Size: Adjust the font size for better visibility using the FontSize(int size) function.

Grid Size: The game transitions automatically to larger grids at higher scores.

Credits:
This project was developed as part of a class team project.

Team members:
-Renad Ibrahim
-Rawan Hany
-Youssed Douban
-Ahmed Fahmy
-Ahmed Farrag













