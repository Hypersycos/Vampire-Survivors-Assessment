#pragma once
#include "ImageHolder.h"

class EnemyImageHolder : public ImageHolder<6>
{
public:
	EnemyImageHolder();
	void Setup() override;
};