#ifndef WIDGETS_CORE_H
#define WIDGETS_CORE_H

#include "../Sprites/SpritesCore.h"
#include <string>

class IWidget : public ISprite {
public:
    IWidget(int x = 0, int y = 0) : ISprite(x, y, 0, 0) {}
    virtual ~IWidget() = default;
    virtual void Render() override = 0;
};

class SBar : public SRectFilled {
protected:
    float FillPercentage;
    std::string RenderCharFilled;
public:
    SBar(int x, int y, int w, int h, float percent,
         std::string empty = ".", std::string filled = "#");
    void Render() override;
};

#endif
