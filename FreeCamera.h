#pragma once

#include "CameraTarget.h"

class FreeCamera : public CameraTarget
{
	Vector<float> position{ 0, 0 };

public:
	void Move(Vector<float> movement);

	Vector<float> GetPosition() override;

	void Update(InputHandler& inputHandler) override;
};