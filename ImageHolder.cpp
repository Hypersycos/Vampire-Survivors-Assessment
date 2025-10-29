#include "ImageHolder.h"

void ImageHolder::Setup(std::string* paths)
{
	setupRun = true;
	for (int i = 0; i < N; i++)
	{
		images[i].load(paths[i]);
	}
}