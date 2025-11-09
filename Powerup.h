#pragma once

#include "CollisionSprite.h"

class Powerup : public CollisionSprite
{
	static inline GamesEngineeringBase::Image powerupImage{};

	static inline bool imageLoaded = false;

	static GamesEngineeringBase::Image* GetImage();

public:
	Powerup(Vector<float> position);
	Powerup();
};