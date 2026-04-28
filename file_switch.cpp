#include "file_switch.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <ctime>

using namespace std;

// Convert difficulty number to readable string
string getDifficultyString(int diff) {
    if (diff == 0) return "Easy";
    if (diff == 1) return "Medium";
    if (diff == 2) return "Hard";
    return "Unknown";
}

// Convert string ("Easy", "0", "Medium", etc.) back to number
int getDifficultyFromString(const string& str) {
    if (str == "Easy" || str == "0") return 0;
    if (str == "Medium" || str == "1") return 1;
    if (str == "Hard" || str == "2") return 2;
    return 0; // default to Easy if unknown
}

// ==================== saveScoreboard ====================
// Changed: Now uses getDifficultyString() instead of printing the number
void saveScoreboard(vector<ScoreEntry>& scoreboard, string file) {
    if (scoreboard.empty()) {
        cout << "Warning: Scoreboard is empty. Nothing to save." << endl;
        return;
    }

    sort(scoreboard.begin(), scoreboard.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.finalScore > b.finalScore;
    });

    ofstream outFile(file);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open " << file << " for writing!" << endl;
        return;
    }

    time_t now = time(0);
    char dt[30];
    strftime(dt, sizeof(dt), "%Y-%m-%d %H:%M:%S", localtime(&now));

    outFile << "=== FOREST ROGUE SCOREBOARD - Updated: " << dt << " ===\n\n";

    outFile << left 
            << setw(15) << "Name"
            << setw(12) << "Difficulty"
            << setw(10) << "Score"
            << setw(12) << "Food Left"
            << setw(12) << "Water Left"
            << setw(8)  << "Zones"
            << setw(8)  << "Result"
            << setw(20) << "Date & Time" << endl;

    outFile << string(92, '-') << endl;

    for (const auto& entry : scoreboard) {
        outFile << left
                << setw(15) << entry.name
                << setw(12) << getDifficultyString(entry.difficulty)   
                << setw(10) << entry.finalScore
                << setw(12) << entry.excessFood
                << setw(12) << entry.excessWater
                << setw(8)  << entry.zonesCompleted
                << setw(8)  << entry.result
                << setw(20) << entry.dateTime << endl;
    }

    outFile.close();
    cout << "Scoreboard saved successfully (" << scoreboard.size() << " entries)\n";
}

// ==================== loadScoreboard ====================
// Changed: Now uses getDifficultyFromString() to handle both numbers and text
void loadScoreboard(vector<ScoreEntry>& scoreboard, string file) {
    scoreboard.clear();
    
    ifstream inFile(file);
    if (!inFile.is_open()) {
        cout << "No scoreboard file found: " << file << endl;
        cout << "Starting with empty scoreboard." << endl;
        return;
    }

    string line;
    int lineNumber = 0;
    int validCount = 0;
    bool headerPassed = false;

    while (getline(inFile, line)) {
        lineNumber++;
        
        if (line.empty() || line.find_first_not_of(" \t") == string::npos) continue;

        if (line.find("=== FOREST ROGUE SCOREBOARD") != string::npos ||
            line.find("Name") != string::npos && line.find("Difficulty") != string::npos ||
            line.find("-----") != string::npos) {
            headerPassed = true;
            continue;
        }

        if (!headerPassed) continue;

        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, '|')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 8) continue;

        try {
            ScoreEntry s;
            s.name           = tokens[0];
            s.difficulty     = getDifficultyFromString(tokens[1]);  
            s.finalScore     = stoi(tokens[2]);
            s.excessFood     = stoi(tokens[3]);
            s.excessWater    = stoi(tokens[4]);
            s.zonesCompleted = stoi(tokens[5]);
            s.result         = tokens[6];
            s.dateTime       = tokens[7];

            scoreboard.push_back(s);
            validCount++;

        } catch (...) {
            cerr << "Warning: Invalid data on line " << lineNumber 
                 << " in " << file << ". Skipping." << endl;
        }
    }

    inFile.close();
    cout << "Successfully loaded " << validCount << " entries from " << file << endl;
}

// ==================== displayTop10 ====================
// Changed: Now shows "Easy/Medium/Hard" instead of numbers
void displayTop10(const vector<ScoreEntry>& scoreboard) {
    if (scoreboard.empty()) {
        cout << "No scores to display yet.\n";
        return;
    }

    vector<ScoreEntry> sorted = scoreboard;
    sort(sorted.begin(), sorted.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.finalScore > b.finalScore;
    });

    cout << "\n========== TOP 10 FOREST ROGUE SCOREBOARD ==========\n";
    
    cout << left 
         << setw(4)  << "Rank"
         << setw(15) << "Name"
         << setw(10) << "Difficulty"
         << setw(8)  << "Score"
         << setw(10) << "Food"
         << setw(10) << "Water"
         << setw(7)  << "Zones"
         << setw(7)  << "Result"
         << setw(20) << "Date" << endl;

    cout << string(90, '-') << endl;

    int rank = 1;
    for (int i = 0; i < min(10, (int)sorted.size()); ++i) {
        cout << left
             << setw(4)  << rank++
             << setw(15) << sorted[i].name
             << setw(10) << getDifficultyString(sorted[i].difficulty)  
             << setw(8)  << sorted[i].finalScore
             << setw(10) << sorted[i].excessFood
             << setw(10) << sorted[i].excessWater
             << setw(7)  << sorted[i].zonesCompleted
             << setw(7)  << sorted[i].result
             << setw(20) << sorted[i].dateTime << endl;
    }
    cout << "==================================================\n";
}
