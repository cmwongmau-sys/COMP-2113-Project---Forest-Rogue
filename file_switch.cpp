#include "file_switch.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;

// Save whole result to scoreboard
void saveScoreboard(vector<ScoreEntry>& scoreboard, string file) {
    // clear screen
    cout << "\033[2J\033[3J\033[1;1H";

    if (scoreboard.empty()) {
        cout << "Warning: Scoreboard is empty. Nothing to save." << endl;
        return;
    }

    // Sort by FinalScore (highest first)
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

    outFile << "=== SURVIVAL SCOREBOARD - Updated: " << dt << " ===\n\n";

    outFile << left 
            << setw(15) << "Name"
            << setw(12) << "Difficulty"
            << setw(10) << "Score"
            << setw(12) << "Food Left"
            << setw(12) << "Water Left"
            << setw(8)  << "Zones"
            << setw(20) << "Date & Time" << endl;

    outFile << string(85, '-') << endl;   // Separator line

    // Data Rows
    for (const auto& entry : scoreboard) {
        outFile << left
                << setw(15) << entry.name
                << setw(12) << entry.difficulty
                << setw(10) << entry.finalScore
                << setw(12) << entry.excessFood
                << setw(12) << entry.excessWater
                << setw(8)  << entry.zonesCompleted
                << setw(20) << entry.dateTime << endl;
    }

    outFile.close();
    
    cout << "Scoreboard saved successfully (" << scoreboard.size() 
         << " entries) with neat formatting.\n";
    
    cin.get();
}

// Load all scoreboard data
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

        // Skip header lines
        if (line.find("=== SURVIVAL SCOREBOARD") != string::npos ||
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

        // Now expecting 8 columns (added "result")
        if (tokens.size() != 8) {
            cerr << "Warning: Skipping corrupted line " << lineNumber << " in " << file << endl;
            continue;
        }

        try {
            ScoreEntry s;
            s.name           = tokens[0];
            s.difficulty     = stoi(tokens[1]);
            s.finalScore     = stoi(tokens[2]);
            s.excessFood     = stoi(tokens[3]);
            s.excessWater    = stoi(tokens[4]);
            s.zonesCompleted = stoi(tokens[5]);
            s.result         = tokens[6];           // NEW
            s.dateTime       = tokens[7];

            // Validation
            if (s.difficulty < 0 || s.difficulty > 2 || 
                s.zonesCompleted < 0 || s.zonesCompleted > 6) {
                throw invalid_argument("Invalid value");
            }

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

// Display Top 10 Scoreboard (sorted by finalScore descending)
void displayTop10(const vector<ScoreEntry>& scoreboard) {
    cout << "\033[2J\033[3J\033[1;1H";

    if (scoreboard.empty()) {
        cout << "No scores to display yet.\n";
        return;
    }

    vector<ScoreEntry> sorted = scoreboard;
    sort(sorted.begin(), sorted.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.finalScore > b.finalScore;
    });

    cout << string(38, '=') << " TOP 10 SCOREBOARD " << string(38, '=') << endl;
    
    cout << left 
         << setw(7)  << "Rank"
         << setw(15) << "Name"
         << setw(8) << "Mode"
         << setw(8) << "Score"
         << setw(10) << "Food"
         << setw(10) << "Water"
         << setw(7) << "Zones"
         << setw(12) << "Result"
         << setw(20) << "Date" << endl;

    cout << string(95, '-') << endl;

    int rank = 1;
    for (int i = 0; i < min(10, (int)sorted.size()); ++i) {
        cout << left
             << setw(4)  << rank++
             << setw(15) << sorted[i].name
             << setw(8) << sorted[i].difficulty
             << setw(8) << sorted[i].finalScore
             << setw(10) << sorted[i].excessFood
             << setw(10) << sorted[i].excessWater
             << setw(7) << sorted[i].zonesCompleted
             << setw(12) << sorted[i].result
             << setw(20) << sorted[i].dateTime << endl;
    }
    cout << "========================================\n";
}
