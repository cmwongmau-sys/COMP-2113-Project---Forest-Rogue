# COMP-2113-Project---Forest-Rogue
Project title:  Forest Rogue

Team Members:

Hung Kwok Kiu - UID:3036058467

Wong Chun Ming Maurice - UID: 3036077695

Ko Kai Man - UID: 3036390073

Bhavani Menon - UID: 3036476243

Kemausuor Winambe Tetteh-Kumah - UID: 3036478552

Nie Eric Yilong - UID: 3036467931


Contributions:

1. Hung Kwok Kiu 3036058467:
   
2. Wong Chun Ming Maurice 3036077695:
  ~constructed the main program
  ~designed function to generate the random event
  ~constructed the simple display function for non-interactive screens
  ~constructed the player set up screen
  ~debugging

3. Ko Kai Man 3036390073:
  ~Designed and debugged some random events.
  ~Final checking and amendments on random.cpp
  ~Worked on the readme.

4. Bhavani Menon 3036476243:
  ~designed and coded game screens for UI displays
  ~coordinated on workspace management

5. Kemausuor Winambe Tetteh-Kumah 3036478552:
  ~designed and debugged some random events.
  ~worked on the scoreboard data.

6. Nie Eric Yilong 3036467931:
  ~help constructed project architecture
  ~constructed base classes and templates for displays
  ~developed generic-use wrapper classes for UI displays
  ~debugging


Files responsible:

1. Hung Kwok Kiu 3036058467:

2. Wong Chun Ming Maurice 3036077695:
   ~main.cpp
   ~event_generation.cpp
   ~simple_display.cpp
   ~GameScreens.cpp
   ~event_generation.h
   ~simple_display.h
   ~GameScreens.h

3. Ko Kai Man 3036390073:
   ~random.h
   ~random.cpp
   ~readme.md

4. Bhavani Menon 3036476243:
   ~Gamescreens.h
   ~Gamescreens.cpp

5. Kemausuor Winambe Tetteh-Kumah 3036478552：
   ~random.h
   ~random.cpp
   ~scoreboard_2026-04-28-012119.txt
   ~readme.md

7. Nie Eric Yilong 3036467931:
   ~SpritesCore.h
   ~SpritesCore.cpp
   ~WidgetsCore.h
   ~WidgetsCore.cpp
   ~SlateCore.h
   ~Gamescreens.h (partially)
   ~Gamescreens.cpp (partially)



Description:
**Forest Rogue** is an immersive text-based survival adventure where you must traverse **6 perilous wilderness zones** to escape the ancient forest.

You manage three key resources for survival — **Health**, **Food**, and **Water** — while facing dynamic random events including bear attacks, hidden treasures, deadly traps, healing water springs, berry rush, changing weather, and peaceful days on different days.

The game features **three unique difficulty levels on your choice** — **Easy**, **Normal**, and **Hard** — which influence starting resources, event probabilities, and severity of outcomes. Every choice you make during events directly impacts your survival and final score.

Survive all zones to claim victory with bonus points based on remaining resources, or perish in the forest.

List of features that we have implemented & Coding Requirement:
|            Implemented Feature             |                 Coding Requirement               | Related files  |
|--------------------------------------------|--------------------------------------------------|----------------|
| Random events (bear, treasure, trap, etc.) |               Random event generation            |   random.cpp   |
|   Difficulty selection (Easy/Normal/Hard)  |             Multiple difficulty levels           |   random.h     |
|        Save & load game state to file      |                     File I/O                     |   Gamescreen.h |
|   Inventory system using dynamic array     |            Dynamic memory management             |simple_display.cpp|
|   Struct EventOutcome for event results    | Data structures, vectors for scoring scoreboard  |   WidgetsCore.h|
|   Code split into multiple .h/.cpp files   |         Program codes in multiple files          |The project is modularized into separate `.h` and `.cpp` files (`main.cpp`, `random.cpp`, `simple_display.cpp`, `file_switch.cpp`, etc.).

## 🔧 Compilation & Execution (Quick Start)

Follow these instructions to compile and run Forest Rogue using a standard C++ compiler:

### Prerequisites
- A C++11 (or later) compiler such as g++.
- Terminal/command prompt access.
- No external libraries are required — only standard C++ headers.

### Compilation
Run the following command in the project root directory:

g++ -std=c++11 main.cpp random.cpp simple_display.cpp file_switch.cpp -o forest_rogue

This will generate an executable file named forest_rogue.

### Execution
After successful compilation, start the game with:

./forest_rogue

### Notes
- Ensure all .cpp and .h files are in the same directory before compiling.
- Save/load functionality will create text files in the working directory.
- The scoreboard file (scoreboard_YYYY-MM-DD.txt) will be generated automatically after gameplay.

---

## ⚠️ Troubleshooting (User Guide)

If you run into problems compiling or running Forest Rogue, try these solutions:

- Compilation fails  
  Ensure you are using a compiler that supports C++11 or later.  
  Use the provided command exactly as shown in the Quick Start section.  

- Executable not created  
  Check that all source files (main.cpp, random.cpp, simple_display.cpp, file_switch.cpp) are present in the same folder.  
  Re-run the compilation command.  

- Game does not start  
  Confirm the executable forest_rogue exists in your directory.  
  Run the game with ./forest_rogue from the terminal.  

- Save/Load not working  
  Make sure you have permission to write files in the current directory.  
  Save files are created as .txt files automatically; check the folder for them.  

- Scoreboard missing  
  The scoreboard file (scoreboard_YYYY-MM-DD.txt) is only generated after a full playthrough.  
  Complete the game to the end to see your score recorded.  


Non-standard Libraries Used:
**None.**  
Only standard C++ libraries are used:
- `<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<iomanip>`, `<ctime>`, `<algorithm>`, `<sstream>`, `<cstdlib>`, `<chrono>`, etc.
