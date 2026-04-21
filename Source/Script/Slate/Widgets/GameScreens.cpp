#include "../../../Header/Slate/Widgets/GameScreens.h"
#include "../../../Header/Slate/Widgets/WidgetsCore.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void DrawBar(int x, int y, int width, int current, int max,
             const std::string fillChar,
             const std::string emptyChar)
{
    float percent = (max > 0) ? (float)current / max : 0.0f;
    SBar bar(x, y, width, 1, percent, emptyChar, fillChar);
    bar.Render();
}

static void DrawText(int x, int y, const std::string& text) {
    STextBox box(x, y, (int)text.length(), 1, text, false, false);
    box.Render();
}

static void DrawCentered(int x, int y, int boxWidth, const std::string& text) {
    int textLen = (int)text.length();
    int centeredX = x + (boxWidth - textLen) / 2;
    DrawText(centeredX, y, text);
}

// ============================================================
// SEventResultScreen
// ============================================================

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

void SEventResultScreen::Render() {
    std::cout << "\033[2J\033[1;1H";
    int x = 5 + Location.X;
    int y = 2 + Location.Y;
    
    SRectWireframe outer(x, y, 80, 20);
    outer.Render();
    SRectFilled titleBar(x, y, 80, 1, "#");
    titleBar.Render();
    DrawCentered(x, y, 80, "- EVENT RESULT -");
    
    DrawText(x + 2, y + 3, "EVENT: " + Outcome.eventName);
    SRectFilled sep(x + 2, y + 4, 76, 1, "─");
    sep.Render();
    DrawText(x + 2, y + 6, "You chose: " + Outcome.choiceMade);
    DrawText(x + 2, y + 7, "Result: " + Outcome.resultText);
    
    std::stringstream changes;
    changes << "\n[CHANGES]\n";
    changes << "├── HEALTH: " << (Outcome.deltaHealth >= 0 ? "+" : "") << Outcome.deltaHealth << "\n";
    changes << "├── FOOD:   " << (Outcome.deltaFood >= 0 ? "+" : "") << Outcome.deltaFood << "\n";
    changes << "└── WATER:  " << (Outcome.deltaWater >= 0 ? "+" : "") << Outcome.deltaWater << "\n";
    if (!Outcome.itemsAdded.empty() || !Outcome.itemsRemoved.empty()) {
        changes << "\n[INVENTORY UPDATE]\n";
        for (const auto& item : Outcome.itemsAdded) changes << "└── Added: " << item << "\n";
        for (const auto& item : Outcome.itemsRemoved) changes << "└── Removed: " << item << "\n";
    }
    STextBox changesBox(x + 4, y + 9, 72, 8, changes.str(), true, true);
    changesBox.Render();
    
    std::stringstream status;
    status << "Health: " << Health << "/" << MaxHealth
           << "  Food: " << Food << "/" << MaxFood
           << "  Water: " << Water << "/" << MaxWater;
    DrawText(x + 2, y + 16, status.str());
    DrawCentered(x, y + 18, 80, "PRESS ENTER");
    std::cin.get();
}

// ============================================================
// SDailySummaryScreen
// ============================================================

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

void SDailySummaryScreen::Render() {
    std::cout << "\033[2J\033[1;1H";
    int x = 5 + Location.X;
    int y = 2 + Location.Y;
    
    SRectWireframe outer(x, y, 80, 20);
    outer.Render();
    std::string titleText = "END OF DAY " + std::to_string(Day);
    DrawCentered(x, y + 1, 80, titleText);
    
    DrawText(x + 3, y + 4, "DAILY CONSUMPTION:");
    DrawText(x + 3, y + 5, "Food: -1");
    DrawText(x + 3, y + 6, "Water: -1");
    
    DrawText(x + 3, y + 9, "HEALTH:");
    DrawBar(x + 13, y + 9, 55, Health, MaxHealth, "█", ".");
    DrawText(x + 71, y + 9, std::to_string(Health) + "/" + std::to_string(MaxHealth));
    
    DrawText(x + 3, y + 11, "FOOD:");
    DrawBar(x + 13, y + 11, 55, Food, MaxFood, "█", ".");
    DrawText(x + 71, y + 11, std::to_string(Food) + "/" + std::to_string(MaxFood));
    
    DrawText(x + 3, y + 13, "WATER:");
    DrawBar(x + 13, y + 13, 55, Water, MaxWater, "█", ".");
    DrawText(x + 71, y + 13, std::to_string(Water) + "/" + std::to_string(MaxWater));
    
    DrawCentered(x, y + 16, 80, "Zone: " + std::to_string(Zone) + "/" + std::to_string(TotalZones));
    DrawCentered(x, y + 18, 80, "Press Enter");
    std::cin.get();
}

