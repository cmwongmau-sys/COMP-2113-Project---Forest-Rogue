#include "Slate/Widgets/GameScreens.h"
#include "Slate/Widgets/WidgetsCore.h"
#include <iostream>
#include <sstream>

// helper to draw a status bar
// uses SBar widget
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
static void DrawText(int x, int y, const std::string& text) {
    STextBox box(x, y, (int)text.length(), 1, text, false, false);
    box.Render();
}

// ============================================================
// SEventResultScreen - shows what happened during a random event
// called after bear attack, treasure, trap, etc
// displays changes to health food water and items found
// ============================================================

SEventResultScreen::SEventResultScreen(const EventOutcome& outcome,
                                       int health, int maxHealth,
                                       int food, int maxFood,
                                       int water, int maxWater,
                                       int offsetX, int offsetY)
    : IScreenBase(offsetX, offsetY)
    , Outcome(outcome)
    , Health(health), MaxHealth(maxHealth)
    , Food(food), MaxFood(maxFood)
    , Water(water), MaxWater(maxWater) {}

void SEventResultScreen::Render() {
    // clear screen and move cursor to top
    std::cout << "\033[2J\033[1;1H";
    
    // apply offset if any
    int x = 10 + Location.X;
    int y = 2 + Location.Y;
    
    // outer box frame
    SRectWireframe outer(x, y, 60, 15);
    outer.Render();
    
    // title bar at top
    SRectFilled titleBar(x, y, 60, 1, "#");
    titleBar.Render();
    STextBox titleText(x + 15, y, 30, 1, "- EVENT RESULT -", false, false);
    titleText.Render();
    
    // event name
    STextBox eventName(x + 2, y + 3, 56, 1, "EVENT: " + Outcome.eventName, false, false);
    eventName.Render();
    
    // separator line
    SRectFilled sep(x + 2, y + 4, 56, 1, "─");
    sep.Render();
    
    // player's choice and what happened
    STextBox choice(x + 2, y + 6, 56, 1, "You chose: " + Outcome.choiceMade, false, false);
    choice.Render();
    STextBox result(x + 2, y + 7, 56, 1, "Result: " + Outcome.resultText, false, false);
    result.Render();
    
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
    STextBox statusBox(x + 2, y + 14, 56, 1, status.str(), false, false);
    statusBox.Render();
    
    // footer and wait for player
    STextBox footer(x + 15, y + 16, 30, 1, "PRESS ENTER", false, false);
    footer.Render();
    
    // wait for user to press enter
    std::cin.get();
}

// ============================================================
// SDailySummaryScreen - shows end of day stats
// called after daily consumption (-1 food -1 water)
// displays updated health food water bars and zone progress
// ============================================================

SDailySummaryScreen::SDailySummaryScreen(int day, int zone, int totalZones,
                                         int health, int maxHealth,
                                         int food, int maxFood,
                                         int water, int maxWater,
                                         int offsetX, int offsetY)
    : IScreenBase(offsetX, offsetY, 70, 18)
    , Day(day), Zone(zone), TotalZones(totalZones)
    , Health(health), MaxHealth(maxHealth)
    , Food(food), MaxFood(maxFood)
    , Water(water), MaxWater(maxWater) {}

