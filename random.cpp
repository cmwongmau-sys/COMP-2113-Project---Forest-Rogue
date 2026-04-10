#include <iostream>
#include <cstdlib>  
#include <ctime> 
#include "random.h"
using namespace std;


// choice: 1 = Fight, 2 = Flee
void wildAnimalEncounter(int choice, int difficulty, int &health, int &food, int &water) {
    int roll = rand() % 100 + 1;

    if (choice == 1) {
        if (roll <= 50) { 
            int damage = (difficulty == 1) ? (5 + rand()%6) : 
                         (difficulty == 2) ? (10 + rand()%6) : 
                                              (15 + rand()%6);
            health -= damage;
            food += 2; 
            cout << "You fought bravely! Lost " << damage << " health, gained 2 food.\n";
        } else {
            int damage = (difficulty == 1) ? (15 + rand()%11) : 
                         (difficulty == 2) ? (15 + rand()%11) : 
                                              (20 + rand()%6);
            health -= damage;
            cout << "You lost the fight! Lost " << damage << " health.\n";
        }
    } else if (choice == 2) { 
        if (roll <= 50) {
            cout << "You fled successfully. No damage.\n";
        } else {
            int damage = 10 + rand()%11;
            health -= damage;
            cout << "Failed to flee! Lost " << damage << " health.\n";
        }
    }
}

// choice: 1 = Take items
void treasureEncounter(int choice, int difficulty, int &health, int &food, int &water) {
    if (choice == 1) {
        int items = rand()%3 + 1;
        for (int i = 0; i < items; i++) {
            int reward = rand()%3; 
            if (reward == 0) {
                int gained = rand()%3 + 1;
                food += gained;
                cout << "Found " << gained << " food.\n";
            } else if (reward == 1) {
                int gained = rand()%3 + 1;
                water += gained;
                cout << "Found " << gained << " water.\n";
            } else {
                health = min(100, health + 30); 
                cout << "Found a healing potion! Restored 30 health.\n";
            }
        }
    }
}

// choice: 1 = Try escape, 2 = Cut free, 3 = Wait for help
void trapEncounter(int choice, int difficulty, int &health, int &food, int &water) {
    int roll = rand()%100 + 1;

    if (choice == 1) { // Try escape
        if (roll <= 70) {
            cout << "You escaped the trap safely.\n";
        } else {
            health -= 15;
            cout << "Failed to escape! Lost 15 health.\n";
        }
    } else if (choice == 2) { // Cut free
        if (food > 0) {
            food -= 1;
            cout << "You cut yourself free. Lost 1 food.\n";
        } else {
            cout << "No food to sacrifice! You remain trapped.\n";
        }
    } else if (choice == 3) { // Wait for help
        if (food > 0) food -= 1;
        if (water > 0) water -= 1;
        cout << "You waited for help. Lost 1 food and 1 water.\n";
        cout << "Escaped next day automatically.\n";
    }
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
