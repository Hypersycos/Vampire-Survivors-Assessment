#pragma once
#include "Vector.h"
#include "Canvas.h"
#include "InputHandler.h"

class UIElement
{
public:
	enum PositionAnchor
	{
		Centre,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

protected:
	Vector<int> anchorPosition;
	Vector<int> drawPosition;
	Vector<int> size;
	PositionAnchor anchor;

public:

	UIElement(Vector<int> position, PositionAnchor anchor = TopLeft) : size(Vector<int>(0, 0))
	{
		SetPosition(position, anchor);
	}

	UIElement(Vector<int> position, Vector<int> size, PositionAnchor anchor = TopLeft) : size(size), anchor(anchor)
	{
		SetPosition(position, anchor);
	}

	void Draw(Canvas& canvas)
	{
		Draw(canvas, Vector<int>(0, 0));
	}

	virtual void Draw(Canvas& canvas, Vector<int> parentPos) = 0;

	void DrawChild(Canvas& canvas, UIElement* parent)
	{
		Draw(canvas, parent->drawPosition);
	}

	virtual void Update(InputHandler& input, Canvas& canvas) = 0;

	void SetPosition(Vector<int> position, PositionAnchor anchor = TopLeft)
	{
		anchorPosition = position;
		this->anchor = anchor;
		switch (anchor)
		{
		case UIElement::Centre:
			position.x -= size.x / 2;
			position.y -= size.y / 2;
			break;
		case UIElement::TopLeft:
			break;
		case UIElement::TopRight:
			position.x -= size.x;
			break;
		case UIElement::BottomLeft:
			position.y -= size.y;
			break;
		case UIElement::BottomRight:
			position.x -= size.x;
			position.y -= size.y;
			break;
		default:
			break;
		}
		drawPosition = position;
	}
};