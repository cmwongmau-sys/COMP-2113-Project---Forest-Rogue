#include "Slate/SlateCore.h"
#include "Slate/Widgets/GameScreens.h"

#include <iostream>
#include <sstream>

void ShowEventResult_Demo()
{
    std::cout << "\033[2J\033[1;1H";

    SRectWireframe outer(5, 2, 60, 18);
    outer.Render();

    SRectFilled titleBar(5, 2, 60, 1);
    titleBar.Render();
    STextBox titleText(20, 2, 30, 1, "─ EVENT RESULT ─", false, false);
    titleText.Render();

    STextBox eventName(7, 5, 56, 1, "EVENT: Wild Boar Encounter", false, false);
    eventName.Render();
    SRectFilled sep(7, 6, 56, 1, "─");
    sep.Render();
    STextBox choice(7, 8, 56, 1, "You chose: FIGHT", false, false);
    choice.Render();
    STextBox result(7, 9, 56, 1, "Result: You defeated the boar but took damage!", false, false);
    result.Render();

    std::stringstream changes;
    changes << "\n[CHANGES]\n";
    changes << "├── HEALTH: 100 → 88  (-12)\n";
    changes << "├── FOOD:   3   → 5   (+2)\n";
    changes << "└── WATER:  2   → 2   (unchanged)\n\n";
    changes << "[INVENTORY UPDATE]\n";
    changes << "└── Added: Boar Meat x2\n";
    STextBox changesBox(9, 11, 52, 8, changes.str(), true, true);
    changesBox.Render();

    STextBox footer(21, 20, 30, 1, "PRESS ENTER TO CONTINUE", false, false);
    footer.Render();

    std::cin.get();
}

void ShowDailySummary_Demo() {
    std::cout << "\033[2J\033[1;1H";

    SRectWireframe outer(5, 2, 60, 18);
    outer.Render();

    STextBox title(25, 3, 30, 1, "END OF DAY 3", false, false);
    title.Render();

    STextBox eventInfo(8, 6, 48, 1, "EVENT: Wolf Attack", false, false);
    eventInfo.Render();
    STextBox choiceInfo(8, 7, 48, 1, "Your Choice: Fight", false, false);
    choiceInfo.Render();
    STextBox resultInfo(8, 8, 48, 1, "Result: Victory! -15 health, +2 food", false, false);
    resultInfo.Render();

    STextBox consumptionTitle(8, 10, 48, 1, "DAILY CONSUMPTION:", false, false);
    consumptionTitle.Render();
    STextBox foodCon(8, 11, 48, 1, "Food: 5 → 4 (-1)", false, false);
    foodCon.Render();
    STextBox waterCon(8, 12, 48, 1, "Water: 3 → 2 (-1)", false, false);
    waterCon.Render();

    STextBox healthLabel(8, 14, 10, 1, "HEALTH:", false, false);
    healthLabel.Render();
    DrawBar(18, 14, 32, 85, 100);
    STextBox(52, 14, 7, 1, "85/100", false, false).Render();

    STextBox foodLabel(8, 15, 10, 1, "FOOD:", false, false);
    foodLabel.Render();
    DrawBar(18, 15, 32, 4, 10);
    STextBox(52, 15, 7, 1, "4/10", false, false).Render();

    STextBox waterLabel(8, 16, 10, 1, "WATER:", false, false);
    waterLabel.Render();
    DrawBar(18, 16, 32, 2, 10);
    STextBox(52, 16, 7, 1, "2/10", false, false).Render();

    STextBox nextZone(8, 18, 48, 1, "Next Zone: 4/6", false, false);
    nextZone.Render();

    STextBox footer(18, 20, 40, 1, "Press Enter to continue to Day 4...", false, false);
    footer.Render();

    std::cin.get();
}

int main() {
    ShowEventResult_Demo();
    ShowDailySummary_Demo();
    return 0;
}