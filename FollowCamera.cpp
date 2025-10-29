#include "FollowCamera.h"

FollowCamera::FollowCamera(Sprite* target) : target(target)
{
}

void FollowCamera::SetTarget(Sprite* _target)
{
	target = _target;
}

Vector<float> FollowCamera::GetPosition()
{
	return target->GetPosition();
}

void FollowCamera::Update(InputHandler& inputHandler)
{
}