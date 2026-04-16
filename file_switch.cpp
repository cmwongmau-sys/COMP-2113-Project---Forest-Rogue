#include "file_switch.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

// Save whole result to scoreboard
void saveScoreboard(vector<ScoreEntry>& scoreboard, string file) {
    if (scoreboard.empty()) {
        cout << "Warning: Scoreboard is empty. Nothing to save." << endl;
        return;
    }

    // Step 1: Sort the scoreboard by FinalScore (Descending)
    sort(scoreboard.begin(), scoreboard.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.finalScore > b.finalScore;
    });

    // Step 2: Open file in overwrite mode (not append)
    ofstream outFile(file);
    
    if (!outFile.is_open()) {
        cerr << "Error: Could not open " << file << " for writing!" << endl;
        return;
    }

    // Step 3: Write current date and time as header
    time_t now = time(0);
    char dt[30];
    strftime(dt, sizeof(dt), "%Y-%m-%d %H:%M:%S", localtime(&now));
    
    outFile << "=== SURVIVAL SCOREBOARD - Updated: " << dt << " ===" << endl;
    outFile << "Name|Difficulty|FinalScore|ExcessFood|ExcessWater|ZonesCompleted|DateTime" << endl;
    outFile << "--------------------------------------------------------------------------------" << endl;

    // Step 4: Write all sorted entries
    for (const auto& entry : scoreboard) {
        outFile << entry.name << "|" 
                << entry.difficulty << "|" 
                << entry.finalScore << "|" 
                << entry.excessFood << "|" 
                << entry.excessWater << "|" 
                << entry.zonesCompleted << "|" 
                << entry.dateTime << endl;
    }

    outFile.close();
    
    cout << "Scoreboard saved and sorted successfully (" << scoreboard.size() 
         << " entries) at " << dt << endl;
}

// Load all scoreboard data
void loadScoreboard(vector<ScoreEntry>& scoreboard) {
    scoreboard.clear();
    
    ifstream inFile("scoreboard.txt");
    
    // Case 1: File does not exist or cannot be opened
    if (!inFile.is_open()) {
        cout << "No previous scoreboard found. Starting new scoreboard." << endl;
        return;   
    }

    string line;
    int lineNumber = 0;
    int validEntries = 0;
    int corruptedEntries = 0;

    while (getline(inFile, line)) {
        lineNumber++;
        
        if (line.empty() || line.find_first_not_of(" \t") == string::npos) {
            continue;  // Skip empty lines
        }

        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, '|')) {
            tokens.push_back(token);
        }

        // Case 2: Wrong number of columns (corrupted line)
        if (tokens.size() != 7) {
            cerr << "Warning: Corrupted line " << lineNumber 
                 << " in scoreboard.txt (expected 7 columns, got " 
                 << tokens.size() << ")" << endl;
            corruptedEntries++;
            continue;
        }

        try {
            // Case 3: Invalid number conversion
            ScoreEntry s;
            s.name          = tokens[0];
            s.difficulty    = stoi(tokens[1]);
            s.finalScore    = stoi(tokens[2]);
            s.excessFood    = stoi(tokens[3]);
            s.excessWater   = stoi(tokens[4]);
            s.zonesCompleted= stoi(tokens[5]);
            s.dateTime      = tokens[6];

            // Basic validation
            if (s.difficulty < 0 || s.difficulty > 2) {
                throw invalid_argument("Invalid difficulty");
            }
            if (s.zonesCompleted < 0 || s.zonesCompleted > 6) {
                throw invalid_argument("Invalid zones");
            }

            scoreboard.push_back(s);
            validEntries++;

        } catch (...) {
            cerr << "Warning: Invalid data on line " << lineNumber 
                 << " in scoreboard.txt. Skipping." << endl;
            corruptedEntries++;
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
