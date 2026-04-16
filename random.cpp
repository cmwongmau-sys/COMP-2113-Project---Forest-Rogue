#include <iostream>
#include <cstdlib>  
#include <ctime> 
#include <algorithm>
#include "random.h"
#include "GameScreens.h"
using namespace std;


// choice: 1 = Fight, 2 = Flee
EventOutcome wildAnimalEncounter(int difficulty, int &health, int &food, int &water) {
    EventOutcome outcome;
    outcome.eventName = "Wild Animal";

    int choice;
    cout << "choice: 1 = Fight, 2 = Flee" << endl;
    cin >> choice;
    outcome.choiceMade = (choice == 1) ? "Fight" : "Flee";

    int roll = rand() % 100 + 1;

    if (choice == 1) {
        if (roll <= 50) {
            int damage = (difficulty == 1) ? (5 + rand()%6) :
                         (difficulty == 2) ? (10 + rand()%6) :
                                              (15 + rand()%6);
            health -= damage;
            food += 2;
            outcome.resultText = "You fought bravely!";
            outcome.deltaHealth = -damage;
            outcome.deltaFood = +2;
        } else {
            int damage = (difficulty == 1) ? (15 + rand()%11) :
                         (difficulty == 2) ? (15 + rand()%11) :
                                              (20 + rand()%6);
            health -= damage;
            outcome.resultText = "You lost the fight!";
            outcome.deltaHealth = -damage;
        }
    } else if (choice == 2) {
        if (roll <= 50) {
            outcome.resultText = "You fled successfully.";
        } else {
            int damage = 10 + rand()%11;
            health -= damage;
            outcome.resultText = "Failed to flee!";
            outcome.deltaHealth = -damage;
        }
    }
    return outcome;
}

EventOutcome treasureEncounter(int difficulty, int &health, int &food, int &water) {
    EventOutcome outcome;
    outcome.eventName = "Treasure";

    int choice;
    cout << "choice: 1 = Take items" << endl;
    cin >> choice;
    outcome.choiceMade = "Take items";

    if (choice == 1) {
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
    return outcome;
}

EventOutcome trapEncounter(int difficulty, int &health, int &food, int &water) {
    EventOutcome outcome;
    outcome.eventName = "Trap";

    int choice;
    cout << "choice: 1 = Try escape, 2 = Cut free, 3 = Wait for help" << endl;
    cin >> choice;
    outcome.choiceMade = (choice == 1) ? "Try escape" :
                         (choice == 2) ? "Cut free" : "Wait for help";

    int roll = rand()%100 + 1;

    if (choice == 1) {
        if (roll <= 70) {
            outcome.resultText = "You escaped safely.";
        } else {
            health -= 15;
            outcome.resultText = "Failed escape!";
            outcome.deltaHealth = -15;
        }
    } else if (choice == 2) {
        if (food > 0) {
            food -= 1;
            outcome.resultText = "You cut yourself free.";
            outcome.deltaFood = -1;
            outcome.itemsRemoved.push_back("Food");
        } else {
            outcome.resultText = "No food to sacrifice!";
        }
    } else if (choice == 3) {
        if (food > 0) { food -= 1; outcome.deltaFood = -1; }
        if (water > 0) { water -= 1; outcome.deltaWater = -1; }
        outcome.resultText = "You waited for help. Escaped next day.";
    }
    return outcome;
}

void waterSpringEncounter(int difficulty, int &health, int &food, int &water){
    int waterGain = 2 + rand() % 3;   // 2,3,4
    water += waterGain;
    cout << "You found a crystal-clear spring! Gained " << waterGain << " water.\n";
    if (rand() % 100 < 50) {
        int heal = 10;
        health += heal;
        if (health > 100) health = 100;
        cout << "The spring's magic water also restored " << heal << " health.\n";
    }
}
void berryBushEncounter(int difficulty, int &health, int &food, int &water){
    int foodGain = 1 + rand() % 3;   // 1,2,3
    food += foodGain;
    cout << "You found a bush full of berries! Gained " << foodGain << " food.\n";
}
void weatherEncounter(int difficulty, int &health, int &food, int &water){
    int weath=rand()%4; // 0: Rain, 1: Heat wave, 2: Cold snap, 3: Mild
    switch(weather){
        case 0: // Rain
            {
                int waterGain = 1 + rand() % 2; // 1 or 2
                water += waterGain;
                cout << "It started raining. You collected " << waterGain << " water.\n";
            }
            break;
        case 1:
            {
                water -=2;
                if(water<0) water=0;
                cout<< "A heat wave strikes! You lost 2 water.\n"
            }
            break;
        case 2:
            {
                health-=5;
                if (health <=0) health=0;
                cout<<"A sudden cold snap! You lost 5 health.\n";
            }
            break;
        case 3:
            cout<<"The weather is mild today. Nothing happens.\n";
            break;
    }
}
void empty(int difficulty, int &health, int &food, int &water){
    cout << "Today was quiet. Nothing special happened.\n";
}
