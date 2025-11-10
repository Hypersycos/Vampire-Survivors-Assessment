#pragma once

#include "UIElement.h"
#include "FixedArray.h"
#include "Colour.h"
#include "Text.h"
#include <functional>

class Button : public UIElement
{
	Text text;
	Colour background;
	Colour hover;
	bool hovering{ false };
	std::function<void()> onClick;

public:

	Button(std::string text, Vector<int> pos, Vector<int> size, Colour background, Colour hoverColour, std::function<void()> onClick, PositionAnchor anchor = TopLeft);

	void Update(InputHandler& input, Canvas& canvas) override;
	void Draw(Canvas& canvas, Vector<int> offset = Vector<int>(0, 0)) override;
};