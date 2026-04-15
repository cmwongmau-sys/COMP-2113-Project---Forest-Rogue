#ifndef GAME_SCREENS_H
#define GAME_SCREENS_H

#include "../../Header/Slate/Widgets/WidgetsCore.h"
#include <string>
#include <vector>

// this struct holds what happened during a random event
// filled by the random events team and passed to the screen
struct EventOutcome {
    std::string eventName;           // bear attack, treasure, etc
    std::string choiceMade;          // fight, run, etc
    std::string resultText;          // what happened after the choice
    int deltaHealth = 0;             // health change, negative means damage
    int deltaFood = 0;               // food change
    int deltaWater = 0;              // water change
    std::vector<std::string> itemsAdded;    // items player found
    std::vector<std::string> itemsRemoved;  // items player lost
};

// base class for all screens
// has offset so screens can be moved if needed
class SScreenBase : public IWidget {
protected:
    int OffsetX, OffsetY;            // moves whole screen position
public:
    SScreenBase(int offsetX = 0, int offsetY = 0) : OffsetX(offsetX), OffsetY(offsetY) {}
    virtual ~SScreenBase() = default;
    virtual void Render() override = 0;   // each screen draws itself and waits for input
};

// shows what happened during a random event
// called after bear attack, treasure, trap, etc
// displays changes to health, food, water, and inventory
class SEventResultScreen : public SScreenBase {
private:
    EventOutcome Outcome;
    int Health, MaxHealth;
    int Food, MaxFood;
    int Water, MaxWater;
    
public:
    SEventResultScreen(const EventOutcome& outcome,
                       int health, int maxHealth,
                       int food, int maxFood,
                       int water, int maxWater,
                       int offsetX = 0, int offsetY = 0);
    
    void Render() override;   // draws screen and waits for enter key
};

// shows end of day summary
// called after daily consumption (-1 food, -1 water)
// displays updated stats with health, food, water bars
class SDailySummaryScreen : public SScreenBase {
private:
    int Day, Zone, TotalZones;
    int Health, MaxHealth;
    int Food, MaxFood;
    int Water, MaxWater;
    
public:
    SDailySummaryScreen(int day, int zone, int totalZones,
                        int health, int maxHealth,
                        int food, int maxFood,
                        int water, int maxWater,
                        int offsetX = 0, int offsetY = 0);
    
    void Render() override;   // draws screen and waits for enter key
};

// game over screen
// called when player dies (health <= 0 or food/water < 0)
// displays final stats and score
class SDeathScreen : public SScreenBase {
private:
    int ZonesCleared, DaysSurvived;
    int FinalHealth, FinalFood, FinalWater, FinalScore;
    
public:
    SDeathScreen(int zonesCleared, int daysSurvived,
                 int finalHealth, int finalFood, int finalWater,
                 int finalScore, int offsetX = 0, int offsetY = 0);
    
    void Render() override;   // draws screen and waits for input
};

// victory screen
// called when player clears all 6 zones
// displays final stats and score breakdown
class SVictoryScreen : public SScreenBase {
private:
    int ZonesCleared, DaysSurvived;
    int FinalHealth, FinalFood, FinalWater;
    int ItemsFound, Multiplier, FinalScore;
    
public:
    SVictoryScreen(int zonesCleared, int daysSurvived,
                   int finalHealth, int finalFood, int finalWater,
                   int itemsFound, int multiplier, int finalScore,
                   int offsetX = 0, int offsetY = 0);
    
    void Render() override;   // draws screen and waits for input
};

// choice menu for player decisions
// used inside events to let player pick between options like fight, run, hide
// works with number input for now (1,2,3), can be upgraded to arrow keys later
class SChoiceMenu : public IWidget {
private:
    std::vector<std::string> Options;
    int SelectedIndex;
    int X, Y;
    bool bHorizontal;
    
public:
    SChoiceMenu(const std::vector<std::string>& options, int x, int y, bool horizontal = true);
    void Render() override;
    int WaitForSelection();        // returns the index player picked (0 based)
    int GetSelectedIndex() const { return SelectedIndex; }
    std::string GetSelectedOption() const { return Options[SelectedIndex]; }
};

#endif
