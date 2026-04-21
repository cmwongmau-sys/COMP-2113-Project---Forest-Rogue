#include "Slate/Widgets/GameScreens.h"
#include "Slate/Widgets/WidgetsCore.h"
#include <iostream>
#include <sstream>

// helper to draw a status bar
// uses SBar widget
// Inputs: x,y position, width, current value, max value, fill character, empty character
// Outputs: none (draws directly to screen)
void DrawBar(int x, int y, int width, int current, int max,
             const std::string fillChar,
             const std::string emptyChar)
{
    float percent = (max > 0) ? (float)current / max : 0.0f;
    SBar bar(x, y, width, 1, percent, emptyChar, fillChar);
    bar.Render();
}

// helper to draw text without direct cout
// uses STextBox
// Inputs: x,y position, text string
// Outputs: none (draws text at specified position)
static void DrawText(int x, int y, const std::string& text) {
    STextBox box(x, y, (int)text.length(), 1, text, false, false);
    box.Render();
}

// ============================================================
// SEventResultScreen - shows what happened during a random event
// called after bear attack, treasure, trap, etc
// displays changes to health food water and items found
// ============================================================

// Constructor: initializes screen with event outcome and current stats.
// Inputs: outcome (EventOutcome struct), health, maxHealth, food, maxFood, water, maxWater, optional x,y offset.
// Outputs: none (initializes object).
SEventResultScreen::SEventResultScreen(const EventOutcome& outcome,
                                       int health, int maxHealth,
                                       int food, int maxFood,
                                       int water, int maxWater,
                                       int x, int y)
    : IScreenBase(x, y)
    , Outcome(outcome)
    , Health(health), MaxHealth(maxHealth)
    , Food(food), MaxFood(maxFood)
    , Water(water), MaxWater(maxWater) {}

// Renders the event result screen.
// Clears screen, draws box, displays event name, choice, result, changes table,
// inventory updates, current status, and waits for Enter.
// Inputs: none (uses member variables).
// Outputs: none (draws to screen, waits for user input).
void SEventResultScreen::Render() {
    // clear screen and move cursor to top
    std::cout << "\033[2J\033[1;1H";
    
    // apply location offset
    int x = 5 + Location.X;
    int y = 2 + Location.Y;
    
    // outer box frame
    SRectWireframe outer(x, y, 60, 18);
    outer.Render();
    
    // title bar at top
    SRectFilled titleBar(x, y, 60, 1, "#");
    titleBar.Render();
    DrawText(x + 15, y, "- EVENT RESULT -");
    
    // event name
    DrawText(x + 2, y + 3, "EVENT: " + Outcome.eventName);
    
    // separator line
    SRectFilled sep(x + 2, y + 4, 56, 1, "─");
    sep.Render();
    
    // player's choice and what happened
    DrawText(x + 2, y + 6, "You chose: " + Outcome.choiceMade);
    DrawText(x + 2, y + 7, "Result: " + Outcome.resultText);
    
    // build the changes table
    std::stringstream changes;
    changes << "\n[CHANGES]\n";
    changes << "├── HEALTH: " << (Outcome.deltaHealth >= 0 ? "+" : "") << Outcome.deltaHealth << "\n";
    changes << "├── FOOD:   " << (Outcome.deltaFood >= 0 ? "+" : "") << Outcome.deltaFood << "\n";
    changes << "└── WATER:  " << (Outcome.deltaWater >= 0 ? "+" : "") << Outcome.deltaWater << "\n";
    
    // add inventory updates if any items were added or removed
    if (!Outcome.itemsAdded.empty() || !Outcome.itemsRemoved.empty()) {
        changes << "\n[INVENTORY UPDATE]\n";
        for (const auto& item : Outcome.itemsAdded) {
            changes << "└── Added: " << item << "\n";
        }
        for (const auto& item : Outcome.itemsRemoved) {
            changes << "└── Removed: " << item << "\n";
        }
    }
    
    STextBox changesBox(x + 4, y + 9, 52, 8, changes.str(), true, true);
    changesBox.Render();
    
    // show current status after changes
    std::stringstream status;
    status << "Health: " << Health << "/" << MaxHealth
           << "  Food: " << Food << "/" << MaxFood
           << "  Water: " << Water << "/" << MaxWater;
    DrawText(x + 2, y + 14, status.str());
    
    // footer and wait for player
    DrawText(x + 15, y + 16, "PRESS ENTER");
    
    // wait for user to press enter
    std::cin.get();
}

// ============================================================
// SDailySummaryScreen - shows end of day stats
// called after daily consumption (-1 food -1 water)
// displays updated health food water bars and zone progress
// ============================================================

