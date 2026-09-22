# BlockForge

A modular Tetris game engine implemented from scratch in C.

## Overview

BlockForge is a terminal-based Tetris implementation built using C.  
The project focuses on designing core game engine components such as game loops, board management, tetromino handling, collision detection, and state management without using external game engines.

## Features

- Custom game loop implementation
- 10x20 game board system
- Tetromino generation and movement
- Piece rotation mechanics
- Collision detection
- Line clearing system
- Score tracking
- Level progression

## Tech Stack

- C Programming Language
- GCC Compiler
- Makefile
- Git/GitHub

## Project Structure

```
BlockForge/
│
├── src/
│   ├── main.c
│   ├── game.c
│   ├── board.c
│   ├── piece.c
│   ├── input.c
│   ├── renderer.c
│   └── score.c
│
├── include/
├── Makefile
└── README.md
```

## Build and Run

Clone the repository:

```bash
git clone https://github.com/<username>/BlockForge.git
```

Navigate to the project:

```bash
cd BlockForge
```

Compile:

```bash
make
```

Run:

```bash
./blockforge
```

## Learning Objectives

This project explores:

- Game loop architecture
- Data structures in C
- Collision detection algorithms
- Memory management
- Modular software design

## Future Enhancements

- Improved rendering system
- Save/load game state
- Next piece preview
- AI-based gameplay
- SDL2 graphical interface

## Author

Your Name