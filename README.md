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
  ~worked on the readme file

7. Nie Eric Yilong 3036467931:
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

## 📖 Forest Rogue – Game Setup & Rules

### 1. Game Concept
- You are lost in an enchanted forest.
- Goal: Reach Zone 6 to escape.
- Manage **Health, Food, Water** to survive.
- Each day brings random encounters.
- Game ends when you escape or die.

### 2. Game World
The forest has **6 zones** in linear order:  
Zone 1 → Zone 2 → Zone 3 → Zone 4 → Zone 5 → Zone 6  
You must progress one zone per day, no skipping.

### 3. Player Resources
- **Health (0–100):** Lost from attacks/traps/weather, gained from healing. If 0 → Game Over.  
- **Food (Easy: 5, Medium: 3, Hard: 2):** -1 per day, gained from berries/hunting. If ≤ -3 → Game Over.  
- **Water (Easy: 3, Medium: 2, Hard: 1):** -1 per day, gained from springs/rain. If ≤ -3 → Game Over.  

### 4. Daily Routine
Each day follows this sequence:
1. Display current status (resources, zone, day).  
2. Random encounter occurs.  
3. Player makes choices (fight/flee/use items).  
4. Apply encounter effects.  
5. Daily consumption (-1 food, -1 water).  
6. Check for death conditions.  
7. Move to next zone if survived.  
8. Log the day’s events.

### 5. Random Encounter Types
- Wild Animal (fight/flee)  
- Treasure (items gained)  
- Trap (lose health or resources)  
- Water Spring (gain water)  
- Berry Bush (gain food)  
- Weather Event (random effect)  
- Empty (nothing happens)  

Probabilities vary by difficulty (Easy/Normal/Hard).

### 6. Difficulty Settings
- **Easy:** High resources, low damage, higher treasure chance.  
- **Medium:** Balanced challenge.  
- **Hard:** Low resources, high damage, higher trap chance.  

### 7. Win/Loss Conditions
- **Win:** Reach Zone 6 with health > 0.  
- **Lose:** Health = 0, Food ≤ -3, or Water ≤ -3.  

### 8. Scoring System
- Base Score = Zones cleared × 100.  
- Bonus = Remaining health × 2 + Food × 5 + Water × 5.  
- Final Score = Base + Bonus.  
- Scoreboard file generated via File I/O.

### 9. Example Gameplay Flow
**Day 1 (Zone 1):** Encounter Berry Bush → +2 food → End: Health 100, Food 4, Water 1.  
**Day 2 (Zone 2):** Encounter Wolf → Fight → -12 health, +2 food → End: Health 88, Food 5, Water 0.  
**Day 3 (Zone 3):** Encounter Water Spring → +3 water → End: Health 88, Food 4, Water 2.  
... continues until Zone 6 or death.


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
