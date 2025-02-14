# Maze Generator

## Overview
This is a **C++ terminal-based maze generator** that creates randomized mazes using recursive backtracking. It allows users to:
- **Generate random mazes**
- **Save mazes to a binary file**
- **Load and display saved mazes**
- **Set custom dimensions** (odd numbers recommended for better structure)

The project is structured with **modular components** using **CMake** for building.

## Features
- **Random Maze Generation:** Uses recursive backtracking for creating unique mazes.
- **File I/O Support:** Save and load mazes in a binary format.
- **Cross-Platform Support:** Works on Windows, macOS, and Linux.
- **Optimized Console Display:** Uses `std::stringstream` for efficient rendering.
- **Entrance and Exit Handling:** Automatically adds an entrance and exit to ensure a solvable maze.

## Tutorial & YouTube Video

This project is part of a **maze generation tutorial** that walks through the code step by step. It is considered beginner friendly but has some advance concepts to expose to young programmers.

🎥 **Watch the full tutorial on YouTube:**  
[➡️ Click here to watch](YOUR_YOUTUBE_VIDEO_LINK)

## Installation

### Prerequisites
- C++17 or later
- CMake (3.10 or newer)
- A C++ compiler (GCC, Clang, MSVC)
- Git (optional)

### Build Instructions
1. Clone the repository (or download the source files):
   ```sh
   git clone https://github.com/GhostTheEngineer/Maze-Generator-CA.git
   cd Maze-Generator-CA
   ```
2. **Compile using CMake**:
   ```sh
   ./compile.sh Release   # For Linux/macOS
   compile.bat Release    # For Windows
   ```
3. **Run the program**:
   ```sh
   ./build.sh Release   # For Linux/macOS
   run.bat Release      # For Windows
   ```

## Usage
When you run the program, you will be presented with a menu:
```
Maze Generator
    1. Set dimensions
    2. Generate New Maze
    3. Display Maze
    4. Save Maze
    5. Load Maze
    6. Exit
Choose an option: 
```
### Generating a Maze
- Select `1` to **set dimensions** (odd numbers recommended for best results).
- Select `2` to **generate a new maze**.

### Saving and Loading Mazes
- Select `4` to **save the current maze to a binary file**.
- Select `5` to **load a previously saved maze**.

## Project Structure
```
MazeGen/
│── src/
│   ├── main.cpp        # Entry point of the application
│   ├── driver.cpp      # Handles user input and program flow
│   ├── maze_gen.cpp    # Maze generation logic
│── include/
│   ├── driver.h        # Header file for driver.cpp
│   ├── maze.h          # Maze structure definition
│   ├── maze_gen.h      # Maze generator class definition
│── CMakeLists.txt      # CMake build configuration
│── compile.bat        # Windows compile script
│── compile.sh         # Linux/macOS compile script
│── run.bat            # Windows run script
│── run.sh           # Linux/macOS run script
```

## Technical Details
- Uses **recursive backtracking** for maze generation.
- **Mersenne Twister PRNG (`std::mt19937`)** for randomness.
- **Binary file handling** with `std::ofstream` and `std::ifstream`.
- **Cross-platform console clearing** for Windows and Linux/macOS.

## License
This project is licensed under the **MIT License**.
