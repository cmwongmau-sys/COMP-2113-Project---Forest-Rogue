// Random Event Generation Function

#include <iostream> 
#include <string>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
#include <array>
#include "event_generation.h"
using namespace std;

// Generate the random event based on the probability of difficulty modes
// Input: difficulty modes
// Output: random event
int randomEvent(int mode) {

    // Generate the random number
    srand(time(0));
    int randomNum = rand() % 100 + 1;

    switch (mode) {
        case 0: { // Easy
            std::array<int, 8> upperBound = {-1, 20, 40, 50, 65, 80, 90, 100};
            // Find the corresponding random event
            for (int i = 1; i < 8; i++) {
                if (randomNum <= upperBound[i])
                    return i;
            }
            break;
        }
        case 1: { // Medium
            std::array<int, 8> upperBound = std::array<int, 8>{-1, 25, 40, 55, 65, 75, 90, 100};
            // Find the corresponding random event
            for (int i = 1; i < 8; i++) {
                if (randomNum <= upperBound[i])
                    return i;
            }
            break;
        }
        case 2: { // Hard
            std::array<int, 8> upperBound = std::array<int, 8>{-1, 30, 40, 60, 65, 70, 90, 100};
            // Find the corresponding random event
            for (int i = 1; i < 8; i++) {
                if (randomNum <= upperBound[i])
                    return i;
            }
            break;
        }
    }

    return 7;
}
