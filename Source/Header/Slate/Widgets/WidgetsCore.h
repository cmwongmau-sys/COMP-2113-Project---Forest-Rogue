#pragma once

#include "Slate/Sprites/SpritesCore.h"

#include <string>

class IWidget : public ISprite
{
public:
    IWidget(int LocationX, int LocationY, int Width, int Height)
        : ISprite(LocationX, LocationY, Width, Height) {
    }

    IWidget(Vector2 Location, Vector2 Size)
        : ISprite(Location, Size) {
    }

    IWidget(int LocationX, int LocationY)
        : ISprite(LocationX, LocationY, 0, 0) { }

    IWidget(Vector2 Location)
        : ISprite(Location, Vector2::Zero) { }
};

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