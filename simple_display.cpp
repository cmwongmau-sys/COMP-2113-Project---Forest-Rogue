#include <iostream>
#include <string>
#include "simple_display.h"
using namespace std;

void startScreen() {
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
        "Can you survive the wilds and claim the rogue's prize?",
        "",
        "Good luck, wanderer. You'll need it."
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
    while (lineIndex < insideLines) {
        cout << "|" << string(insideWidth, ' ') << "|" << endl;
        lineIndex++;
    }
    // Bottom border (no side borders)
    string bottomBorder = "+" + string(width - 2, '-') + "+";
    cout << bottomBorder << endl;
}

