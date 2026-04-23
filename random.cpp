#include <iostream>   // 临时，用于事件描述，后续应替换为屏幕函数
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <string>
#include "random.h"
#include "Slate/Widgets/GameScreens.h"
#include "Slate/Widgets/WidgetsCore.h"
using namespace std;

// ========== 野生生物 ==========
void bearEncounter(int difficulty, int &health, int &food, int &water) {
    string banner = "Bear Attack";
    vector<string> content = {"A snarling bear lunges from the shadows - right in your path!"};
    DrawStaticFrame(banner, content);

    vector<string> options = {"Fight", "Flee"};
    SChoiceMenu menu(options, 50, 5);
    menu.Render();
    int choiceIndex = menu.WaitForSelection();

    EventOutcome outcome;
    outcome.eventName = "Bear Attack";
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

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}

// ========== 宝藏 ==========
void treasureEncounter(int difficulty, int &health, int &food, int &water) {
    string banner = "Treasure Encounter";
    vector<string> content = {"You stumble upon a weathered chest bursting with gold and gems!"};
    DrawStaticFrame(banner, content);

    vector<string> options = {"Take items"};
    SChoiceMenu menu(options, 50, 5);
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

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}

// ========== 陷阱 ==========
void trapEncounter(int difficulty, int &health, int &food, int &water) {
    string banner = "Trap Encounter";
    vector<string> content = {"A sharp snap - you've triggered a hidden trap!"};
    DrawStaticFrame(banner, content);

    vector<string> options = {"Try escape", "Cut free", "Wait for help"};
    SChoiceMenu menu(options, 50, 5);
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

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}

// ========== 泉水 ==========
void waterSpringEncounter(int difficulty, int &health, int &food, int &water) {
    string banner = "Water Spring Encounter";
    vector<string> content = {"A crystal-clear spring bubbles up from the mossy rocks, cool and inviting."};
    DrawStaticFrame(banner, content);

    EventOutcome outcome;
    outcome.eventName = "Water Spring";
    outcome.choiceMade = "None";

    int waterGain = 2 + rand() % 3;   // 2,3,4
    water += waterGain;
    outcome.deltaWater = waterGain;
    outcome.resultText = "You drank from the spring and gained water.";

    if (rand() % 100 < 50) {
        int heal = 10;
        health += heal;
        if (health > 100) health = 100;
        outcome.deltaHealth = heal;
        outcome.resultText += " The magic water also restored health!";
    }

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}

// ========== 浆果丛 ==========
void berryBushEncounter(int difficulty, int &health, int &food, int &water) {
    string banner = "Berry Bush Encounter";
    vector<string> content = {"A thicket of ripe, juicy berries sways in the breeze - time to feast!"};
    DrawStaticFrame(banner, content);

    EventOutcome outcome;
    outcome.eventName = "Berry Bush";
    outcome.choiceMade = "None";

    int foodGain = 1 + rand() % 3;   // 1,2,3
    food += foodGain;
    outcome.deltaFood = foodGain;
    outcome.resultText = "You ate the sweet berries and gained food.";

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}

// ========== 天气事件 ==========
void weatherEncounter(int difficulty, int &health, int &food, int &water) {
    int weatherType = rand() % 3; // 0: Rain, 1: Heat wave, 2: Cold snap (原设计有4种，这里只用了3种)
    EventOutcome outcome;
    outcome.eventName = "Weather Event";
    outcome.choiceMade = "None";

    switch (weatherType) {
        case 0: { // Rain
            string banner = "Heavy Rain";
            vector<string> content = {"Torrential rain fills your canteen - you drink deeply"};
            DrawStaticFrame(banner, content);
            int waterGain = 1 + rand() % 2;
            water += waterGain;
            outcome.deltaWater = waterGain;
            outcome.resultText = "Rain provided fresh water.";
            break;
        }
        case 1: { // Heat wave
            string banner = "Heat Wave";
            vector<string> content = {"Scorching sun beats down, sweat drains your water supply."};
            DrawStaticFrame(banner, content);
            int waterLoss = 2;
            water -= waterLoss;
            if (water < 0) water = 0;
            outcome.deltaWater = -waterLoss;
            outcome.resultText = "Heat wave caused dehydration!";
            break;
        }
        case 2: { // Cold snap
            string banner = "Cold Snap";
            vector<string> content = {"Bitter frost numbs your bones, sapping your health."};
            DrawStaticFrame(banner, content);
            int damage = 5;
            health -= damage;
            if (health < 0) health = 0;
            outcome.deltaHealth = -damage;
            outcome.resultText = "Cold snap damaged your health.";
            break;
        }
    }

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}

// ========== 空事件 ==========
void emptyEncounter(int difficulty, int &health, int &food, int &water) {
    string banner = "Quiet Day";
    vector<string> content = {"You wander through the forest and nothing happens."};
    DrawStaticFrame(banner, content);

    EventOutcome outcome;
    outcome.eventName = "Empty";
    outcome.choiceMade = "None";
    outcome.resultText = "Nothing interesting happened today.";

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}
