#include "Slate/Sprites/SpritesCore.h"

#include <iostream>

const Vector2 Vector2::Zero = Vector2(0, 0);


void SRectFilled::Render() {
    for (int row = 0; row < Size.Y; ++row) {
        // Move cursor to (locationY + row, locationX)
        std::cout << "\033[" << (Location.Y + row) << ";" << Location.X << "H";
        for (int col = 0; col < Size.X; ++col) {
            std::cout << RenderChar;
        }
    }
    std::cout.flush();
}

void SRectWireframe::Render() {
    for (int row = 0; row < Size.Y; ++row) {
        // Move cursor to (locationY + row, locationX)
        std::cout << "\033[" << (Location.Y + row) << ";" << Location.X << "H";
        for (int col = 0; col < Size.X; ++col) {
            bool top = (row == 0);
            bool bottom = (row == Size.Y - 1);
            bool left = (col == 0);
            bool right = (col == Size.X - 1);

            if ((top || bottom) && (left || right)) {
                std::cout << "+"; // corners
            }
            else if (top || bottom) {
                std::cout << "-"; // horizontal edges
            }
            else if (left || right) {
                std::cout << "|"; // vertical edges
            }
            else {
                std::cout << " "; // interior
            }
        }
    }
    std::cout.flush();
}

void STextBox::Render() {
    int row = 0, col = 0;
    std::string line;

    for (size_t i = 0; i < Text.size(); ++i) {
        char c = Text[i];

        // Handle explicit newlines
        if (c == '\n') {
            // Print current line
            if (row < Size.Y)
                std::cout << "\033[" << (Location.Y + row) << ";" << Location.X << "H" << line;
            line.clear(); col = 0; ++row; continue;
        }

        line.push_back(c); ++col;

        // Handle wrapping
        if (col >= Size.X) {
            if (bWrapText) {
                if (row < Size.Y || !bClipText)
                    std::cout << "\033[" << (Location.Y + row) << ";" << Location.X << "H" << line;
                line.clear(); col = 0; ++row;
            }
            else if (bClipText) {
                break;
            }
        }

        // Handle clipping
        if (bClipText && row >= Size.Y) { line.clear(); break; }
    }

    // Print any remaining text in the buffer
    if (!line.empty()) {
        std::cout << "\033[" << (Location.Y + row) << ";" << Location.X << "H" << line;
    }

    std::cout.flush();
}
