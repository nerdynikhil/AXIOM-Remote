#ifndef BUTTONBAR_H
#define BUTTONBAR_H

#include "IButton.h"
#include "../Painter/IPainter.h"

#include "../Color565.h"

#define MAX_BUTTON_NUMBER 3

enum class ButtonPosition : uint8_t
{
    Left = 0,
    Center = 1,
    Right = 2
};

class ButtonBar : public IWidget
{
    IButton* _buttons[MAX_BUTTON_NUMBER] = {nullptr, nullptr, nullptr};

    uint16_t _backgroundColor;
    uint8_t _verticalMargin;

  public:
    ButtonBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height) :
        IWidget(x, y, width, height), _backgroundColor(RGB565(97, 92, 91)), _verticalMargin(1)
    {
    }

    virtual void Draw(IPainter* painter)
    {
        painter->DrawFillRectangle(_x, _y - _verticalMargin, _width, _height + _verticalMargin, _backgroundColor);

        for (int i = 0; i < MAX_BUTTON_NUMBER; i++)
        {
            IButton* button = _buttons[i];

            if (button == nullptr)
            {
                continue;
            }

            button->Draw(painter);
        }
    }

    void SetButton(ButtonPosition position, IButton* button)
    {
        // Adjust positions of the button to correspond to the bar area
        uint8_t buttonWidth = _width / MAX_BUTTON_NUMBER;
        button->SetDimensions(_x + buttonWidth * (uint8_t)position, _y, buttonWidth, _height);

        _buttons[(uint8_t)position] = button;
    }
};

#endif // BUTTONBAR_H