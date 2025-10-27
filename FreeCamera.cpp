#include "CameraTarget.h"

class FreeCamera : public CameraTarget
{
	Vector<float> position{ 0, 0 };

public:
	void Move(Vector<float> movement)
	{
		position += movement;
	}

	Vector<float> GetPosition() override
	{
		return position;
	}

	void Update(InputHandler& inputHandler) override
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
};