#ifndef FILE_SWITCH_H
#define FILE_SWITCH_H

#include <string>
#include <vector>
using namespace std;

//scoreboard column
struct ScoreEntry 
    string name;
    int difficulty;
    int finalScore;
    int excessFood;
    int excessWater;
    int zonesCompleted;
    string dateTime;
};

// Function declarations
void saveScore(ScoreEntry entry);
void loadScoreboard(vector<ScoreEntry>& scoreboard);
void displayTop10(const vector<ScoreEntry>& scoreboard);

#endif
