// Main Program

#include <iostream> 
#include <string>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
using namespace std;

int main() {

    // Call the function to print screen

    // Read the user's input of his name
    string name;
    getline(cin, name);

    // Read the user's input for the difficulty level
    // 0/1/2 for easy/medium/hard
    int mode;
    cin >> mode;

    // Call the function to print screen


    // Enter the game and go through 6 zones
    for (int zone = 1; zone < 7; zone ++) {

        int health = 100, food, water;

        switch (mode) {
            case 0:     // Easy mode
                food = 5;
                water = 3;
                break;
            case 1:     // Medium mode
                food = 3;
                water = 2;
                break;
            case 3:     // Hard mode
                food = 2;
                water = 1;
                break;
            default:    // Default to be easy mode
                food = 5;
                water = 3;
                break;
        }

        // Print screen to display current status

        // Encounter random events
        int Event = randomEvent(mode);


    }



    return 0;
}