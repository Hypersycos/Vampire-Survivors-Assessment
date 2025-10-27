#include "GamesEngineeringBase.h"

#pragma once

class InputHandler
{
	GamesEngineeringBase::Window& window;
	bool keysLastState[256];
	bool mouseLastState[3];

public:
	InputHandler(GamesEngineeringBase::Window& window) : window(window)
	{
		for (int i = 0; i < 256; i++)
		{
			keysLastState[i] = false;
		}
		for (int i = 0; i < 3; i++)
		{
			mouseLastState[i] = false;
		}
	}
	
	void Update()
	{
		for (int i = 0; i < 256; i++)
		{
			keysLastState[i] = window.keyPressed(i);
		}
		mouseLastState[GamesEngineeringBase::MouseLeft] = window.mouseButtonPressed(GamesEngineeringBase::MouseLeft);
		mouseLastState[GamesEngineeringBase::MouseMiddle] = window.mouseButtonPressed(GamesEngineeringBase::MouseMiddle);
		mouseLastState[GamesEngineeringBase::MouseRight] = window.mouseButtonPressed(GamesEngineeringBase::MouseRight);
		window.checkInput();
	}

	bool KeyHeld(int i)
	{
		return window.keyPressed(i);
	}

	bool KeyDown(int i)
	{
		return window.keyPressed(i) && !keysLastState[i];
	}

	bool KeyUp(int i)
	{
		return !window.keyPressed(i) && keysLastState[i];
	}

	bool MouseHeld(GamesEngineeringBase::MouseButton i)
	{
		return window.mouseButtonPressed(i);
	}

	bool MouseDown(GamesEngineeringBase::MouseButton i)
	{
		return window.mouseButtonPressed(i) && !mouseLastState[i];
	}

	bool MouseUp(GamesEngineeringBase::MouseButton i)
	{
		return !window.mouseButtonPressed(i) && mouseLastState[i];
	}
};