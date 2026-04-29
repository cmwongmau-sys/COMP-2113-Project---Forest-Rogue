#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "random.h"
#include "../../../Header/Slate/Widgets/GameScreens.h"
#include "../../../Header/Slate/Widgets/WidgetsCore.h"
#include "simple_display.h"
using namespace std;

namespace encounter {
// ========== Bear Attack ==========
void bearEncounter(int difficulty, int &health, int &food, int &water) {
    string banner = "Bear Attack";
    vector<string> content = {"A snarling bear lunges from the shadows - right in your path!"};
    DrawStaticFrame(banner, content);

    vector<string> options = {"Fight", "Flee"};
    SChoiceMenu menu(options, 10, 13);
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
            outcome.deltaFood = 2;
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

// ========== Treasure ==========
void treasureEncounter(int difficulty, int &health, int &food, int &water) {
    string banner = "Treasure Encounter";
    vector<string> content = {"You stumble upon a weathered chest bursting with gold and gems!"};
    DrawStaticFrame(banner, content);

    vector<string> options = {"Take items", "Leave it"};
    SChoiceMenu menu(options, 10, 13);
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
                outcome.deltaFood = gained;
            } else if (reward == 1) {
                int gained = rand()%3 + 1;
                water += gained;
                outcome.deltaWater = gained;
            } else {
               health += 30;
               outcome.deltaHealth = 30;
            }
        }
        outcome.resultText = "You found treasure!";
    }
    else {
        health += 10;
        outcome.deltaHealth = 10;
        outcome.resultText = "You leave the treasure aside and proceed forward.";
    }

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}

// ========== Trap ==========
void trapEncounter(int difficulty, int &health, int &food, int &water) {
    string banner = "Trap Encounter";
    vector<string> content = {"A sharp snap - you've triggered a hidden trap!"};
    DrawStaticFrame(banner, content);

    vector<string> options = {"Try escape", "Cut free", "Wait for help"};
    SChoiceMenu menu(options, 10, 13);
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
            food -= 1;
            outcome.resultText = "You cut yourself free.";
            outcome.deltaFood = -1;
    } else if (choiceIndex == 2) { // Wait
        food -= 1;
        water -= 1; 
        outcome.deltaFood = -1; 
        outcome.deltaWater = -1;
        outcome.resultText = "You waited for help. Escaped next day.";
    }

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}

// ========== Water Spring ==========
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
    outcome.resultText = "You drank from the spring.";

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}

// ========== Berru Bush ==========
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

// ========== Weather ==========
void weatherEncounter(int difficulty, int &health, int &food, int &water) {
    int weatherType = rand() % 3; // 0: Rain, 1: Heat wave, 2: Cold snap
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
            outcome.deltaHealth = -damage;
            outcome.resultText = "Cold snap damaged your health.";
            break;
        }
    }

    SEventResultScreen resultScreen(outcome, health, 100, food, 10, water, 10, 0, 0);
    resultScreen.Render();
}

// ========== Empty ==========
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
}
