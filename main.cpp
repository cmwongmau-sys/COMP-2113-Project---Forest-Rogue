// Main Program

#include <iostream> 
#include <string>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "event_generation.h"
#include "file_switch.h"
#include "random.h"
#include "Slate/Sprites/SpritesCore.h"
#include "../../../Header/Slate/Widgets/GameScreens.h"
#include "../../../Header/Slate/Widgets/WidgetsCore.h"
#include "simple_display.h"
using namespace std;

int main() {
    
    // Call the function to print set up screen
    SPlayerSetupScreen setupScreen(0,0);
    SPlayerSetupInfo info = setupScreen.Run();

    // Read the user's input of his name, path and diffculty mode
     // 0/1/2 for easy/medium/hard
    string name = info.PlayerName, path = info.SaveFilePath;
    int mode = info.Difficulty;

    if (!path.empty()) {
        vector<ScoreEntry> scoreboard;
        
        // load the data into the scoreboard
        loadScoreboard(scoreboard, path);
    }

    // Call the function to print start screen


    // Enter the game and go through 6 zones
    bool win = true;
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
                bearEncounter(mode, health, food, water);
                break;
            case 2:     // Treasure
                // call function for treasure;
                treasureEncounter(mode, health, food, water);
                break;
            case 3:     //Trap
                // call function for trap;
                trap(mode, health, food, water);
                break;
            case 4:     // Water spring
                // call function for water spring;
                waterSpringEncounter(mode, health, food, water);
                break;
            case 5:     // Berry rush
                // call function for berry rush;
                berryBushEncounter(mode, health, food, water);
                break;
            case 6:     // Weather
                // call function for weather;
                weatherEncounter(mode, health, food, water);
                break;
            case 7:     // Peaceful day (Nothing happens)
                emptyEncounter(mode, health, food, water);
                break;
        }

        
        // Track changes and check survival
        if (health < 0 || food >= -3 || water >= -3)
            // Lose the game
            win = false;
            break;

        // Daily consumption
        food--;
        water--;

        // Track changes and check survival
        if (health > 0 && food >= -3 && water >= -3)
            // call function to print screen to show daily consumption
            // status includes health, food, water
            SDailySummaryScreen dailySummaryScreen(zone, zone, 6, health, 100, 
                                            food, 10, water, 10, 0, 0);
            dailySummaryScreen.Render();

        else 
            // Lose the game
            win = false;
            break;


    }

    // Calculate the score of the player including the bonus from excess food and water
    int score;
    score += (health * 2) + (food * 5) + (water * 5) + (zone * 100);

    // Display victory screen if win 
    if (win) {
        SVictoryScreen victoryScreen(zone, health, food, water, score, 0,0);
        victoryScreen.Render();
    }

    // Display death screen if lose
    else {
        SDeathScreen deathScreen(zone, heath, food, water, score, 0, 0);
        deathScreen.Render();
    }


    // Display scoreboard
    cout << "\033[2J\033[1;1H";
    displayTop10(scoreboard);


    // File output
    // Get current time
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
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

    string winLose = win ? "Won" : "Lose";
    ScoreEntey player = {name, mode, score, food, water, zone, winLose, dateTimeData};
    scoreboard.push_back(player);

    saveScoreboard(scoreboard, filename);

    return 0;
}