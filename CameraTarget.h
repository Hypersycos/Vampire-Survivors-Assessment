#pragma once

#include "Vector.h"
#include "InputHandler.h"

class CameraTarget
{
public:
	virtual Vector<float> GetPosition() = 0;
	virtual void Update(InputHandler& inputHandler) = 0;
};