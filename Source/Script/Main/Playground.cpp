#include "Slate/SlateCore.h"
#include "Slate/Widgets/GameScreens.h"

#include <iostream>
#include <sstream>

void ShowEventResult_Demo()
{
    std::cout << "\033[2J\033[1;1H";

    SRectWireframe outer(10, 2, 60, 15);
    outer.Render();

    SRectFilled titleBar(10, 2, 60, 1);
    titleBar.Render();
    STextBox titleText(25, 2, 30, 1, "─ EVENT RESULT ─", false, false);
    titleText.Render();

    STextBox eventName(12, 5, 56, 1, "EVENT: Wild Boar Encounter", false, false);
    eventName.Render();
    SRectFilled sep(12, 6, 56, 1, "─");
    sep.Render();
    STextBox choice(12, 8, 56, 1, "You chose: FIGHT", false, false);
    choice.Render();
    STextBox result(12, 9, 56, 1, "Result: You defeated the boar but took damage!", false, false);
    result.Render();

    std::stringstream changes;
    changes << "\n[CHANGES]\n";
    changes << "├── HEALTH: 100 → 88  (-12)\n";
    changes << "├── FOOD:   3   → 5   (+2)\n";
    changes << "└── WATER:  2   → 2   (unchanged)\n\n";
    changes << "[INVENTORY UPDATE]\n";
    changes << "└── Added: Boar Meat x2\n";
    STextBox changesBox(14, 11, 52, 8, changes.str(), true, true);
    changesBox.Render();

    STextBox footer(25, 18, 30, 1, "PRESS ENTER TO CONTINUE", false, false);
    footer.Render();

    std::cin.get();
}

void ShowDailySummary_Demo() {
    std::cout << "\033[2J\033[1;1H";

    SRectWireframe outer(5, 2, 70, 18);
    outer.Render();

    STextBox title(25, 3, 30, 1, "END OF DAY 3", false, false);
    title.Render();

    STextBox eventInfo(8, 6, 64, 1, "EVENT: Wolf Attack", false, false);
    eventInfo.Render();
    STextBox choiceInfo(8, 7, 64, 1, "Your Choice: Fight", false, false);
    choiceInfo.Render();
    STextBox resultInfo(8, 8, 64, 1, "Result: Victory! -15 health, +2 food", false, false);
    resultInfo.Render();

    STextBox consumptionTitle(8, 10, 64, 1, "DAILY CONSUMPTION:", false, false);
    consumptionTitle.Render();
    STextBox foodCon(8, 11, 64, 1, "Food: 5 → 4 (-1)", false, false);
    foodCon.Render();
    STextBox waterCon(8, 12, 64, 1, "Water: 3 → 2 (-1)", false, false);
    waterCon.Render();

    STextBox healthLabel(8, 14, 10, 1, "HEALTH:", false, false);
    healthLabel.Render();
    DrawBar(18, 14, 40, 85, 100);
    std::cout << "\033[14;60H85/100";

    STextBox foodLabel(8, 15, 10, 1, "FOOD:", false, false);
    foodLabel.Render();
    DrawBar(18, 15, 40, 4, 10);
    std::cout << "\033[15;60H4/10";

    STextBox waterLabel(8, 16, 10, 1, "WATER:", false, false);
    waterLabel.Render();
    DrawBar(18, 16, 40, 2, 10);
    std::cout << "\033[16;60H2/10";

    STextBox nextZone(8, 18, 64, 1, "Next Zone: 4/6", false, false);
    nextZone.Render();

    STextBox footer(20, 20, 40, 1, "Press Enter to continue to Day 4...", false, false);
    footer.Render();

    std::cin.get();
}

int main() {
    ShowEventResult_Demo();
    ShowDailySummary_Demo();
    return 0;
}