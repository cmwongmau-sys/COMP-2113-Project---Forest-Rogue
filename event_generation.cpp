// Random Event Generation Function

#include <iostream> 
#include <string>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
#include "event_generation.h"
using namespace std;

// Generate the random event based on the probability of difficulty modes
int randomEvent(int mode) {

    // Upper bound array for 7 events , ignore index 0
    int upperBound[8];

    switch (mode) {
        case 0: {  // Easy
            int _upperBoundEasy[8] = { 20, 40, 50, 65, 80, 90, 100 };
            memcpy(upperBound, _upperBoundEasy, 8);
            break;
        }
        case 1: {  // Medium
            int _upperBoundMedium[8] = { 25, 40, 55, 65, 75, 90, 100 };
            memcpy(upperBound, _upperBoundMedium, 8);
            break;
        }
        case 2: {  // Hard
            int _upperBoundHard[8] = { 30, 40, 60, 65, 70, 90, 100 };
            memcpy(upperBound, _upperBoundHard, 8);
            break;
        }
        default: {
            throw exception("Error: mode must be 0(easy), 1(medium) or 2(hard)");
        }
    }

    // Generate the random number
    srand((int)time(0));
    int randomNum = rand() % 100 + 1;

    // Find the corresponding random event
    for (int i = 0; i < 8; i++) {
        if (randomNum < upperBound[i])
            return i;
    }
    
    throw exception("Error: no valid events found");
}