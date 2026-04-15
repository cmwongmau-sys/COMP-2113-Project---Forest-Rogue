#ifndef GAME_SCREENS_H
#define GAME_SCREENS_H

#include "../../Header/Slate/Widgets/WidgetsCore.h"  // for IWidget and SBar
#include <string>
#include <vector>

// this struct holds what happened during a random event
// the random events team fills this and passes it to my screen
struct EventOutcome {
    std::string eventName;           // bear attack, treasure, etc
    std::string choiceMade;          // fight, run, etc
    std::string resultText;          // "you defeated the bear but got hurt"
    int deltaHealth = 0;             // health change (negative means damage)
    int deltaFood = 0;               // food change
    int deltaWater = 0;              // water change
    std::vector<std::string> itemsAdded;    // items the player found
    std::vector<std::string> itemsRemoved;  // items the player lost
};

// base class for all screens - inherits from IWidget like teammate wanted
// has offset so screens can be moved around if needed
class SScreenBase : public IWidget {
protected:
    int OffsetX, OffsetY;            // for moving the whole screen
public:
    SScreenBase(int offsetX = 0, int offsetY = 0) : OffsetX(offsetX), OffsetY(offsetY) {}
    virtual ~SScreenBase() = default;
    virtual void Render() override = 0;      // each screen draws itself
    virtual void HandleInput() {}            // override if screen needs user input
};

// displays what happened during a random event
// shows changes to health food water and inventory updates
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
    
    void Render() override;
    void HandleInput() override;   // waits for enter key
};

// shows end of day summary
// displays daily consumption (-1 food -1 water) and current status bars
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
    
    void Render() override;
    void HandleInput() override;   // waits for enter key
};

// game over screen
// shows when player dies - displays final stats and score
class SDeathScreen : public SScreenBase {
private:
    int ZonesCleared, DaysSurvived;
    int FinalHealth, FinalFood, FinalWater, FinalScore;
    
public:
    SDeathScreen(int zonesCleared, int daysSurvived,
                 int finalHealth, int finalFood, int finalWater,
                 int finalScore, int offsetX = 0, int offsetY = 0);
    
    void Render() override;
    void HandleInput() override;
};

// victory screen
// shows when player beats all 6 zones - displays score breakdown
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
    
    void Render() override;
    void HandleInput() override;
};

// simple choice menu - lets player pick from options
// can be upgraded to arrow keys later but works with numbers for now
class SChoiceMenu : public IWidget {
private:
    std::vector<std::string> Options;
    int SelectedIndex;
    int X, Y;
    bool bHorizontal;
    
public:
    SChoiceMenu(const std::vector<std::string>& options, int x, int y, bool horizontal = true);
    void Render() override;
    int WaitForSelection();        // returns the index the player picked (0 based)
    int GetSelectedIndex() const { return SelectedIndex; }
    std::string GetSelectedOption() const { return Options[SelectedIndex]; }
};

#endif
