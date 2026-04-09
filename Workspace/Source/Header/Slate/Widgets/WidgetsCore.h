#pragma once

#include "../Sprites/SpritesCore.h"

#include <string>

class IWidget : public ISprite { };

class SBar : public SRectFilled
{
protected:
    float FillPercentage;
    std::string RenderCharFilled;

public:
    SBar(Vector2 Location, Vector2 Size, float FillPercentage,
        std::string RenderCharUnfilled = ".",
        std::string RenderCharFilled = "#")
        : SRectFilled(Location, Size, RenderCharUnfilled)
        , FillPercentage(FillPercentage)
        , RenderCharFilled(RenderCharFilled) {
    }

    SBar(int LocationX, int LocationY, int Width, int Height,
        float FillPercentage,
        std::string RenderCharUnfilled = ".",
        std::string RenderCharFilled = "#")
        : SRectFilled(LocationX, LocationY, Width, Height, RenderCharUnfilled)
        , FillPercentage(FillPercentage)
        , RenderCharFilled(RenderCharFilled) {
    }

    virtual void Render() override;
};