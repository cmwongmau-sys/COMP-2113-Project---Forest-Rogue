#include <iostream>   // 临时，用于事件描述，后续应替换为屏幕函数
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <string>
#include "random.h"
#include "GameScreens.h"
using namespace std;

// ========== 野生生物 ==========
EventOutcome wildAnimalEncounter(int difficulty, int &health, int &food, int &water) {
    EventOutcome outcome;
    outcome.eventName = "Wild Animal";
    cout << "A wild animal appears!" << endl;

    std::vector<std::string> options = {"Fight", "Flee"};
    SChoiceMenu menu(options, 10, 10, true);
    int selectedIndex = menu.WaitForSelection();   // 0: Fight, 1: Flee
    outcome.choiceMade = options[selectedIndex];

    int roll = rand() % 100 + 1;

    if (selectedIndex == 0) {  // Fight
        if (roll <= 50) {   // 胜利
            int damage = (difficulty == 1) ? (5 + rand()%6) :
                         (difficulty == 2) ? (10 + rand()%6) :
                                              (15 + rand()%6);
            health -= damage;
            food += 2;
            outcome.deltaHealth = -damage;
            outcome.deltaFood = 2;
            outcome.resultText = "You fought bravely!";
        } else {            // 失败
            int damage = (difficulty == 1) ? (15 + rand()%11) :
                         (difficulty == 2) ? (15 + rand()%11) :
                                              (20 + rand()%6);
            health -= damage;
            outcome.deltaHealth = -damage;
            outcome.resultText = "You lost the fight!";
        }
    } else {  // Flee
        if (roll <= 50) {   // 成功逃跑
            outcome.resultText = "You fled successfully.";
        } else {            // 逃跑失败
            int damage = 10 + rand()%11;
            health -= damage;
            outcome.deltaHealth = -damage;
            outcome.resultText = "Failed to flee!";
        }
    }

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
    return outcome;
}

// ========== 宝藏 ==========
EventOutcome treasureEncounter(int difficulty, int &health, int &food, int &water) {
    EventOutcome outcome;
    outcome.eventName = "Treasure";

    cout << "You found an abandoned campsite!" << endl;

    std::vector<std::string> options = {"Take items"};
    SChoiceMenu menu(options, 10, 10, true);
    int selectedIndex = menu.WaitForSelection();   // 0
    outcome.choiceMade = options[selectedIndex];

    int items = rand() % 3 + 1;   // 1~3 件物品
    for (int i = 0; i < items; i++) {
        int reward = rand() % 3;
        if (reward == 0) {
            int gained = rand() % 3 + 1;
            food += gained;
            outcome.deltaFood += gained;
            outcome.itemsAdded.push_back("Food +" + to_string(gained));
        } else if (reward == 1) {
            int gained = rand() % 3 + 1;
            water += gained;
            outcome.deltaWater += gained;
            outcome.itemsAdded.push_back("Water +" + to_string(gained));
        } else {
            int heal = 30;
            health = min(100, health + heal);
            outcome.deltaHealth += heal;
            outcome.itemsAdded.push_back("Healing Potion (+30 health)");
        }
    }
    outcome.resultText = "You found treasure!";

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
    return outcome;
}

// ========== 陷阱 ==========
EventOutcome trapEncounter(int difficulty, int &health, int &food, int &water) {
    EventOutcome outcome;
    outcome.eventName = "Trap";

    cout << "You step into a trap!" << endl;

    std::vector<std::string> options = {"Try escape", "Cut free (cost 1 food)", "Wait for help"};
    SChoiceMenu menu(options, 10, 10, true);
    int selectedIndex = menu.WaitForSelection();   // 0,1,2
    outcome.choiceMade = options[selectedIndex];

    int roll = rand() % 100 + 1;

    if (selectedIndex == 0) {  // Try escape
        if (roll <= 70) {
            outcome.resultText = "You escaped safely.";
        } else {
            health -= 15;
            outcome.deltaHealth = -15;
            outcome.resultText = "Failed to escape!";
        }
    } else if (selectedIndex == 1) {  // Cut free
        if (food > 0) {
            food -= 1;
            outcome.deltaFood = -1;
            outcome.itemsRemoved.push_back("Food");
            outcome.resultText = "You cut yourself free.";
        } else {
            outcome.resultText = "No food to sacrifice! You remain trapped.";
        }
    } else {  // Wait for help
        if (food > 0) { food -= 1; outcome.deltaFood = -1; }
        if (water > 0) { water -= 1; outcome.deltaWater = -1; }
        outcome.resultText = "You waited for help. Escaped next day.";
    }

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
    return outcome;
}

// ========== 泉水 ==========
EventOutcome waterSpringEncounter(int difficulty, int &health, int &food, int &water) {
    EventOutcome outcome;
    outcome.eventName = "Water Spring";
    outcome.choiceMade = "None";

    cout << "You find a crystal-clear spring!" << endl;

    int waterGain = 2 + rand() % 3;   // 2,3,4
    water += waterGain;
    outcome.deltaWater = waterGain;
    outcome.resultText = "You drink from the spring.";

    if (rand() % 100 < 50) {
        int heal = 10;
        health += heal;
        if (health > 100) health = 100;
        outcome.deltaHealth = heal;
        outcome.resultText += " The magical water also restores health!";
    }

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
    return outcome;
}

// ========== 浆果丛 ==========
EventOutcome berryBushEncounter(int difficulty, int &health, int &food, int &water) {
    EventOutcome outcome;
    outcome.eventName = "Berry Bush";
    outcome.choiceMade = "None";

    cout << "You spot a bush full of berries!" << endl;

    int foodGain = 1 + rand() % 3;   // 1,2,3
    food += foodGain;
    outcome.deltaFood = foodGain;
    outcome.resultText = "You eat the sweet berries.";

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
    return outcome;
}

// ========== 天气事件 ==========
EventOutcome weatherEncounter(int difficulty, int &health, int &food, int &water) {
    EventOutcome outcome;
    outcome.eventName = "Weather Event";
    outcome.choiceMade = "None";

    cout << "The weather changes suddenly!" << endl;

    int weatherType = rand() % 4; // 0: Rain, 1: Heat wave, 2: Cold snap, 3: Mild
    switch (weatherType) {
        case 0: { // Rain
            int waterGain = 1 + rand() % 2;
            water += waterGain;
            outcome.deltaWater = waterGain;
            outcome.resultText = "Rain provides fresh water.";
            break;
        }
        case 1: { // Heat wave
            int waterLoss = 2;
            water -= waterLoss;
            if (water < 0) water = 0;
            outcome.deltaWater = -waterLoss;
            outcome.resultText = "Heat wave causes dehydration!";
            break;
        }
        case 2: { // Cold snap
            int damage = 5;
            health -= damage;
            if (health < 0) health = 0;
            outcome.deltaHealth = -damage;
            outcome.resultText = "Cold snap damages your health.";
            break;
        }
        case 3: { // Mild
            outcome.resultText = "The weather is mild. Nothing happens.";
            break;
        }
    }

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
    return outcome;
}

// ========== 空事件 ==========
EventOutcome emptyEncounter(int difficulty, int &health, int &food, int &water) {
    EventOutcome outcome;
    outcome.eventName = "Empty";
    outcome.choiceMade = "None";
    outcome.resultText = "Nothing interesting happens today.";

    cout << "You wander through the forest... It's quiet." << endl;

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
    return outcome;
}
