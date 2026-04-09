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
