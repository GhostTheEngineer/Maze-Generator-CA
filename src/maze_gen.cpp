/******************************************************************************
 * Project: Maze Generator - Console App
 * File: maze_gen.cpp
 * Description:
 * Implements the maze generation algorithm using recursive backtracking along with File I/O.
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

#include "maze_gen.h"
#include <vector>
#include <fstream>    // Used for file operations (saving and loading mazes in binary format)
#include <algorithm>  // Used for std::shuffle() in the maze generation algorithm
#include <sstream> // Used to buffer strings in Display function before sending to cout - helps if maze is big

namespace MazeGen {

    // ***********************************
    // PRIVATE
    // ***********************************

    void MazeGenerator::addEntranceAndExit() {

        // Set the entrance at the top (fixed)
        for (int x = 1; x < m_CurrentMaze.m_Width; x += 2) { // start at cell next to left/top border, move by unit of 2 to stay in structure
            if (m_CurrentMaze.m_Grid[1][x] == ' ') { // Find a valid entry point
                m_CurrentMaze.m_Grid[0][x] = ' '; // Open entrance
                break;
            }
        }

        // Find all possible exit locations on the bottom row and add that index to vector
        std::vector<int> validExits;
        for (int x = 1; x < m_CurrentMaze.m_Width; x += 2) {
            if (m_CurrentMaze.m_Grid[m_CurrentMaze.m_Height - 2][x] == ' ') {
                validExits.push_back(x); // Store all possible exits
            }
        }

        // Pick a random exit (index) from vector, if there are valid options
        if (!validExits.empty()) {
            int exitIndex = validExits[m_RNG() % validExits.size()]; // Select a random valid exit
            m_CurrentMaze.m_Grid[m_CurrentMaze.m_Height - 1][exitIndex] = ' '; // Open exit
        }
    }

    void MazeGenerator::carveMaze(int x, int y) {
        /* Static Variables inside function

            Any variables labeled as static in a function will construct once (based on first call)
            and will continue to exist after exiting the function. On future calls, the data
            will be consistent to the last call. This is because the variable belongs to the 
            function and not a specific call.

            Why do this?
            Since this function will be called a lot of times due to the recursive nature,
            we don't want to keep reallocating these variables. Specifically:

                The dx and dy members are constant because this will not change from call to call and
                its best to avoid this reallocation.

                The dirs vector will need to persist its state between calls because the elements
                will be shuffled each time and it is best to reshuffle based on last shuffle
                to promote more randomness - also, we don't want to keep reallocating this vector.

        */
        // Moves two cells at a time to ensure clear paths are created and walls remain intact between paths.
        static const int dx[] = { 0,  0, -2,  2 }; // Movement offsets for Left & Right
        static const int dy[] = { -2, 2,  0,  0 }; // Movement offsets for Up & Down

        // List of direction indices (0: Up, 1: Down, 2: Left, 3: Right) - reused across function calls
        static std::vector<int> dirs = { 0, 1, 2, 3 };

        // A <algorithm> library function to randomly shuffle the directions to create unique maze structures on each generation
        std::shuffle(dirs.begin(), dirs.end(), m_RNG);

        // Mark the current cell/location (passed in as arg) as an open path (' ')
        m_CurrentMaze.m_Grid[y][x] = ' ';

        // lambda function to easily check the bounds of ny and nx(below) to ensure we are not at border or beyond
        auto isBounds = [](int& ax, int& bound) { 
            return (ax > 0) && (ax < bound - 1);
        };

        // Iterate through shuffled directions to determine where to move next
        for (int dir : dirs) {
            // Calculate the new cell coordinates by moving two steps in the chosen direction
            // This moves in unit of 2
            int nx = x + dx[dir]; // new x position
            int ny = y + dy[dir]; // new y position

            // Check if the new cell is within the grid boundaries and is still a wall ('#')
            if (isBounds(ny, m_CurrentMaze.m_Height) && 
                isBounds(nx, m_CurrentMaze.m_Width) && 
                m_CurrentMaze.m_Grid[ny][nx] == '#') {

                // Carve a passage by opening the wall between the current cell and the new cell
                // We divide by 2 to get the actual neighbor cell (since we move by a unit of 2) and set element to space to connect passage with the current cell
                m_CurrentMaze.m_Grid[y + dy[dir] / 2][x + dx[dir] / 2] = ' ';

                // Recursively call carveMaze on the new cell to continue carving paths - will carve down to last cell and return back up
                carveMaze(nx, ny);
            }
        }
    }

    // ***********************************
    // PUBLIC
    // ***********************************

    MazeGenerator::MazeGenerator()  // default
        : m_Width(0), m_Height(0), m_RNG(std::random_device{}()) {} 

    MazeGenerator::MazeGenerator(int w, int h) // NEW: not in tutorial
        :  m_RNG(std::random_device{}()) {
            // In tutorial, we set width and height in member list
            // That may cause issue if we don't validate like we do in SetDimensions function
            // So, instead we just call it
            SetDimensions(w, h, false); // we don't want to generate, so pass false
    }

    void MazeGenerator::SetDimensions(int w, int h, bool generate) {
        // Enforces odd dimensions only by checking using ternary and modulo operator
        m_Width = (w % 2 == 0) ? ++w : w; // if even, increment(prefix to make sure it happens before assignment), to odd number
        m_Height = (h % 2 == 0) ? ++h : h; // same for height

        if (generate) Generate(); // Optional: Call this to automatically update the maze so the user is not working with the old one
    }

    void MazeGenerator::Generate() {

        // Ensure dimensions are set before generating - don't allow negative or zero values
        if (m_Width <= 0 || m_Height <= 0) {
            std::cout << "Set the maze dimensions first!\n";
            return;
        }

        m_CurrentMaze = Maze(m_Width, m_Height); // create new maze object. Replaces the old maze object - no memory leak since m_CurrentMaze is stack allocated
        m_RNG.seed(std::random_device{}()); // generate new seed for randomness
        m_CurrentMaze.m_Grid.assign(m_CurrentMaze.m_Height, std::vector<char>(m_CurrentMaze.m_Width, '#')); // Fill entire grid with walls - initializes the vector to a new size and fills it
        /* Example 5x5 Grid - Filled matrix
                #####
                #####
                #####
                #####
                #####
        */
        carveMaze(1, 1); // Recursively carve path ways, randomly starting from (1,1) position (inside border)
        
        addEntranceAndExit(); // adds an entrance and exit to the existing new maze
        
        Display(); // display the generated maze
    }

    void MazeGenerator::Display() const {

        if (m_CurrentMaze.m_Grid.empty()) { // return early if the grid is empty - happens if user attempts to display before generating or loading any mazes
            std::cout << "There is no loaded or pre-made maze.\nPlease load or select \"Generate New Maze\"" << std::endl;
            return;
        } 

        /* String Stream Buffer
            The use of string stream is to avoid slowing down the process of calling cout multiple times, especially in large mazes.
            String stream acts as a buffer, storing every string and flushing it all out at once in the end to cout. 
        */

        std::stringstream ss;
        ss << "Viewing \'" << m_CurrentMaze.m_Name << "\' maze!\n" << std::endl;
        
        for (const auto& row : m_CurrentMaze.m_Grid) {
            for (char cell : row) {
                ss << cell;
            }
            ss<< '\n';
        }

        std::cout << ss.str(); // flush entire contents from string stream buffer to console
    }

    void MazeGenerator::SaveToFile(const std::string& filename) {
        m_CurrentMaze.m_Name = filename; // set the current maze name to the filename

        std::ofstream file(filename, std::ios::binary);

        // Ensure file is not corrupt and is open
        if (!file || !file.is_open()) {
            std::cerr << "Error saving the maze!\n";
            return;
        }

        // Save the maze m_Name (length + content)
        size_t nameLength = m_CurrentMaze.m_Name.size();
        // Use write function since we are working with binary(raw) data instead of insertion which is for text base
        // Use reinterpret_cast because write function expects a c string pointer. The second arg is the size of the data.
        // Here we write the length of name string to file
        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength)); 
        // Next we write the name to file using the .data function which returns the raw array pointer to the first character of string
        file.write(m_CurrentMaze.m_Name.data(), nameLength);

        // We save the width and height
        file.write(reinterpret_cast<const char*>(&m_CurrentMaze.m_Width), sizeof(m_CurrentMaze.m_Width));
        file.write(reinterpret_cast<const char*>(&m_CurrentMaze.m_Height), sizeof(m_CurrentMaze.m_Height));

        // Finally, Save maze m_Grid vector using the .data, per row, which returns a pointer to the first element
        for (const auto& row : m_CurrentMaze.m_Grid) {
            file.write(row.data(), row.size());
        }

        std::cout << "Maze saved to " << filename << " successfully!\n";
    }

    bool MazeGenerator::LoadFromFile(const std::string& filename) {

        std::ifstream file(filename, std::ios::binary);

        // Ensure file is not corrupt and is open
        if (!file || !file.is_open()) {
            std::cerr << "Error loading the maze! File may not exist.\n";
            return false;
        }

        size_t nameLength;
        // Use read function since we are working with binary(raw) data instead of insertion which is for text base
        // We read in order of save structure starting with size of name string
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        // Use the size to resize the string of maze m_Name member
        m_CurrentMaze.m_Name.resize(nameLength);
        // Read the name and assign it to the maze m_Name member starting at first character - which is why we needed to save the size
        file.read(&m_CurrentMaze.m_Name[0], nameLength);

        // Load m_Width and m_Height and assign to the maze members
        file.read(reinterpret_cast<char*>(&m_CurrentMaze.m_Width), sizeof(m_CurrentMaze.m_Width));
        file.read(reinterpret_cast<char*>(&m_CurrentMaze.m_Height), sizeof(m_CurrentMaze.m_Height));

        // Use the width and height information to resize the grid of current maze
        m_CurrentMaze.m_Grid.assign(m_CurrentMaze.m_Height, std::vector<char>(m_CurrentMaze.m_Width));

        // Load each row of grid from file into maze m_Grid starting at first element
        for (auto& row : m_CurrentMaze.m_Grid) {
            file.read(row.data(), row.size());
        }

        // Update generator dimensions, not the maze dimensions. This ensure we are working on this dimension now for future maze generations
        m_Width = m_CurrentMaze.m_Width;
        m_Height = m_CurrentMaze.m_Height;

        std::cout << "Maze '" << m_CurrentMaze.m_Name << "' loaded from " << filename << " successfully!\n";

        return true;
    }

}
