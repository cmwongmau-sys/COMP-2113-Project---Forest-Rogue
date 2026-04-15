// Main Program

#include <iostream> 
#include <string>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "file_switch.h"
using namespace std;

int main() {

    // Call the function to print welcome screen

    // Read the user's input of his name
    string name;
    getline(cin, name);

    // Ask the use if he have files to input (Y/N)


    // Read the user's input of his answer and file
    string ans, file;
    cin >> ans;

    if (ans == "Y") {
        // Get the file path
        getline(cin, file);
        vector<ScoreEntry> scoreboard;
        
        // load the data into the scoreboard
        loadScoreboard(scoreboard, file);
    }

    // Read the user's input for the difficulty level
    // 0/1/2 for easy/medium/hard
    int mode;
    cin >> mode;

    // Ask the user if he has any file to input
    char ans;
    cout << "Do you have any player statistics to input? (Y/N)" << endl;
    cin >> ans;

    string path;
    if (ans == 'Y') {
        cout << "Please give the path of the file for player statistics: ";
        cin >> path;
        cout << endl;
    }

    // Call the function to print start screen


    // Enter the game and go through 6 zones
    int zone = 1;
    for (; zone < 7; zone ++) {

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
        int event = randomEvent(mode);

        switch (event) {
            case 1:     // Bear attack
                // call function for bear attack;
                break;
            case 2:     // Treasure
                // call function for treasure;
                break;
            case 3:     //Trap
                // call function for trap;
                break;
            case 4:     // Water spring
                // call function for water spring;
                break;
            case 5:     // Berry rush
                // call function for berry rush;
                break;
            case 6:     // Weather
                // call function for weather;
                break;
            case 7:     // Peaceful day (Nothing happens)
                break;
        }

        
        // Track changes and check survival
        if (health > 0 && food >= -3 && water >= -3)
            // call function to prnt screen to show changes in the status
            // status includes health, food, water

        else 
            // display death screen

        // Daily consumption
        food--;
        water--;

        // Track changes and check survival
        if (health > 0 && food >= -3 && water >= -3)
            // call function to prnt screen to show daily consumption
            // status includes health, food, water

        else 
            // display death screen


    }

    // Display victory screen
    // Calculate the score of the player including the bonus from excess food and water
    int score;

    // Display scoreboard

    // File output
    // Get current time
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    
    // Convert to local time
    tm* localTime = localtime(&currentTime);

    // Datetime Format 1: For filename
    stringstream ss_filename;
    ss_filename << put_time(localTime, "%Y-%m-%d-%H%M%S");
    string dateTimeFilename = ss_filename.str();
    string filename = "scoreboard_" + dateTimeFilename + ".txt"

    // Datetime Format 2: For player data
    stringstream ss_data;
    ss_data << put_time(localTime, "%Y-%m-%d %H:%M:%S");
    string dateTimeData = ss_data.str();
    ScoreEntey player = {name, mode, score, food, water, zone, dateTimeData};

    saveScoreboard(scoreboard, filename);

    return 0;
}