# FlappyForge
A real-time Flappy Bird clone with physics-based movement and procedural obstacle generation, built in C++

# FlappyForge — 2D Game Engine

A fully functional **Flappy Bird clone** built in C++ using the LIFAMI graphics library. The player controls a bird navigating through randomly generated obstacles, with real-time physics and a dynamic scoring system.

---

##  Gameplay

- Press the **UP arrow** to make the bird fly upward
- Avoid the columns — each has a randomly positioned gap
- The further you go, the higher your score
- Hit **Rejouer** to restart at any time
- Your current score is displayed in the **top-right corner**

---

##  How It Works

The game is built around a central `world` structure that holds all game state:

| Field | Description |
|---|---|
| `player position` | Current (x, y) coordinates of the bird |
| `vertical speed` | Applied each frame for gravity effect |
| `obstacles` | Array of columns with random gap positions |
| `score` | Incremented each time an obstacle is passed |

### Core Loop

```
init()   → place bird at center, spawn obstacles with random gaps
update() → apply gravity, move obstacles left, detect collisions, update score
draw()   → render bird, obstacles, score display
```

---

##  Build & Run

### Requirements
- C++ compiler (g++)
- [LIFAMI graphics library](https://perso.univ-lyon1.fr/thierry.excoffier/COURS/LIFAMI/)

### Compile
```bash
g++ -o flappyforge main.cpp -llifami
```

### Run
```bash
./flappyforge
```

---

##  Concepts Used

- Real-time game loop (init / update / draw pattern)
- Vertical physics simulation (gravity + velocity)
- Procedural obstacle generation with random gaps
- Collision detection
- Score tracking and UI rendering

---

##  Project Structure

```
FlappyForge/
├── src/
│   └── LIFAPI_TP.cpp       # Main source file
├── docs/
│   └── markdown-preview.pdf        # Full project report (French)
├── data/
│   └── bird1.png
├   └── Thumbs.db
├   └── grapic_0.png
├   └── grapic_3.png
│ 
└── README.md
```

---

## 🎓 Academic Context

Developed as part of the **LIFAMI** course (C++ graphics programming) at **Université Claude Bernard Lyon 1** — Licence Mathématiques-Informatique, Year 1 (2025).
