#include "Slate/Widgets/WidgetsCore.h"

#include <cmath>

void SBar::Render()
{
    SRectFilled::Render();

    Vector2 FillSize((int)round(Size.X * FillPercentage), Size.Y);
    SRectFilled FilledPart(Location, FillSize, RenderCharFilled);    

    FilledPart.Render();
}
