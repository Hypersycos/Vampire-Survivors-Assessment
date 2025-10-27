#include "CameraTarget.h"
#include "Sprite.h"

class FollowCamera : public CameraTarget
{
	Sprite* target{nullptr};

public:
	FollowCamera(Sprite* target) : target(target)
	{
	}

	void SetTarget(Sprite* _target)
	{
		target = _target;
	}

	Vector<float> GetPosition() override
	{
		return target->GetPosition();
	}

	void Update(InputHandler& inputHandler) override
	{
	}
};