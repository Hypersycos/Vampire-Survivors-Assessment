#pragma once
#include "ImageHolder.h"

class EnemyImageHolder : public ImageHolder<4>
{
public:
	EnemyImageHolder();
	void Setup() override;
};