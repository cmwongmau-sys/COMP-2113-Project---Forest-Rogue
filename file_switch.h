#ifndef FILE_SWITCH_H
#define FILE_SWITCH_H

#include <string>
#include <vector>
using namespace std;

struct ScoreEntry {
    string name;
    int difficulty;
    int finalScore;
    int excessFood;
    int excessWater;
    int zonesCompleted;
    string result;      // NEW: showing "Won" or "Lose"
    string dateTime;
};

// Function declarations
void saveScoreboard(vector<ScoreEntry>& scoreboard, string file);
void loadScoreboard(vector<ScoreEntry>& scoreboard, string file);
void displayTop10(const vector<ScoreEntry>& scoreboard);
#endif
