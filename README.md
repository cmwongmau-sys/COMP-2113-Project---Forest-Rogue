# COMP-2113-Project---Forest-Rogue
Project title:  Forest Rogue

Team Members:

Hung Kwok Kiu - UID:3036058467

Wong Chin Ming Maurice - UID: 3036077695

Ko Kai Man - UID: 3036390073

Bhavani Menon - UID: 3036476243

Kemausuor Winambe Tetteh-Kumah - UID: 3036478552

Nie Eric Yilong - UID: 3036467931

Contributions:
1. Hung Kwok Kiu 3036058467:
2. Wong Chin Ming Maurice 3036077695:
  ~constructed the main program
  ~designed function to generate the random event
  ~constructed the simple display function for non-interactive screens
  ~constructed the player set up screen
  ~debugging
3. Ko Kai Man 3036390073:
  ~Designed and debugged some random events.
  ~Final checking and amendments on random.cpp
  ~Worked on the readme.




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
|   Code split into multiple .h/.cpp files   |         Program codes in multiple files          |

Non-standard Libraries Used:
**None.**  
Only standard C++ libraries are used:
- `<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<iomanip>`, `<ctime>`, `<algorithm>`, `<sstream>`, `<cstdlib>`, `<chrono>`, etc.
