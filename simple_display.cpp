#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "simple_display.h"
using namespace std;

// Draw the screen to start the game
// Showing game description and player's initial status
// Input: player's status, health, food, water
// Output: prints out the screen, no return
void startScreen(int health, int food, int water) {
    const int width = 80;
    const int totalHeight = 22;          // including bottom border
    const int insideWidth = width - 2;   // 78 for lines with side borders
    const int insideLines = totalHeight - 1; // 21 lines with '|' side borders (bottom border is separate)

    // Offset to the screen
    const int offsetX = 5;
    const int offsetY = 2;

    // Clear screen
    cout << "\033[2J\033[3J\033[1;1H";

    // Move cursor to offset position
    cout << "\033[" << offsetY << ";" << offsetX << "H";

    // Banner box inside the frame
    string bannerText = " WELCOME TO FOREST ROGUE ";
    int textLen = bannerText.length();
    int padding = (insideWidth - textLen) / 2;
    string textLine = string(padding, ' ') + bannerText + string(insideWidth - textLen - padding, ' ');
    string boxBorder = "+" + string(insideWidth - 2, '-') + "+";

    // Print first three lines (banner) with side borders
    cout << "|" << boxBorder << "|" << endl;
    cout << string(offsetX - 1, ' ') << "|" << textLine << "|" << endl;
    cout << string(offsetX - 1, ' ') << "|" << boxBorder << "|" << endl;

    // Content lines (original passage)
    string content[] = {
        "The ancient forest looms before you, dark and unforgiving.",
        "",
        "You must cross 6 deadly zones to reach the other side.",
        "Your life hangs by a thread:",
        "  > Health must stay above 0 (one wrong step could end you).",
        "  > Food and water must NEVER drop below -3.",
        "    (Below that, starvation or thirst will consume you.)",
        "",
        "Every choice matters. Every resource counts.",
        "Yout current status:",
        "Health: " + to_string(health),
        "Food: " + to_string(food),
        "Water: " + to_string(water),
        "",
        "Good luck. You'll need it."
    };

    int numContent = sizeof(content) / sizeof(content[0]);
    const string indent = "    ";
    int lineIndex = 3;   // after banner lines
    for (int i = 0; i < numContent && lineIndex < insideLines; ++i) {
        string line = indent + content[i];
        if (line.length() > insideWidth) line = line.substr(0, insideWidth);
        line.append(insideWidth - line.length(), ' ');
        cout << string(offsetX - 1, ' ') << "|" << line << "|" << endl;
        lineIndex++;
    }
    // Fill remaining lines with empty rows (to reach insideLines = 21)
    while (lineIndex < insideLines - 1) {
        cout << string(offsetX - 1, ' ') << "|" << string(insideWidth, ' ') << "|" << endl;
        lineIndex++;
    }
    // Output "PRESS ENTER" at the bottom
    const string promptText = "PRESS ENTER";
    int promptLen = promptText.length();
    int promptPadding = (insideWidth - promptLen) / 2;
    string promptLine = string(promptPadding, ' ') + promptText +
            string(insideWidth - promptLen - promptPadding, ' ');
    cout << string(offsetX - 1, ' ') << "|" << promptLine << "|" << endl;

    // Bottom border (no side borders)
    string bottomBorder = "+" + string(width - 2, '-') + "+";
    cout << string(offsetX - 1, ' ') << bottomBorder << endl;

    cin.get();
}

// -------------------------------------------------------------------
// Draws the static frame (banner box + content + empty rows + bottom border)
// Parameters:
//   bannerText : the title to display (will be centered and capitalised automatically)
//   content    : a vector of strings (each line will be indented 4 spaces)
// -------------------------------------------------------------------
void DrawStaticFrame(const string& bannerText, const vector<string>& content) {
    const int width = 80;
    const int totalHeight = 22;
    const int insideWidth = width - 2;   // 78
    const int insideHeight = totalHeight - 1;  // 21 lines inside + bottom border = 22 total

    // Offset to the screen
    const int offsetX = 5;
    const int offsetY = 2;

    // Clear screen
    cout << "\033[2J\033[3J\033[1;1H";

    // Move cursor to offset position
    cout << "\033[" << offsetY << ";" << offsetX << "H";

    // ----- Convert banner text to uppercase and add spaces -----
    string upperBanner = bannerText;
    for (char& c : upperBanner) c = toupper(c);
    string banner = " " + upperBanner + " ";  // add space padding inside the box

    // ----- 3‑line banner box (full inner width) -----
    int padding = (insideWidth - banner.length()) / 2;
    string textLine = string(padding, ' ') + banner + string(insideWidth - banner.length() - padding, ' ');
    string boxBorder = "+" + string(insideWidth - 2, '-') + "+";

    cout << "|" << boxBorder << "|" << endl;
    cout << string(offsetX - 1, ' ') << "|" << string(insideWidth, ' ') << "|" << endl;
    cout << string(offsetX - 1, ' ') << "|" << textLine << "|" << endl;
    cout << string(offsetX - 1, ' ') << "|" << string(insideWidth, ' ') << "|" << endl;
    cout << string(offsetX - 1, ' ') << "|" << boxBorder << "|" << endl;
    cout << string(offsetX - 1, ' ') << "|" << string(insideWidth, ' ') << "|" << endl;

    // ----- Print content lines (indented 4 spaces) -----
    const string indent = "    ";
    int lineIndex = 6;   // we have already printed 3 banner lines
    for (const string& rawLine : content) {
        if (lineIndex >= insideHeight) break;
        string line = indent + rawLine;
        if (line.length() > insideWidth) line = line.substr(0, insideWidth);
        line.append(insideWidth - line.length(), ' ');
        cout << string(offsetX - 1, ' ') << "|" << line << "|" << endl;
        lineIndex++;
    }

    // ----- Fill remaining lines with empty rows (for menu or other UI) -----
    while (lineIndex < insideHeight) {
        cout << string(offsetX - 1, ' ') << "|" << string(insideWidth, ' ') << "|" << endl;
        lineIndex++;
    }

    // ----- Bottom border -----
    string bottomBorder = "+" + string(width - 2, '-') + "+";
    cout << string(offsetX - 1, ' ') << bottomBorder << endl;

    cin.get();
}

