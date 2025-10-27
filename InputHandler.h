#include "GamesEngineeringBase.h"

#pragma once

class InputHandler
{
	GamesEngineeringBase::Window& window;
	bool keysLastState[256];
	bool mouseLastState[3];

public:
	InputHandler(GamesEngineeringBase::Window& window);

	void Update();

	bool KeyHeld(int i);

	bool KeyDown(int i);

	bool KeyUp(int i);

	bool MouseHeld(GamesEngineeringBase::MouseButton i);

	bool MouseDown(GamesEngineeringBase::MouseButton i);

	bool MouseUp(GamesEngineeringBase::MouseButton i);
};