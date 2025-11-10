#include "Button.h"

Button::Button(std::string text, Vector<int> pos, Vector<int> size, Colour background, Colour hover, std::function<void()> onClick, PositionAnchor anchor) : text{size / 2, text, Centre}, background(background), hover(hover), UIElement(pos, size, anchor), onClick{onClick}
{
}

void Button::Update(InputHandler& input, Canvas& canvas)
{
	int mouseX = input.MouseX(canvas);
	hovering = false;
	if (mouseX >= drawPosition.x && mouseX < drawPosition.x + size.x)
	{
		int mouseY = input.MouseY(canvas);
		if (mouseY >= drawPosition.y && mouseY < drawPosition.y + size.y)
		{
			if (input.MouseDown(GamesEngineeringBase::MouseLeft))
			{
				onClick();
			}
			else
			{
				hovering = true;
			}
		}
	}
}

void Button::Draw(Canvas& canvas, Vector<int> offset)
{
	Vector<int> drawPos = drawPosition - offset;
	Colour* c = &background;
	if (hovering)
		c = &hover;
	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			if (hovering)
				canvas.DrawPixelSafe(drawPos.x + i, drawPos.y + j, c->alpha, c->color);
			else
				canvas.DrawPixelSafe(drawPos.x + i, drawPos.y + j, c->alpha, c->color);
		}
	}
	text.DrawChild(canvas, this);
}
