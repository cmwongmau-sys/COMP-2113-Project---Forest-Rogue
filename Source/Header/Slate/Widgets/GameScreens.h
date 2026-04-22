#ifndef GAME_SCREENS_H
#define GAME_SCREENS_H

#include "WidgetsCore.h"
#include <string>
#include <vector>

struct EventOutcome {
    std::string eventName;
    std::string choiceMade;
    std::string resultText;
    int deltaHealth = 0;
    int deltaFood = 0;
    int deltaWater = 0;
    std::vector<std::string> itemsAdded;
    std::vector<std::string> itemsRemoved;
};

struct SPlayerSetupInfo {
    std::string PlayerName;
    std::string SaveFilePath;   // empty if no file
    int Difficulty;             // 0 = Easy, 1 = Normal, 2 = Hard
};

class IScreenBase : public IWidget {
public:
    IScreenBase(int x = 0, int y = 0) : IWidget(x, y) {}
    virtual ~IScreenBase() = default;
    virtual void Render() override = 0;
};

class SEventResultScreen : public IScreenBase {
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
                       int x = 0, int y = 0);
    void Render() override;
};

class SDailySummaryScreen : public IScreenBase {
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
                        int x = 0, int y = 0);
    void Render() override;
};

class SDeathScreen : public IScreenBase {
private:
    int ZonesCleared;
    int FinalHealth, FinalFood, FinalWater, FinalScore;
public:
    SDeathScreen(int zonesCleared,
                 int finalHealth, int finalFood, int finalWater,
                 int finalScore, int x = 0, int y = 0);
    void Render() override;
};

class SVictoryScreen : public IScreenBase {
private:
    int ZonesCleared;
    int FinalHealth, FinalFood, FinalWater, FinalScore;
public:
    SVictoryScreen(int zonesCleared,
                   int finalHealth, int finalFood, int finalWater,
                   int finalScore, int x = 0, int y = 0);
    void Render() override;
};

class SChoiceMenu : public IWidget {
private:
    std::vector<std::string> Options;
    int SelectedIndex;
    bool bHorizontal;
public:
    SChoiceMenu(const std::vector<std::string>& options, int x, int y, bool horizontal = true);
    void Render() override;
    int WaitForSelection();
    int GetSelectedIndex() const { return SelectedIndex; }
    std::string GetSelectedOption() const { return Options[SelectedIndex]; }
};

#endif

class SPlayerSetupScreen : public IScreenBase {
public:
    SPlayerSetupScreen(int x = 0, int y = 0);
    virtual void Render() override;          // draws the frame and title
    SPlayerSetupInfo Run();                  // runs the interactive sequence

private:
    // Helper methods for input inside the frame
    std::string GetUserInput(int x, int y, const std::string& prompt);
    bool AskYesNo(int x, int y, const std::string& question);
};
