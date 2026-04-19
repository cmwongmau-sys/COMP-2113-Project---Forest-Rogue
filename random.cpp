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
void wildAnimalEncounter(int difficulty, int &health, int &food, int &water) {
    vector<string> options = {"Fight", "Flee"};
    SChoiceMenu menu(options, 10, 5);
    menu.Render();
    int choiceIndex = menu.WaitForSelection();

    EventOutcome outcome;
    outcome.eventName = "Wild Animal";
    outcome.choiceMade = options[choiceIndex];

    int roll = rand()%100 + 1;
    if (choiceIndex == 0) { // Fight
        if (roll <= 50) {
            int damage = (difficulty==1)?(5+rand()%6):(difficulty==2)?(10+rand()%6):(15+rand()%6);
            health -= damage; food += 2;
            outcome.resultText = "You won the fight!";
            outcome.deltaHealth = -damage;
            outcome.deltaFood = +2;
        } else {
            int damage = (difficulty==1)?(15+rand()%11):(difficulty==2)?(15+rand()%11):(20+rand()%6);
            health -= damage;
            outcome.resultText = "You lost the fight!";
            outcome.deltaHealth = -damage;
        }
    } else { // Flee
        if (roll <= 50) {
            outcome.resultText = "You fled successfully.";
        } else {
            int damage = 10+rand()%11;
            health -= damage;
            outcome.resultText = "Failed to flee!";
            outcome.deltaHealth = -damage;
        }
    }

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10);
    resultScreen.Render();
}

// ========== 宝藏 ==========
void treasureEncounter(int difficulty, int &health, int &food, int &water) {
    vector<string> options = {"Take items"};
    SChoiceMenu menu(options, 10, 5);
    menu.Render();
    int choiceIndex = menu.WaitForSelection();

    EventOutcome outcome;
    outcome.eventName = "Treasure";
    outcome.choiceMade = options[choiceIndex];

    if (choiceIndex == 0) {
        int items = rand()%3 + 1;
        for (int i = 0; i < items; i++) {
            int reward = rand()%3;
            if (reward == 0) {
                int gained = rand()%3 + 1;
                food += gained;
                outcome.deltaFood += gained;
                outcome.itemsAdded.push_back("Food +" + to_string(gained));
            } else if (reward == 1) {
                int gained = rand()%3 + 1;
                water += gained;
                outcome.deltaWater += gained;
                outcome.itemsAdded.push_back("Water +" + to_string(gained));
            } else {
                health = min(100, health + 30);
                outcome.deltaHealth += +30;
                outcome.itemsAdded.push_back("Healing Potion (+30 health)");
            }
        }
        outcome.resultText = "You found treasure!";
    }

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10);
    resultScreen.Render();
}

// ========== 陷阱 ==========
void trapEncounter(int difficulty, int &health, int &food, int &water) {
    vector<string> options = {"Try escape", "Cut free", "Wait for help"};
    SChoiceMenu menu(options, 10, 5);
    menu.Render();
    int choiceIndex = menu.WaitForSelection();

    EventOutcome outcome;
    outcome.eventName = "Trap";
    outcome.choiceMade = options[choiceIndex];

    int roll = rand()%100 + 1;

    if (choiceIndex == 0) { // Try escape
        if (roll <= 70) {
            outcome.resultText = "You escaped safely.";
        } else {
            health -= 15;
            outcome.resultText = "Failed escape!";
            outcome.deltaHealth = -15;
        }
    } else if (choiceIndex == 1) { // Cut free
        if (food > 0) {
            food -= 1;
            outcome.resultText = "You cut yourself free.";
            outcome.deltaFood = -1;
            outcome.itemsRemoved.push_back("Food");
        } else {
            outcome.resultText = "No food to sacrifice!";
        }
    } else if (choiceIndex == 2) { // Wait
        if (food > 0) { food -= 1; outcome.deltaFood = -1; }
        if (water > 0) { water -= 1; outcome.deltaWater = -1; }
        outcome.resultText = "You waited for help. Escaped next day.";
    }

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10);
    resultScreen.Render();
}

// ========== 泉水 ==========
void waterSpringEncounter(int difficulty, int &health, int &food, int &water) {
    EventOutcome outcome;
    int waterGain = 2 + rand() % 3;   // 2,3,4
    water += waterGain;
    if (rand() % 100 < 50) {
        int heal = 10;
        health += heal;
    }
    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}

// ========== 浆果丛 ==========
void berryBushEncounter(int difficulty, int &health, int &food, int &water) {
    int foodGain = 1 + rand() % 3;   // 1,2,3
    food += foodGain;
    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}

// ========== 天气事件 ==========
void weatherEncounter(int difficulty, int &health, int &food, int &water) {
    int weatherType = rand() % 4; // 0: Rain, 1: Heat wave, 2: Cold snap, 3: Mild
    switch (weatherType) {
        case 0: { // Rain
            int waterGain = 1 + rand() % 2;
            water += waterGain;
            break;
        }
        case 1: { // Heat wave
            int waterLoss = 2;
            water -= waterLoss;
            break;
        }
        case 2: { // Cold snap
            int damage = 5;
            health -= damage;
            break;
        }
        case 3: { // Mild
            break;
        }
    }

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}

// ========== 空事件 ==========
void emptyEncounter(int difficulty, int &health, int &food, int &water) {
    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}
