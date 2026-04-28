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
  ~construct the scoreboard
  ~help to manage the switch between files
  ~construct the readme file
  
   
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
   ~file_switch.cpp
   ~file_switch.h
   ~readme.md
  

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

## 📊 Difficulty Comparison Table

The three difficulty modes in Forest Rogue adjust starting resources and event probabilities.  
This table summarizes the differences:

This combined table shows starting resources by difficulty alongside the probabilities of different encounters.

| Difficulty | Starting Health | Starting Food | Starting Water | Wild Animal | Treasure | Trap | Water Spring | Berry Bush | Weather Event | Empty |
|------------|-----------------|---------------|----------------|-------------|----------|------|--------------|------------|---------------|-------|
| Easy       | 100             | 5             | 3              | 20% (Fight/Flee) | 20% (Find items) | 10% (Lose health) | 15% (Gain water) | 15% (Gain food) | 10% (Random effect) | 10% (Nothing) |
| Medium     | 100             | 3             | 2              | 25% (Fight/Flee) | 15% (Find items) | 15% (Lose health) | 10% (Gain water) | 10% (Gain food) | 15% (Random effect) | 10% (Nothing) |
| Hard       | 100             | 2             | 1              | 30% (Fight/Flee) | 10% (Find items) | 20% (Lose health) | 5% (Gain water)  | 5% (Gain food)  | 20% (Random effect) | 10% (Nothing) |

---

This unified view makes it easy to see how **difficulty settings** affect both your starting resources and the likelihood of each encounter type.
It also helps players choose the right mode for their skill level.


List of features that we have implemented & Coding Requirement:
|            Implemented Feature             |                 Coding Requirement               | Related files  |
|--------------------------------------------|--------------------------------------------------|----------------|
| Random events (bear, treasure, trap, etc.) |               Random event generation            |   random.cpp   |
|   Difficulty selection (Easy/Normal/Hard)  |             Multiple difficulty levels           |   random.h     |
|        Save & load game state to file      |                     File I/O                     |   Gamescreen.h |
|   Inventory system using dynamic array     |            Dynamic memory management             |simple_display.cpp|
|   Struct EventOutcome for event results, vectors for scoring scoreboard    | Data structures  |   file_switch.cpp|
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

### 🧮 Scoring Examples

To illustrate how the scoring system works, here are two sample calculations:

**Example 1 – Easy Mode Victory**
- Zones cleared: 6 → Base Score = 600
- Remaining Health: 85 → Bonus = 85 × 2 = 170
- Remaining Food: 4 → Bonus = 4 × 5 = 20
- Remaining Water: 3 → Bonus = 3 × 5 = 15
- **Final Score = 600 + 170 + 20 + 15 = 805**

**Example 2 – Hard Mode Defeat (Zone 4)**
- Zones cleared: 4 → Base Score = 400
- Remaining Health: 0 → Bonus = 0
- Remaining Food: -2 → Bonus = 0 (starvation)
- Remaining Water: 1 → Bonus = 5
- **Final Score = 400 + 5 = 405**

These examples show how survival resources directly impact the final score.


### 9. Example Gameplay Flow
## 🎮 Extended Sample Gameplay Run (Easy Mode)

Below is a complete playthrough transcript showing all 6 zones in order.
---

**Day 1 – Zone 1**
Status: Health 100, Food 5, Water 3  
Encounter: Berry Bush  
Outcome: +2 Food  
Daily Consumption: Food -1, Water -1  
End of Day: Health 100, Food 6, Water 2  

---

**Day 2 – Zone 2**
Status: Health 100, Food 6, Water 2  
Encounter: Wolf Attack  
Choice: Fight (roll 42 → Win)  
Outcome: -10 Health, +2 Food  
Daily Consumption: Food -1, Water -1  
End of Day: Health 90, Food 7, Water 1  

---

**Day 3 – Zone 3**
Status: Health 90, Food 7, Water 1  
Encounter: Water Spring  
Outcome: +3 Water  
Daily Consumption: Food -1, Water -1  
End of Day: Health 90, Food 6, Water 3  

---

