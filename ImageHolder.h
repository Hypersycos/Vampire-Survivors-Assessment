#pragma once

#include "GamesEngineeringBase.h"
#include <string>
#include "FixedArray.h"

template <int N>
class ImageHolder
{
protected:
	bool setupRun = false;
	FixedArray<GamesEngineeringBase::Image, N> images;

	void Setup(std::string* paths)
	{
		setupRun = true;
		for (int i = 0; i < N; i++)
		{
			images[i].load(paths[i]);
		}
	}

public:
	ImageHolder() : images()
	{
	}

	GamesEngineeringBase::Image* GetImage(unsigned int i)
	{
		if (!setupRun)
			return nullptr;
		return &images[i];
	}
};