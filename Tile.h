#pragma once

class Tile
{
public:
	int type;
	bool* collisionMatrix;
	float* speedMatrix;
};