**Day 4 – Zone 4**
Status: Health 90, Food 6, Water 3  
Encounter: Trap  
Choice: Escape attempt (Fail)  
Outcome: -15 Health  
Daily Consumption: Food -1, Water -1  
End of Day: Health 75, Food 5, Water 2  

---

**Day 5 – Zone 5**
Status: Health 75, Food 5, Water 2  
Encounter: Treasure (Abandoned campsite)  
Outcome: +2 Food, +1 Water, +30 Health  
Daily Consumption: Food -1, Water -1  
End of Day: Health 105, Food 6, Water 2  

---

**Day 6 – Zone 6**
Status: Health 105, Food 6, Water 2  
Encounter: Peaceful Day  
Outcome: No changes  
Daily Consumption: Food -1, Water -1  
End of Day: Health 105, Food 5, Water 1  

---

**Victory Screen**
Congratulations! You survived all 6 zones.  
Final Scoreboard → Health: 105, Food: 5, Water: 1  
Base Score: 600  
Bonus: Health (105×2 = 210) + Food (5×5 = 25) + Water (1×5 = 5)  
Total Score = 600 + 210 + 25 + 5 = 840  
Scoreboard file generated: scoreboard_2026-04-28.txt  

---

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
### 📺 Display Recommendation

Forest Rogue is best experienced in a **run screen console**.  
For proper text alignment and UI display, please ensure your terminal window is at least:

**90 characters wide × 30 lines tall**

Running the game in smaller windows may cause text wrapping or misaligned UI elements.

## 💡 Tips for Survival

Here are some strategies to improve your chances of escaping the forest:

- **Conserve Food and Water**  
  Always keep track of daily consumption. Collect berries and water whenever possible to avoid starvation or dehydration.

- **Know When to Flee**  
  Fighting animals can cost a lot of health. If your health is low, fleeing may be the safer option.

- **Treasure is Rare in Hard Mode**  
  Don’t rely on treasure events for survival. Focus on springs and bushes to replenish resources.

- **Balance Risk and Reward**  
  Some encounters offer big rewards but carry high risk. Consider your current resource levels before making bold choices.

- **Use Save/Load Wisely**  
  Save your progress before entering a new zone. This allows you to retry if you encounter an unlucky sequence of events.

- **Watch the Weather**  
  Rain can help restore water, but heat waves and cold snaps can drain resources quickly. Plan accordingly.

These tips are based on playtesting and highlight how different coding elements (random events, difficulty settings, file I/O) affect gameplay.



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

## 🛠️ Developer Notes

During the development of **Forest Rogue**, several design choices and challenges shaped the final implementation:

- **Modular Code Structure**  
  We split the project into multiple `.h` and `.cpp` files to improve readability and teamwork. Each member could focus on specific modules (e.g., random events, UI displays, scoreboard) without conflicts.

- **Random Event System**  
  Events were implemented using probability ranges (`rand()%100`) to ensure unpredictability. Balancing event probabilities across Easy, Medium, and Hard modes required careful tuning to keep gameplay fair but challenging.

- **Difficulty Balancing**  
  Starting resources and damage values were adjusted after multiple test runs. For example, Hard mode initially felt impossible, so we reduced trap damage slightly to make survival achievable but still tough.

- **File I/O for Save/Load**  
  We chose plain text files for simplicity and transparency. This allowed easy debugging of saved states and ensured compatibility across different systems without external libraries.

- **Scoreboard Implementation**  
  The scoreboard was designed to log results with timestamps (`scoreboard_YYYY-MM-DD.txt`). This not only tracks player progress but also demonstrates use of vectors and structs for storing outcomes.

- **UI Display Constraints**  
  Since the game is text-based, we optimized output for console readability. A minimum window size of **90×30** was recommended to prevent misaligned text and ensure health/food/water bars display correctly.

- **Testing & Debugging**  
  We ran multiple simulated playthroughs to verify event probabilities, resource consumption, and win/loss conditions. Debugging focused on edge cases like starvation, dehydration, and save/load consistency.

These notes highlight the reasoning behind our coding elements and show how design decisions support the implemented features.


Non-standard Libraries Used:
**None.**  
Only standard C++ libraries are used:
- `<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<iomanip>`, `<ctime>`, `<algorithm>`, `<sstream>`, `<cstdlib>`, `<chrono>`, etc.
