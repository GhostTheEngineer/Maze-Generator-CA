@echo off
setlocal

:: Require build flag
if not "%1"=="Release" if not "%1"=="Debug" (
    echo Usage: build.bat Release or Debug
    exit /b 1
)
set BUILD_TYPE=%1
set BUILD_DIR=out/%BUILD_TYPE%

if exist %BUILD_DIR%/MazeGen.exe (
    :: Changing directory first allows the maze files to save in the out directory
    cd /d "%BUILD_DIR%" 
    start MazeGen.exe
) else (
    echo Could not find .exe file. Please run ./compile in main directory first!
)