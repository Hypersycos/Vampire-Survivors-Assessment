#include "FreeCamera.h"

void FreeCamera::Move(Vector<float> movement)
{
	position += movement;
}

Vector<float> FreeCamera::GetPosition()
{
	return position;
}

void FreeCamera::Update(InputHandler& inputHandler)
{
	Vector<float> movement = Vector<float>();

	if (inputHandler.KeyHeld('W'))
	{
		movement.y -= 1;
	}
	if (inputHandler.KeyHeld('A'))
	{
		movement.x -= 1;
	}
	if (inputHandler.KeyHeld('S'))
	{
		movement.y += 1;
	}
	if (inputHandler.KeyHeld('D'))
	{
		movement.x += 1;
	}

	if (movement.x != 0 || movement.y != 0)
	{
		movement *= inputHandler.GetDT() * (inputHandler.KeyHeld(VK_SHIFT) ? 2000 : 100);
		if (movement.x != 0 && movement.y != 0)
			movement *= 0.7071;

		position += movement;
	}
}