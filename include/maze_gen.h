/******************************************************************************
 * Project: Maze Generator - Console App
 * File: maze_gen.h
 * Description:
 * Declares the MazeGenerator class and its methods.
 *
 * Copyright © 2025 Ghost - Two Byte Tech. All Rights Reserved.
 *
 * This source code is licensed under the MIT License. For more details, see
 * the LICENSE file in the root directory of this project.
 *
 * Version: v1.0.0
 * Author: Ghost
 * Created On: 02-14-2025
 * Last Modified: 02-14-2025
 *****************************************************************************/

#pragma once
#include "maze.h"
#include <iostream>
#include <random>     // Used for std::mt19937 (Mersenne Twister PRNG) to randomize maze paths

namespace MazeGen {
    class MazeGenerator {
    private:
        Maze m_CurrentMaze;
        int m_Width, m_Height;
        std::mt19937 m_RNG; // Mersenne Twister - pseudo-random number generator

        void carveMaze(int x, int y);

        void addEntranceAndExit();

    public:
        
        MazeGenerator(); // default constructor

        MazeGenerator(int w, int h);

        void SetDimensions(int w, int h, bool generate = true); // default value for third arg

        void Generate();

        void Display() const;

        void SaveToFile(const std::string& filename);
        
        bool LoadFromFile(const std::string& filename);
            
    };
}
