#include "FollowCamera.h"

FollowCamera::FollowCamera() : target(nullptr)
{

}

FollowCamera::FollowCamera(Sprite* target) : target(target)
{
}

void FollowCamera::SetTarget(Sprite* _target)
{
	target = _target;
}

Vector<float> FollowCamera::GetPosition()
{
	if (target == nullptr)
		return Vector<float>(0, 0);
	return target->GetPosition();
}

void FollowCamera::Update(InputHandler& inputHandler)
{
}