// Constructor: initializes daily summary screen.
// Inputs: day number, current zone, total zones, health, maxHealth, food, maxFood, water, maxWater, optional x,y offset.
// Outputs: none.
SDailySummaryScreen::SDailySummaryScreen(int day, int zone, int totalZones,
                                         int health, int maxHealth,
                                         int food, int maxFood,
                                         int water, int maxWater,
                                         int x, int y)
    : IScreenBase(x, y)
    , Day(day), Zone(zone), TotalZones(totalZones)
    , Health(health), MaxHealth(maxHealth)
    , Food(food), MaxFood(maxFood)
    , Water(water), MaxWater(maxWater) {}

// Renders the daily summary screen.
// Clears screen, draws box, shows daily consumption, health/food/water bars with values,
// zone progress, and waits for Enter.
// Inputs: none (uses member variables).
// Outputs: none (draws to screen, waits for input).
void SDailySummaryScreen::Render() {
    std::cout << "\033[2J\033[1;1H";
    
    int x = 5 + Location.X;
    int y = 2 + Location.Y;
    
    // outer frame
    SRectWireframe outer(x, y, 60, 18);
    outer.Render();
    
    // title
    std::string titleText = "END OF DAY " + std::to_string(Day);
    DrawText(x + 20, y + 1, titleText);
    
    // daily consumption section
    DrawText(x + 3, y + 4, "DAILY CONSUMPTION:");
    DrawText(x + 3, y + 5, "Food: -1");
    DrawText(x + 3, y + 6, "Water: -1");
    
    // health bar
    DrawText(x + 3, y + 9, "HEALTH:");
    DrawBar(x + 13, y + 9, 40, Health, MaxHealth);
    DrawText(x + 55, y + 9, std::to_string(Health) + "/" + std::to_string(MaxHealth));
    
    // food bar
    DrawText(x + 3, y + 11, "FOOD:");
    DrawBar(x + 13, y + 11, 40, Food, MaxFood);
    DrawText(x + 55, y + 11, std::to_string(Food) + "/" + std::to_string(MaxFood));
    
    // water bar
    DrawText(x + 3, y + 13, "WATER:");
    DrawBar(x + 13, y + 13, 40, Water, MaxWater);
    DrawText(x + 55, y + 13, std::to_string(Water) + "/" + std::to_string(MaxWater));
    
    // zone progress
    DrawText(x + 3, y + 16, "Zone: " + std::to_string(Zone) + "/" + std::to_string(TotalZones));
    
    // footer and wait for player
    DrawText(x + 15, y + 18, "Press Enter");
    
    // wait for user to press enter
    std::cin.get();
}

// ============================================================
// SDeathScreen - game over screen
// called when player dies (health <= 0 or food/water < 0)
// displays final stats and score
// ============================================================

// Constructor: initializes death screen.
// Inputs: zones cleared, days survived, final health, final food, final water, final score, optional x,y offset.
// Outputs: none.
SDeathScreen::SDeathScreen(int zonesCleared, int daysSurvived,
                           int finalHealth, int finalFood, int finalWater,
                           int finalScore, int x, int y)
    : IScreenBase(x, y)
    , ZonesCleared(zonesCleared), DaysSurvived(daysSurvived)
    , FinalHealth(finalHealth), FinalFood(finalFood), FinalWater(finalWater)
    , FinalScore(finalScore) {}

// Renders the game over screen.
// Clears screen, draws box, shows death message, final stats, score, and waits for Enter.
// Inputs: none (uses member variables).
// Outputs: none (draws to screen, waits for input).
void SDeathScreen::Render() {
    std::cout << "\033[2J\033[1;1H";
    
    int x = 5 + Location.X;
    int y = 2 + Location.Y;
    
    SRectWireframe outer(x, y, 60, 18);
    outer.Render();
    SRectFilled titleBar(x, y, 60, 1, "#");
    titleBar.Render();
    DrawText(x + 18, y, "- GAME OVER -");
    
    std::stringstream stats;
    stats << "\n   you didn't survive the forest...\n\n";
    stats << "   FINAL STATS\n";
    stats << "   --------------------------------\n";
    stats << "   zones cleared: " << ZonesCleared << "/6\n";
    stats << "   days survived: " << DaysSurvived << "\n";
    stats << "   final health:  " << FinalHealth << "\n";
    stats << "   food left: " << FinalFood << "\n";
    stats << "   water left: " << FinalWater << "\n\n";
    stats << "   FINAL SCORE: " << FinalScore << "\n\n";
    stats << "   [1] new game    [2] quit";
    
    STextBox statsBox(x + 2, y + 3, 56, 14, stats.str(), true, true);
    statsBox.Render();
    
    // wait for user input
    std::cin.get();
}

// ============================================================
// SVictoryScreen - win screen
// called when player clears all 6 zones
// displays final stats and score breakdown
// ============================================================

