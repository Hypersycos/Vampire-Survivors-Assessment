#include "InputHandler.h"

InputHandler::InputHandler(GamesEngineeringBase::Window& window) : window(window)
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
	
void InputHandler::Update()
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

bool InputHandler::KeyHeld(int i)
{
	return window.keyPressed(i);
}

bool InputHandler::KeyDown(int i)
{
	return window.keyPressed(i) && !keysLastState[i];
}

bool InputHandler::KeyUp(int i)
{
	return !window.keyPressed(i) && keysLastState[i];
}

bool InputHandler::MouseHeld(GamesEngineeringBase::MouseButton i)
{
	return window.mouseButtonPressed(i);
}

bool InputHandler::MouseDown(GamesEngineeringBase::MouseButton i)
{
	return window.mouseButtonPressed(i) && !mouseLastState[i];
}

bool InputHandler::MouseUp(GamesEngineeringBase::MouseButton i)
{
	return !window.mouseButtonPressed(i) && mouseLastState[i];
}