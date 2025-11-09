#include "Text.h"
#include "font.h"

Text::Text(Vector<int> position, std::string text, PositionAnchor anchor, unsigned int scale) : UIElement(position, anchor), text(text)
{
	SetScale(scale);
}

void Text::Draw(Canvas& canvas, Vector<int> offset)
{
	canvas.DrawFont(text, (Vector<float>)drawPosition + offset, scale);
}

void Text::Update(InputHandler& input, Canvas& canvas)
{
}

void Text::SetText(std::string text)
{
	this->text = text;
	size = GetSize();
	SetPosition(anchorPosition, anchor);
}

void Text::SetScale(unsigned int scale)
{
	if (scale > 0)
		this->scale = scale;
	size = GetSize();
	SetPosition(anchorPosition, anchor);
}

Vector<int> Text::GetSize()
{
	return Vector<int>((text.length() * Font::letterSize.x + max(0, (text.length() - 1)) * Font::xGap) * scale, Font::letterSize.y * scale);
}