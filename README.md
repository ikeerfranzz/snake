
# 🐍 Snake

<p>
  <img alt="Language" src="https://img.shields.io/badge/C%2B%2B-00599C?logo=cplusplus&logoColor=white">
  <img alt="Platform" src="https://img.shields.io/badge/Platform-Windows%20Console-lightgrey">
  <img alt="Status" src="https://img.shields.io/badge/Status-Completed-brightgreen">
</p>

A classic Snake game implemented in **C++**, rendered entirely in the Windows console. The snake grows as it eats, tracks its own tail as a real body (not just a length counter), and the game ends on a wall or self-collision — all running on a fixed-tick game loop with real-time, non-blocking keyboard input.

## 📋 Table of Contents

- [Gameplay](#-gameplay)
- [Features](#-features)
- [Tech Stack](#-tech-stack)
- [Project Structure](#-project-structure)
- [Getting Started](#-getting-started)
- [Controls](#-controls)
- [Author](#-author)
- [Status & License](#-status--license)

---

## 🎮 Gameplay

- **Grid-based board** (20×10) rendered as ASCII art directly in the console, redrawn every frame.
- **Real-time movement** — the snake moves continuously in its current direction; pressing a perpendicular direction key turns it (reversing directly into yourself is disallowed).
- **Growing tail** — eating a fruit (`O`) appends a new segment to the snake's body, which then follows the head one step behind, frame by frame.
- **Collision detection** — the game ends immediately if the head hits a wall or any segment of its own tail.
- **Scoring** — +15 points per fruit eaten, plus +1 point per tail segment every frame (so score scales with both how much you've eaten and how long you survive with a longer snake).
- **Fruit respawn** — after being eaten, the fruit reappears at a random empty cell (guaranteed not to spawn on the snake's head).

## ✨ Features

- Non-blocking keyboard polling via the Windows API (`GetAsyncKeyState`), so movement doesn't pause waiting for input
- Fixed-tick game loop (`std::this_thread::sleep_for`) decoupling game speed from rendering
- Tail implemented as a `std::vector` of positions, shifted each tick to follow the head — a real growing body rather than a simple score counter
- Direction-lock guard (e.g. can't set a vertical direction while already moving vertically) to prevent instant self-collision on a reversed key press

## 🛠️ Tech Stack

| Category | Technology |
|---|---|
| Language | C++ |
| Build System | Visual Studio (`.sln` / `.vcxproj`) |
| Input | Windows API (`Windows.h`, `GetAsyncKeyState`) |
| I/O | Standard console I/O (`iostream`), `system("cls")` for screen refresh |

## 📁 Project Structure

```
snake/
├── Snake.sln              # Visual Studio solution
└── Snake/
    ├── main.cpp            # Game loop: state, movement, collisions, scoring, rendering
    ├── keyboard.h           # Input polling declarations
    └── keyboard.cpp         # WASD key-state polling via WinAPI
```

## 🚀 Getting Started

### Prerequisites

- Windows with **Visual Studio** (2019 or later recommended) and the "Desktop development with C++" workload

### Build & Run

1. Clone the repository:
   ```bash
   git clone https://github.com/ikeerfranzz/snake.git
   ```
2. Open `Snake.sln` in Visual Studio
3. Build and run (`F5` / `Ctrl+F5`)

## 🕹️ Controls

| Key | Action |
|---|---|
| `W` | Move up |
| `A` | Move left |
| `S` | Move down |
| `D` | Move right |

## 👨‍💻 Author

**Iker Franzoni** ([@ikeerfranzz](https://github.com/ikeerfranzz)) — sole developer of this project.

## 📄 Status & License

This project is **complete**. It was built as a course exercise and is shared here as a portfolio piece; no open-source license is granted. Please reach out before reusing any part of this code.
