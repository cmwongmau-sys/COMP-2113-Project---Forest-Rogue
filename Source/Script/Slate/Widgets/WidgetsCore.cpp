#include "../../../Header/Slate/Widgets/WidgetsCore.h"
#include <cmath>

SBar::SBar(int x, int y, int w, int h, float percent,
           std::string empty, std::string filled)
    : SRectFilled(x, y, w, h, empty), FillPercentage(percent), RenderCharFilled(filled) {}

void SBar::Render() {
    SRectFilled::Render();
    int fillWidth = (int)round(Size.X * FillPercentage);
    if (fillWidth > 0) {
        SRectFilled filledPart(Location.X, Location.Y, fillWidth, Size.Y, RenderCharFilled);
        filledPart.Render();
    }
}
