#include <iostream>
#include <string>
#include <vector>
#include "simple_display.h"
using namespace std;

void startScreen(int health, int food, int water) {
    const int width = 80;
    const int totalHeight = 22;          // including bottom border
    const int insideWidth = width - 2;   // 78 for lines with side borders
    const int insideLines = totalHeight - 1; // 21 lines with '|' side borders (bottom border is separate)

    // Clear screen
    cout << "\033[2J\033[3J\033[1;1H";

    // Banner box inside the frame
    string bannerText = " WELCOME TO FOREST ROGUE ";
    int textLen = bannerText.length();
    int padding = (insideWidth - textLen) / 2;
    string textLine = string(padding, ' ') + bannerText + string(insideWidth - textLen - padding, ' ');
    string boxBorder = "+" + string(insideWidth - 2, '-') + "+";

    // Print first three lines (banner) with side borders
    cout << "|" << boxBorder << "|" << endl;
    cout << "|" << textLine << "|" << endl;
    cout << "|" << boxBorder << "|" << endl;

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
        "Yout cuurent status:",
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
        cout << "|" << line << "|" << endl;
        lineIndex++;
    }
    // Fill remaining lines with empty rows (to reach insideLines = 21)
    while (lineIndex < insideLines - 1) {
        cout << "|" << string(insideWidth, ' ') << "|" << endl;
        lineIndex++;
    }
    // Output "PRESS ENTER" at the bottom
    const string promptText = "PRESS ENTER";
    int promptLen = promptText.length();
    int promptPadding = (insideWidth - promptLen) / 2;
    string promptLine = string(promptPadding, ' ') + promptText +
            string(insideWidth - promptLen - promptPadding, ' ');
    cout << "|" << promptLine << "|" << endl;

    // Bottom border (no side borders)
    string bottomBorder = "+" + string(width - 2, '-') + "+";
    cout << bottomBorder << endl;

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

    // Clear screen completely (including scrollback) – works on macOS/Linux/modern Windows Terminal
    cout << "\033[2J\033[3J\033[1;1H";

    // ----- Convert banner text to uppercase and add spaces -----
    string upperBanner = bannerText;
    for (char& c : upperBanner) c = toupper(c);
    string banner = " " + upperBanner + " ";  // add space padding inside the box

    // ----- 3‑line banner box (full inner width) -----
    int padding = (insideWidth - banner.length()) / 2;
    string textLine = string(padding, ' ') + banner + string(insideWidth - banner.length() - padding, ' ');
    string boxBorder = "+" + string(insideWidth - 2, '-') + "+";

    cout << "|" << boxBorder << "|" << endl;
    cout << "|" << textLine << "|" << endl;
    cout << "|" << boxBorder << "|" << endl;

    // ----- Print content lines (indented 4 spaces) -----
    const string indent = "    ";
    int lineIndex = 3;   // we have already printed 3 banner lines
    for (const string& rawLine : content) {
        if (lineIndex >= insideHeight) break;
        string line = indent + rawLine;
        if (line.length() > insideWidth) line = line.substr(0, insideWidth);
        line.append(insideWidth - line.length(), ' ');
        cout << "|" << line << "|" << endl;
        lineIndex++;
    }

    // ----- Fill remaining lines with empty rows (for menu or other UI) -----
    while (lineIndex < insideHeight) {
        cout << "|" << string(insideWidth, ' ') << "|" << endl;
        lineIndex++;
    }

    // ----- Bottom border -----
    string bottomBorder = "+" + string(width - 2, '-') + "+";
    cout << bottomBorder << endl;

    cin.get();
}

