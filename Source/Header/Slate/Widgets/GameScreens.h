#ifndef GAME_SCREENS_H
#define GAME_SCREENS_H

#include "Slate/Widgets/WidgetsCore.h"
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
// abstract class (pure virtual) - serves as interface
class IScreenBase : public IWidget {
public:
    IScreenBase(int x = 0, int y = 0) : IWidget(x, y) {}
    virtual ~IScreenBase() = default;
    virtual void Render() override = 0;   // each screen draws itself and waits for input
};

// shows what happened during a random event
// called after bear attack, treasure, trap, etc
// displays changes to health, food, water, and inventory
class SEventResultScreen : public IScreenBase {
private:
    EventOutcome Outcome;
    int Health, MaxHealth;
    int Food, MaxFood;
    int Water, MaxWater;
    
public:
    // Constructor: takes event outcome and current stats (health, food, water with max values).
    // Also accepts optional x,y offset for screen positioning.
    SEventResultScreen(const EventOutcome& outcome,
                       int health, int maxHealth,
                       int food, int maxFood,
                       int water, int maxWater,
                       int x = 0, int y = 0);
    
    // Renders the event result screen: clears screen, draws box, shows event name,
    // player's choice, result text, changes table, inventory updates, and current status.
    // Waits for the player to press Enter. No inputs, no outputs.
    void Render() override;
};

// shows end of day summary
// called after daily consumption (-1 food, -1 water)
// displays updated stats with health, food, water bars
class SDailySummaryScreen : public IScreenBase {
private:
    int Day, Zone, TotalZones;
    int Health, MaxHealth;
    int Food, MaxFood;
    int Water, MaxWater;
    
public:
    // Constructor: takes day number, current zone, total zones, current health/food/water
    // and their maximum values. Optional x,y offset.
    SDailySummaryScreen(int day, int zone, int totalZones,
                        int health, int maxHealth,
                        int food, int maxFood,
                        int water, int maxWater,
                        int x = 0, int y = 0);
    
    // Renders the daily summary: clears screen, draws box, shows daily consumption (-1 food/water),
    // health/food/water bars with numeric values, zone progress, and waits for Enter.
    void Render() override;
};

// game over screen
// called when player dies (health <= 0 or food/water < 0)
// displays final stats and score
class SDeathScreen : public IScreenBase {
private:
    int ZonesCleared, DaysSurvived;
    int FinalHealth, FinalFood, FinalWater, FinalScore;
    
public:
    // Constructor: takes zones cleared, days survived, final health/food/water, final score.
    // Optional x,y offset.
    SDeathScreen(int zonesCleared, int daysSurvived,
                 int finalHealth, int finalFood, int finalWater,
                 int finalScore, int x = 0, int y = 0);
    
    // Renders the game over screen: clears screen, draws box, shows death message,
    // final stats, score, and waits for Enter.
    void Render() override;
};

// victory screen
// called when player clears all 6 zones
// displays final stats and score breakdown
class SVictoryScreen : public IScreenBase {
private:
    int ZonesCleared, DaysSurvived;
    int FinalHealth, FinalFood, FinalWater;
    int ItemsFound, Multiplier, FinalScore;
    
public:
    // Constructor: takes zones cleared, days survived, final health/food/water,
    // items found (unused), difficulty multiplier (unused), final score.
    // Optional x,y offset.
    SVictoryScreen(int zonesCleared, int daysSurvived,
                   int finalHealth, int finalFood, int finalWater,
                   int itemsFound, int multiplier, int finalScore,
                   int x = 0, int y = 0);
    
    // Renders the victory screen: clears screen, draws box, shows escape message,
    // final stats, score breakdown (base + health/food/water bonuses), final score,
    // and waits for Enter.
    void Render() override;
};

// choice menu for player decisions
// used inside events to let player pick between options like fight, run, hide
// works with number input for now (1,2,3), can be upgraded to arrow keys later
class SChoiceMenu : public IWidget {
private:
    std::vector<std::string> Options;
    int SelectedIndex;
    bool bHorizontal;
    
public:
    // Constructor: takes list of option strings, screen position (x,y), and layout flag.
    // If horizontal = true, options are placed left-to-right; otherwise top-to-bottom.
    SChoiceMenu(const std::vector<std::string>& options, int x, int y, bool horizontal = true);
    
    // Renders the choice menu: displays options with the currently selected one highlighted
    // (surrounded by > <). Does not handle input.
    void Render() override;
    
    // Waits for player to make a selection using number keys (1,2,3...).
    // Displays numbered list below the rendered menu, reads input, validates.
    // Returns zero‑based index of the selected option.
    int WaitForSelection();
    
    // Returns the currently selected index (without waiting for input).
    int GetSelectedIndex() const { return SelectedIndex; }
    
    // Returns the currently selected option string.
    std::string GetSelectedOption() const { return Options[SelectedIndex]; }
};

#endif
