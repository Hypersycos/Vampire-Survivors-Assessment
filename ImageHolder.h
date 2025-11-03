#pragma once

#include "GamesEngineeringBase.h"
#include <string>
#include "FixedArray.h"

template <int N>
class ImageHolder
{
protected:
	bool setupRun = false;
	FixedArray<GamesEngineeringBase::Image*, N> images;

	void Setup(std::string* paths)
	{
		for (int i = 0; i < N; i++)
		{
			images[i] = new GamesEngineeringBase::Image{};
			if (!images[i]->load(paths[i]))
				return;
		}
		setupRun = true;
	}

	virtual void Setup() = 0;

public:
	ImageHolder() : images()
	{
	}

	GamesEngineeringBase::Image* GetImage(unsigned int i)
	{
		if (!setupRun)
			Setup();
		if (!setupRun)
			return nullptr;
		return images[i];
	}

	~ImageHolder()
	{
		for (GamesEngineeringBase::Image* img : images)
		{
			delete img;
		}
	}
};