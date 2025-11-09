#include "GamesEngineeringBase.h"
#include "Canvas.h"

#pragma once

class InputHandler
{
	GamesEngineeringBase::Window& window;
	GamesEngineeringBase::Timer timer;
	float dt{ 0 };
	int index{ 0 };
	int altIndex{ 1 };
	bool keysLastState[256][2]{};
	bool mouseLastState[3][2]{};
	int lastWheel{ 0 };
	int wheelState{ 0 };

public:
	InputHandler(GamesEngineeringBase::Window& window);

	void Update();

	float GetDT() const;

	bool KeyHeld(int i) const;

	bool KeyDown(int i) const;

	bool KeyUp(int i) const;

	bool MouseHeld(GamesEngineeringBase::MouseButton i) const;

	bool MouseDown(GamesEngineeringBase::MouseButton i) const;

	bool MouseUp(GamesEngineeringBase::MouseButton i) const;

	int MouseWheel() const;

	int MouseX() const;

	int MouseY() const;

	int MouseX(Canvas& canvas) const;

	int MouseY(Canvas& canvas) const;
};