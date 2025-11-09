#pragma once

#include "UIElement.h"

class Text : public UIElement
{
	std::string text;
	unsigned int scale;

public:
	Text(Vector<int> position, std::string text = "", PositionAnchor anchor = TopLeft, unsigned int scale = 1);

	void Draw(Canvas& canvas, Vector<int> offset) override;
	void Update(InputHandler& input, Canvas& canvas) override;
	void SetText(std::string text);
	void SetScale(unsigned int scale);
	Vector<int> GetSize();
};