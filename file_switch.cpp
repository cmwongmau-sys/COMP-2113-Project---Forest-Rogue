#include "file_switch.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

// Save one game result to scoreboard
void saveScoreboard(vector<ScoreEntry>& scoreboard, string file) {
    ofstream outFile(file, ios::app);  // append mode
    
    if (outFile.is_open()) {
        outFile << entry.name << "|" 
                << entry.difficulty << "|" 
                << entry.finalScore << "|" 
                << entry.excessFood << "|" 
                << entry.excessWater << "|" 
                << entry.zonesCompleted << "|" 
                << entry.dateTime << endl;
        outFile.close();
    }
}

// Load all scoreboard data
void loadScoreboard(vector<ScoreEntry>& scoreboard, string file) {
    scoreboard.clear();
    ifstream inFile(file);
    string line;
    
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, '|')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 7) {
            ScoreEntry s;
            s.name = tokens[0];
            s.difficulty = stoi(tokens[1]);
            s.finalScore = stoi(tokens[2]);
            s.excessFood = stoi(tokens[3]);
            s.excessWater = stoi(tokens[4]);
            s.zonesCompleted = stoi(tokens[5]);
            s.dateTime = tokens[6];
            scoreboard.push_back(s);
        }
    }
    inFile.close();
}

// Display Top 10 Scoreboard (sorted by finalScore descending)
void displayTop10(const vector<ScoreEntry>& scoreboard) {
    vector<ScoreEntry> sorted = scoreboard;
    
    sort(sorted.begin(), sorted.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.finalScore > b.finalScore;
    });
    
    cout << "\n========== TOP 10 SCOREBOARD ==========\n";
    cout << "Rank | Name\t| Diff | Score | Food | Water | Zones | Date\n";
    cout << "----------------------------------------------------\n";
    
    int rank = 1;
    for (int i = 0; i < min(10, (int)sorted.size()); i++) {
        cout << rank++ << "    | " 
             << sorted[i].name << "\t| " 
             << sorted[i].difficulty << "    | " 
             << sorted[i].finalScore << "   | " 
             << sorted[i].excessFood << "    | " 
             << sorted[i].excessWater << "     | " 
             << sorted[i].zonesCompleted << "     | " 
             << sorted[i].dateTime << endl;
    }
    cout << "========================================\n";
}
