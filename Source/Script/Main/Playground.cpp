#include "../../Header/Slate/SlateCore.h"
#include "../../Header/Slate/Widgets/GameScreens.h"
#include <iostream>
#include <vector>

using namespace std;

int __main() {  // change to main() to run
    // Test 1: Event Result
    EventOutcome testOutcome;
    testOutcome.eventName = "Bear Attack";
    testOutcome.choiceMade = "FIGHT";
    testOutcome.resultText = "You fought bravely but got hurt";
    testOutcome.deltaHealth = -25;
    testOutcome.deltaFood = 2;
    testOutcome.deltaWater = 0;

    SEventResultScreen eventScreen(testOutcome, 75, 100, 5, 10, 3, 10);
    eventScreen.Render();

    // Test 2: Daily Summary
    SDailySummaryScreen dailyScreen(3, 4, 6, 75, 100, 5, 10, 3, 10);
    dailyScreen.Render();

    // Test 3: Death Screen
    SDeathScreen deathScreen(4, 6, 0, 2, 480);
    deathScreen.Render();

    // Test 4: Choice Menu
    cout << "\033[2J\033[1;1H";
    cout << "=== CHOICE MENU TEST ===\n\n";
    vector<string> choices = {"FIGHT", "RUN", "HIDE"};
    SChoiceMenu menu(choices, 20, 10, true);
    int choice = menu.WaitForSelection();
    cout << "\nYou picked: " << choices[choice] << endl;
    cout << "\nPress Enter to continue to victory screen...";
    cin.ignore();
    cin.get();

    // Test 5: Victory Screen
    SVictoryScreen victoryScreen(6, 45, 7, 5, 750);
    victoryScreen.Render();

    return 0;
}