void SDailySummaryScreen::Render() {
    std::cout << "\033[2J\033[1;1H";
    
    int x = 5 + Location.X;
    int y = 2 + Location.Y;
    
    // outer frame
    SRectWireframe outer(x, y, 70, 18);
    outer.Render();
    
    // title
    std::string titleText = "END OF DAY " + std::to_string(Day);
    STextBox title(x + 20, y + 1, 30, 1, titleText, false, false);
    title.Render();
    
    // daily consumption section
    STextBox consumptionTitle(x + 3, y + 4, 64, 1, "DAILY CONSUMPTION:", false, false);
    consumptionTitle.Render();
    STextBox foodCon(x + 3, y + 5, 64, 1, "Food: -1", false, false);
    foodCon.Render();
    STextBox waterCon(x + 3, y + 6, 64, 1, "Water: -1", false, false);
    waterCon.Render();
    
    // health bar
    STextBox healthLabel(x + 3, y + 9, 10, 1, "HEALTH:", false, false);
    healthLabel.Render();
    DrawBar(x + 13, y + 9, 40, Health, MaxHealth);
    DrawText(x + 55, y + 9, std::to_string(Health) + "/" + std::to_string(MaxHealth));
    
    // food bar
    STextBox foodLabel(x + 3, y + 11, 10, 1, "FOOD:", false, false);
    foodLabel.Render();
    DrawBar(x + 13, y + 11, 40, Food, MaxFood);
    DrawText(x + 55, y + 11, std::to_string(Food) + "/" + std::to_string(MaxFood));
    
    // water bar
    STextBox waterLabel(x + 3, y + 13, 10, 1, "WATER:", false, false);
    waterLabel.Render();
    DrawBar(x + 13, y + 13, 40, Water, MaxWater);
    DrawText(x + 55, y + 13, std::to_string(Water) + "/" + std::to_string(MaxWater));
    
    // zone progress
    STextBox nextZone(x + 3, y + 16, 64, 1,
        "Zone: " + std::to_string(Zone) + "/" + std::to_string(TotalZones), false, false);
    nextZone.Render();
    
    // footer and wait for player
    STextBox footer(x + 15, y + 18, 40, 1, "Press Enter", false, false);
    footer.Render();
    
    // wait for user to press enter
    std::cin.get();
}

// ============================================================
// SDeathScreen - game over screen
// called when player dies (health <= 0 or food/water < 0)
// displays final stats and score
// ============================================================

SDeathScreen::SDeathScreen(int zonesCleared, int daysSurvived,
                           int finalHealth, int finalFood, int finalWater,
                           int finalScore, int offsetX, int offsetY)
    : IScreenBase(offsetX, offsetY)
    , ZonesCleared(zonesCleared), DaysSurvived(daysSurvived)
    , FinalHealth(finalHealth), FinalFood(finalFood), FinalWater(finalWater)
    , FinalScore(finalScore) {}

void SDeathScreen::Render() {
    std::cout << "\033[2J\033[1;1H";
    
    int x = 10 + Location.X;
    int y = 2 + Location.Y;
    
    SRectWireframe outer(x, y, 60, 16);
    outer.Render();
    SRectFilled titleBar(x, y, 60, 1, "#");
    titleBar.Render();
    STextBox title(x + 18, y, 30, 1, "- GAME OVER -", false, false);
    title.Render();
    
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

SVictoryScreen::SVictoryScreen(int zonesCleared, int daysSurvived,
                               int finalHealth, int finalFood, int finalWater,
                               int itemsFound, int multiplier, int finalScore,
                               int offsetX, int offsetY)
    : IScreenBase(offsetX, offsetY)
    , ZonesCleared(zonesCleared), DaysSurvived(daysSurvived)
    , FinalHealth(finalHealth), FinalFood(finalFood), FinalWater(finalWater)
    , ItemsFound(itemsFound), Multiplier(multiplier), FinalScore(finalScore) {}

void SVictoryScreen::Render() {
    std::cout << "\033[2J\033[1;1H";
    
    int x = 5 + Location.X;
    int y = 2 + Location.Y;
    
    SRectWireframe outer(x, y, 70, 20);
    outer.Render();
    SRectFilled titleBar(x, y, 70, 1, "#");
    titleBar.Render();
    STextBox title(x + 28, y, 30, 1, "- VICTORY -", false, false);
    title.Render();
    
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
    
    STextBox statsBox(x + 2, y + 3, 66, 18, stats.str(), true, true);
    statsBox.Render();
    
    // wait for user input
    std::cin.get();
}

// ============================================================
// SChoiceMenu - simple menu for player choices
// used inside events to let player pick fight, run, hide, etc
// returns the index of what the player chose (0,1,2...)
// ============================================================

SChoiceMenu::SChoiceMenu(const std::vector<std::string>& options, int x, int y, bool horizontal)
    : IWidget(X, Y), Options(options), SelectedIndex(0), bHorizontal(horizontal) { }

void SChoiceMenu::Render() {
    int cx = X, cy = Y;
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

// simple number based selection
// shows options as 1 2 3 and waits for player to type a number
// can be upgraded to arrow keys later if needed
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