// ============================================================
// SDeathScreen
// ============================================================

SDeathScreen::SDeathScreen(int zonesCleared,
                           int finalHealth, int finalFood, int finalWater,
                           int finalScore, int x, int y)
    : IScreenBase(x, y)
    , ZonesCleared(zonesCleared)
    , FinalHealth(finalHealth), FinalFood(finalFood), FinalWater(finalWater)
    , FinalScore(finalScore) {}

void SDeathScreen::Render() {
    std::cout << "\033[2J\033[1;1H";
    int x = 5 + Location.X;
    int y = 2 + Location.Y;
    
    SRectWireframe outer(x, y, 80, 22);
    outer.Render();
    SRectFilled titleBar(x, y, 80, 1, "#");
    titleBar.Render();
    DrawCentered(x, y, 80, "- GAME OVER -");
    
    std::stringstream stats;
    stats << "\n   you didn't survive the forest...\n\n";
    stats << "   FINAL STATS\n";
    stats << "   --------------------------------\n";
    stats << "   zones cleared: " << ZonesCleared << "/6\n";
    stats << "   final health:  " << FinalHealth << "\n";
    stats << "   food left: " << FinalFood << "\n";
    stats << "   water left: " << FinalWater << "\n\n";
    stats << "   FINAL SCORE: " << FinalScore << "\n";
    
    STextBox statsBox(x + 2, y + 3, 76, 14, stats.str(), true, true);
    statsBox.Render();
    DrawCentered(x, y + 18, 80, "PRESS ENTER");
    std::cin.get();
}

// ============================================================
// SVictoryScreen
// ============================================================

SVictoryScreen::SVictoryScreen(int zonesCleared,
                               int finalHealth, int finalFood, int finalWater,
                               int finalScore, int x, int y)
    : IScreenBase(x, y)
    , ZonesCleared(zonesCleared)
    , FinalHealth(finalHealth), FinalFood(finalFood), FinalWater(finalWater)
    , FinalScore(finalScore) {}

void SVictoryScreen::Render() {
    std::cout << "\033[2J\033[1;1H";
    int x = 5 + Location.X;
    int y = 2 + Location.Y;
    
    SRectWireframe outer(x, y, 80, 22);
    outer.Render();
    SRectFilled titleBar(x, y, 80, 1, "#");
    titleBar.Render();
    DrawCentered(x, y, 80, "- VICTORY -");
    
    std::stringstream stats;
    stats << "   you escaped the forest\n\n";
    stats << "   FINAL STATS\n";
    stats << "   --------------------------------\n";
    stats << "   zones cleared: " << ZonesCleared << "/6\n";
    stats << "   final health:  " << FinalHealth << "\n\n";
    stats << "   SCORE BREAKDOWN\n";
    stats << "   --------------------------------\n";
    
    int base = ZonesCleared * 100;
    int healthBonus = FinalHealth * 2;
    int foodBonus = FinalFood * 5;
    int waterBonus = FinalWater * 5;
    int subtotal = base + healthBonus + foodBonus + waterBonus;
    
    stats << "   base (zones x 100):           " << base << "\n";
    stats << "   remaining health x 2:         " << healthBonus << "\n";
    stats << "   remaining food x 5:           " << foodBonus << "\n";
    stats << "   remaining water x 5:          " << waterBonus << "\n";
    stats << "   --------------------------------\n";
    stats << "   subtotal:                     " << subtotal << "\n";
    stats << "   --------------------------------\n";
    stats << "   FINAL SCORE:                  " << FinalScore << "\n";
    
    STextBox statsBox(x + 2, y + 3, 76, 16, stats.str(), true, true);
    statsBox.Render();
    DrawCentered(x, y + 20, 80, "PRESS ENTER");
    std::cin.get();
}

// ============================================================
// SChoiceMenu
// ============================================================

