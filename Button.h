#pragma once

#include "UIElement.h"
#include "FixedArray.h"
#include "Colour.h"
#include "Text.h"

class Button : public UIElement
{
	Text text;
	Colour background;
	Colour hover;
	bool hovering{ false };

public:

	Button(std::string text, Vector<int> pos, Vector<int> size, Colour background, Colour hoverColour, PositionAnchor anchor = TopLeft);

	void Update(InputHandler& input, Canvas& canvas) override;
	void Draw(Canvas& canvas, Vector<int> offset = Vector<int>(0, 0)) override;
};