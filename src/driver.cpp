/******************************************************************************
 * Project: Maze Generator - Console App
 * File: driver.cpp
 * Description:
 * Manages program flow, user input, and command execution.
 *
 * Copyright © 2025 Ghost - Two Byte Tech. All Rights Reserved.
 *
 * This source code is licensed under the MIT License. For more details, see
 * the LICENSE file in the root directory of this project.
 *
 * Version: v1.0.1
 * Author: Ghost
 * Created On: 02-14-2025
 * Last Modified: 02-21-2025
 *****************************************************************************/

#include "driver.h"
#include "maze_gen.h"     // Used for creating the maze grid as a 2D matrix (std::vector<std::vector>)
#include <iostream>
#include <string>

namespace MazeGen {

    void clearScreen() {
        // Cross platform way to deal with clearing the console screen
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux/Mac
    #endif
    }

    // CHANGE - removed inline keyword. They have no effect due to compiler optimization which will do what inline is attempting to do.
    bool validateInput() {
        // Inline functions are not real functions, wherever this is called, the contents in this scope are copied to that location.
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Numeric input only, letters and symbols not allowed!" << std::endl;
            return false;
        }
        return true;
    }

    void displayMenu() {
        // R and () allows formating strings, exactly as shown in IDE (hence the string pushed all the way to left)
        std::cout << R"(
Maze Generator
    1. Set dimensions
    2. Generate New Maze
    3. Display Maze
    4. Save Maze
    5. Load Maze
    6. Exit
Choose an option: )";
    }

    int run() {
        clearScreen(); // begin with a clear terminal

        // define the maze dimension, could change to something else if you would like
        // TODO check out the constructor, there is new code that is not found in tutorial
        MazeGenerator generator(15, 9); 
        
        int choice;
        
        do {
            displayMenu();

            std::cin >> choice;

            // Validation Check point
            if (!validateInput()) continue;

            clearScreen();

            // More efficient than if-statements
            switch (choice) {
            case 1: // Set Dimensions
                { // scope creation is required if stack variables declarations need to happen
                    int m_Width, m_Height;
                    bool isGenerating;
                    std::cout << "Enter maze m_Width (odd number only): ";
                    std::cin >> m_Width;
                    if (!validateInput()) continue;
                    std::cout << "Enter maze m_Height (odd number only): ";
                    std::cin >> m_Height;
                    if (!validateInput()) continue;
                    // NEW: not in tutorial - allows user to decide if they want to generate automatically or not
                    // 1 and 0 input to keep it simple
                    std::cout << "Would you like to generate (1(Yes) or 0(No))? ";
                    std::cin >> isGenerating;
                    if (!validateInput()) continue;

                    generator.SetDimensions(m_Width, m_Height, isGenerating); 
                }
                break;

            case 2: // Generate Maze
                std::cout << "generating maze...\n\n";
                generator.Generate();
                break;

            case 3: // Display Current Maze
                generator.Display();
                break;

            case 4: // Save Current Maze to File
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // handles removing the '\n' character left in input buffer from std::cin above
                    std::string filename;
                    std::cout << "Enter filename to save: ";
                    std::getline(std::cin, filename);  // allow white spaces
                    generator.SaveToFile(filename);
                }
                break;

            case 5: // Save Maze from File to Current Maze
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // handles removing the '\n' character left in input buffer from std::cin above
                    std::string filename;
                    std::cout << "Enter filename to load: ";
                    std::getline(std::cin, filename); // allow white spaces
                    if (!generator.LoadFromFile(filename)) {
                        std::cout << "Failed to load maze. Try again.\n";
                    }
                }
                    break;

            case 6:
                std::cout << "Exiting program.\n";
                break;  

            default:
                std::cout << "Invalid choice, try again.\n";
                break;

            }
        
        }  while (choice != 6); // runs until a 6 is input

        return 0;
    }

}