SChoiceMenu::SChoiceMenu(const std::vector<std::string>& options, int x, int y, bool horizontal)
    : IWidget(x, y), Options(options), SelectedIndex(0), bHorizontal(horizontal) {}

void SChoiceMenu::Render() {
    int cx = Location.X;
    int cy = Location.Y;
    for (size_t i = 0; i < Options.size(); ++i) {
        std::string display = (i == SelectedIndex) ? "> " + Options[i] + " <" : "  " + Options[i] + "  ";
        DrawText(cx, cy, display);
        if (bHorizontal) cx += (int)Options[i].length() + 6;
        else cy++;
    }
    std::cout.flush();
}

int SChoiceMenu::WaitForSelection() {
    Render();
    std::cout << "\n";
    for (size_t i = 0; i < Options.size(); ++i)
        std::cout << "  " << (i + 1) << ". " << Options[i] << "\n";
    std::cout << "\nenter choice (1-" << Options.size() << "): ";
    int choice;
    std::cin >> choice;
    while (choice < 1 || choice > (int)Options.size()) {
        std::cout << "invalid. enter 1-" << Options.size() << ": ";
        std::cin >> choice;
    }
    return choice - 1;
}

// ============================================================
// SSetUpScreen
// ============================================================
SPlayerSetupScreen::SPlayerSetupScreen(int x, int y) : IScreenBase(x, y) {}

void SPlayerSetupScreen::Render() {
    std::cout << "\033[2J\033[1;1H";   // clear screen
    int x = Location.X + 5;
    int y = Location.Y + 2;
    SRectWireframe frame(x, y, 60, 18);
    frame.Render();
    DrawText(x + 60/2 - 6, y + 1, "PLAYER SETUP");
}

std::string SPlayerSetupScreen::GetUserInput(int x, int y, const std::string& prompt) {
    DrawText(x, y, prompt);
    // Move cursor to end of prompt
    std::cout << "\033[" << y << ";" << (x + prompt.length()) << "H";
    std::string input;
    std::getline(std::cin, input);
    return input;
}

bool SPlayerSetupScreen::AskYesNo(int x, int y, const std::string& question) {
    DrawText(x, y, question + " (Y/N): ");
    std::cout << "\033[" << y << ";" << (x + question.length() + 8) << "H";
    char ch;
    std::cin >> ch;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return (ch == 'y' || ch == 'Y');
}

SPlayerSetupInfo SPlayerSetupScreen::Run() {
    Render();   // draw the background frame

    int frameX = Location.X + 5;
    int frameY = Location.Y + 2;
    int cursorY = frameY + 3;      // first line inside the frame

    // 1. Player name
    std::string name = GetUserInput(frameX + 2, cursorY, "Enter your name: ");
    cursorY += 2;

    // 2. Ask about save file
    bool hasFile = AskYesNo(frameX + 2, cursorY, "Load from save file?");
    cursorY += 2;

    std::string filepath;
    if (hasFile) {
        filepath = GetUserInput(frameX + 2, cursorY, "File path: ");
        cursorY += 2;
    }

    // 3. Difficulty selection using SChoiceMenu
    //    Draw the options manually to keep everything inside the frame
    DrawText(frameX + 2, cursorY, "Select difficulty:");
    cursorY++;
    std::vector<std::string> difficulties = {"Easy", "Normal", "Hard"};
    for (size_t i = 0; i < difficulties.size(); ++i) {
        DrawText(frameX + 6, cursorY + (int)i, std::to_string(i+1) + ". " + difficulties[i]);
    }
    std::string choiceStr = GetUserInput(frameX + 6, cursorY + (int)difficulties.size(),
                                           "Choice (1-3): ");
    int diffIndex = std::stoi(choiceStr) - 1;
    // Clamp in case of invalid input
    if (diffIndex < 0) diffIndex = 0;
    if (diffIndex >= (int)difficulties.size()) diffIndex = (int)difficulties.size() - 1;

    // Wait for user to acknowledge before leaving the screen
    DrawText(frameX + 2, cursorY + (int)difficulties.size() + 2, "Press Enter to continue...");
    std::cin.get();

    // Fill and return the info struct
    SPlayerSetupInfo info;
    info.PlayerName = name;
    info.SaveFilePath = filepath;
    info.Difficulty = diffIndex;
    return info;
}
