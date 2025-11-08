#pragma once
#include "GamesEngineeringBase.h"
#include "Vector.h"

class Font
{
	static inline GamesEngineeringBase::Image fontImage{};

	static inline bool imageLoaded = false;

	inline const static int yGap{ 8 };

public:
	static GamesEngineeringBase::Image* GetImage();

	inline const static Vector<int> letterSize{ 14,20 };

	inline const static int xGap{ 2 };

	static Vector<int> GetLetterLocation(char l);
};