// Constructor: initializes victory screen.
// Inputs: zones cleared, days survived, final health, final food, final water,
//         items found (unused), difficulty multiplier (unused), final score, optional x,y offset.
// Outputs: none.
SVictoryScreen::SVictoryScreen(int zonesCleared, int daysSurvived,
                               int finalHealth, int finalFood, int finalWater,
                               int itemsFound, int multiplier, int finalScore,
                               int x, int y)
    : IScreenBase(x, y)
    , ZonesCleared(zonesCleared), DaysSurvived(daysSurvived)
    , FinalHealth(finalHealth), FinalFood(finalFood), FinalWater(finalWater)
    , ItemsFound(itemsFound), Multiplier(multiplier), FinalScore(finalScore) {}

// Renders the victory screen.
// Clears screen, draws box, shows escape message, final stats, score breakdown,
// final score, and waits for Enter.
// Inputs: none (uses member variables).
// Outputs: none (draws to screen, waits for input).
void SVictoryScreen::Render() {
    std::cout << "\033[2J\033[1;1H";
    
    int x = 5 + Location.X;
    int y = 2 + Location.Y;
    
    SRectWireframe outer(x, y, 60, 18);
    outer.Render();
    SRectFilled titleBar(x, y, 60, 1, "#");
    titleBar.Render();
    DrawText(x + 28, y, "- VICTORY -");
    
    std::stringstream stats;
    stats << "\n   you escaped the forest\n\n";
    stats << "   FINAL STATS\n";
    stats << "   --------------------------------\n";
    stats << "   zones cleared: " << ZonesCleared << "/6\n";
    stats << "   days survived: " << DaysSurvived << "\n";
    stats << "   final health:  " << FinalHealth << "\n";
    stats << "   items found: " << ItemsFound << "\n\n";
    stats << "   SCORE BREAKDOWN\n";
    stats << "   --------------------------------\n";
    
    // calculate score components
    int base = ZonesCleared * 100;
    int healthBonus = FinalHealth * 2;
    int foodBonus = FinalFood * 5;
    int waterBonus = FinalWater * 5;
    int itemsBonus = ItemsFound * 10;
    int daysBonus = DaysSurvived * 20;
    int subtotal = base + healthBonus + foodBonus + waterBonus + itemsBonus + daysBonus;
    
    stats << "   base (zones x 100):           " << base << "\n";
    stats << "   remaining health x 2:         " << healthBonus << "\n";
    stats << "   remaining food x 5:           " << foodBonus << "\n";
    stats << "   remaining water x 5:          " << waterBonus << "\n";
    stats << "   items found x 10:             " << itemsBonus << "\n";
    stats << "   days survived x 20:           " << daysBonus << "\n";
    stats << "   --------------------------------\n";
    stats << "   subtotal:                     " << subtotal << "\n";
    stats << "   difficulty multiplier x " << Multiplier << ":    " << FinalScore << "\n";
    stats << "   --------------------------------\n";
    stats << "   FINAL SCORE:                  " << FinalScore << "\n\n";
    stats << "   [1] play again   [2] high scores   [3] quit";
    
    STextBox statsBox(x + 2, y + 3, 56, 18, stats.str(), true, true);
    statsBox.Render();
    
    // wait for user input
    std::cin.get();
}

// ============================================================
// SChoiceMenu - simple menu for player choices
// used inside events to let player pick fight, run, hide, etc
// returns the index of what the player chose (0,1,2...)
// ============================================================

// Constructor: initializes choice menu with options, position, and layout.
// Inputs: vector of option strings, x,y position, horizontal flag (true for left-right, false for top-bottom).
// Outputs: none.
SChoiceMenu::SChoiceMenu(const std::vector<std::string>& options, int x, int y, bool horizontal)
    : IWidget(x, y), Options(options), SelectedIndex(0), bHorizontal(horizontal) {}

// Renders the choice menu: displays options with the currently selected one highlighted.
// Does not handle input.
// Inputs: none (uses member variables).
// Outputs: none (draws to screen).
void SChoiceMenu::Render() {
    int cx = Location.X;
    int cy = Location.Y;
    for (size_t i = 0; i < Options.size(); ++i) {
        std::string display = (i == SelectedIndex) ? "> " + Options[i] + " <" : "  " + Options[i] + "  ";
        DrawText(cx, cy, display);
        if (bHorizontal) {
            cx += (int)Options[i].length() + 6;
        } else {
            cy++;
        }
    }
    std::cout.flush();
}

// Waits for player to select an option using number keys.
// Displays numbered list below menu, reads input, validates.
// Returns zero-based index of the selected option.
// Inputs: none (uses member variables).
// Outputs: returns integer choice index.
int SChoiceMenu::WaitForSelection() {
    Render();
    for (size_t i = 0; i < Options.size(); ++i) {
        std::cout << "\n  " << (i + 1) << ". " << Options[i];
    }
    std::cout << "\nenter choice (1-" << Options.size() << "): ";
    
    int choice;
    std::cin >> choice;
    while (choice < 1 || choice > (int)Options.size()) {
        std::cout << "invalid. enter 1-" << Options.size() << ": ";
        std::cin >> choice;
    }
    return choice - 1;
}
