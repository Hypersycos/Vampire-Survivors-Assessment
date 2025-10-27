#include "InputHandler.h"

InputHandler::InputHandler(GamesEngineeringBase::Window& window) : window(window)
{
}
	
void InputHandler::Update()
{
	window.checkInput();
	altIndex = index;
	index = (index + 1) % 2;
	for (int i = 0; i < 256; i++)
	{
		keysLastState[i][index] = window.keyPressed(i);
	}
	mouseLastState[GamesEngineeringBase::MouseLeft][index] = window.mouseButtonPressed(GamesEngineeringBase::MouseLeft);
	mouseLastState[GamesEngineeringBase::MouseMiddle][index] = window.mouseButtonPressed(GamesEngineeringBase::MouseMiddle);
	mouseLastState[GamesEngineeringBase::MouseRight][index] = window.mouseButtonPressed(GamesEngineeringBase::MouseRight);
	dt = timer.dt();
}

float InputHandler::GetDT() const
{
	return dt;
}

bool InputHandler::KeyHeld(int i) const
{
	return window.keyPressed(i);
}

bool InputHandler::KeyDown(int i) const
{
	return window.keyPressed(i) && !keysLastState[i][altIndex];
}

bool InputHandler::KeyUp(int i) const
{
	return !window.keyPressed(i) && keysLastState[i][altIndex];
}

bool InputHandler::MouseHeld(GamesEngineeringBase::MouseButton i) const
{
	return window.mouseButtonPressed(i);
}

bool InputHandler::MouseDown(GamesEngineeringBase::MouseButton i) const
{
	return window.mouseButtonPressed(i) && !mouseLastState[i][altIndex];
}

bool InputHandler::MouseUp(GamesEngineeringBase::MouseButton i) const
{
	return !window.mouseButtonPressed(i) && mouseLastState[i][altIndex];
}