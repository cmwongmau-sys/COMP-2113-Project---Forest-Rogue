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
    std::array<int, 8> upperBound = {20, 40, 50, 65, 80, 90, 100};

    switch (mode) {
        case 0:  // Easy
            upperBound = {20, 40, 50, 65, 80, 90, 100};
            break;
        case 1:  // Medium
            upperBound = {25, 40, 55, 65, 75, 90, 100};
            break;
        case 2:  // Hard
            upperBound = {30, 40, 60, 65, 70, 90, 100};
            break;
    }

    // Generate the random number
    srand(time(0));
    int randomNum = rand() % 100 + 1;

    // Find the corresponding random event
    for (int i = 0; i < 8; i++) {
        if (randomNum < upperBound[i])
            return i;
    }
}
