# Change Log
This document reflects this current commit's state and not just its version. All items listed below were implemented for this commit.

## Version v1.0.1
Removed code that was not necessary.

### Addition
- None

### Changes
- driver.cpp
    - Removed the `inline` keyword from `validateInput`, since it has no effect since the compiler optimization (-O2) handles it(essentially finds any small functions like `validateInput` treats it like `inline` keyword.). This was phased out in c++98. `inline` has been repurposed and I will explain in an upcoming video!  
    - Removed the function `clearInputBuffer` and placed the content of it directly where it was called.
- maze_gen.cpp
    - Removed `std::endl` from string stream. `\n` is better on performance as `std::endl` is a strict flush and is more expensive.

### Fixes
- None