// Draws one screen for specific zone (1-6) with ASCII art perfectly centered
// Input: zone number
// Output: prints out the screen showing the zone, no return
void DrawZone(int zone) {
    if (zone < 1 || zone > 6) zone = 1;

    const int width = 80;
    const int insideWidth = width - 2;      // 78
    const int contentLines = 20;

    const int offsetX = 5;
    const int offsetY = 2;

    // Clear screen and move cursor
    cout << "\033[2J\033[3J\033[1;1H";
    cout << "\033[" << offsetY << ";" << offsetX << "H";

    // Zones 1 to 6 - ZONE 4 AND ZONE 5 SWAPPED
    vector<string> zones = {
        // Zone 1
        R"( ________    ______   .__   __.  _______     __ 
|       /   /  __  \  |  \ |  | |   ____|   /_ |
`---/  /   |  |  |  | |   \|  | |  |__       | |
   /  /    |  |  |  | |  . `  | |   __|      | |
  /  /----.|  `--'  | |  |\   | |  |____     | |
 /________| \______/  |__| \__| |_______|    |_|)",

        // Zone 2
        R"( ________    ______   .__   __.  _______     ___  
|       /   /  __  \  |  \ |  | |   ____|   |__ \ 
`---/  /   |  |  |  | |   \|  | |  |__         ) |
   /  /    |  |  |  | |  . `  | |   __|       / / 
  /  /----.|  `--'  | |  |\   | |  |____     / /_ 
 /________| \______/  |__| \__| |_______|   |____|)",

        // Zone 3
        R"( ________    ______   .__   __.  _______     ____  
|       /   /  __  \  |  \ |  | |   ____|   |___ \ 
`---/  /   |  |  |  | |   \|  | |  |__        __) |
   /  /    |  |  |  | |  . `  | |   __|      |__ < 
  /  /----.|  `--'  | |  |\   | |  |____     ___) |
 /________| \______/  |__| \__| |_______|   |____/ )",

        // Zone 4 ← now using the one that was previously Zone 5
        R"( ________    ______   .__   __.  _______     _  _   
|       /   /  __  \  |  \ |  | |   ____|   | || |  
`---/  /   |  |  |  | |   \|  | |  |__      | || |_ 
   /  /    |  |  |  | |  . `  | |   __|     |__   _|
  /  /----.|  `--'  | |  |\   | |  |____       | |  
 /________| \______/  |__| \__| |_______|      |_|  )",

        // Zone 5 ← now using the one that was previously Zone 4
        R"( ________    ______   .__   __.  _______     _____ 
|       /   /  __  \  |  \ |  | |   ____|   | ____|
`---/  /   |  |  |  | |   \|  | |  |__      | |__  
   /  /    |  |  |  | |  . `  | |   __|     |___ \ 
  /  /----.|  `--'  | |  |\   | |  |____     ___) |
 /________| \______/  |__| \__| |_______|   |____/ )",

        // Zone 6
        R"( ________    ______   .__   __.  _______       __  
|       /   /  __  \  |  \ |  | |   ____|     / /  
`---/  /   |  |  |  | |   \|  | |  |__       / /_  
   /  /    |  |  |  | |  . `  | |   __|     | '_ \ 
  /  /----.|  `--'  | |  |\   | |  |____    | (_) |
 /________| \______/  |__| \__| |_______|    \___/ )"
    };

    // Extract lines from the selected zone
    stringstream ss(zones[zone - 1]);
    vector<string> artLines;
    string line;
    while (getline(ss, line)) {
        artLines.push_back(line);
    }

    int artHeight = artLines.size();
    int totalPadding = contentLines - artHeight;
    int topPadding = totalPadding / 2;

    string border = "+" + string(width - 2, '-') + "+";

    cout << border << endl;                    // Top border

    for (int i = 0; i < topPadding; ++i) {     // Vertical top padding
        cout << string(offsetX - 1, ' ') << "|" << string(insideWidth, ' ') << "|" << endl;
    }

    for (const string& artLine : artLines) {   // ASCII art - horizontally centered
        int leftPad = (insideWidth - (int)artLine.length()) / 2;
        if (leftPad < 0) leftPad = 0;
        string centered = string(leftPad, ' ') + artLine +
                          string(insideWidth - artLine.length() - leftPad, ' ');
        cout << string(offsetX - 1, ' ') << "|" << centered << "|" << endl;
    }

    for (int i = 0; i < totalPadding - topPadding; ++i) {  // Vertical bottom padding
        cout << string(offsetX - 1, ' ') << "|" << string(insideWidth, ' ') << "|" << endl;
    }

    cout << string(offsetX - 1, ' ') << border << endl;                    // Bottom border

    cin.get();
}
