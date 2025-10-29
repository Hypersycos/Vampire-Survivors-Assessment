#pragma once

#include "CameraTarget.h"
#include "Sprite.h"

class FollowCamera : public CameraTarget
{
	Sprite* target{ nullptr };

public:
	FollowCamera(Sprite* target);

	void SetTarget(Sprite* _target);

	Vector<float> GetPosition() override;

	void Update(InputHandler& inputHandler) override;
};