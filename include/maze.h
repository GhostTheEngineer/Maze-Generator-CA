/******************************************************************************
 * Project: Maze Generator - Console App
 * File: maze.h
 * Description:
 * Defines the Maze structure and its attributes.
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
#include <vector>  // Used for creating the maze grid as a 2D matrix (std::vector)
#include <string>  

namespace MazeGen {
    struct Maze {
        int m_Width, m_Height; // stores the maze, grid dimensions
        std::vector<std::vector<char>> m_Grid; // stores all pathways and walls of the maze as character '#' (wall) or ' ' (passage)
        std::string m_Name; // track name of maze for file i/o

        Maze() : m_Width(0), m_Height(0), m_Name("Unnamed") {} // default constructor
        Maze(int w, int h) : m_Width(w), m_Height(h), m_Name("Unnamed") {}

    };
}
