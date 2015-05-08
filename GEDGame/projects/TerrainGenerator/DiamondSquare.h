#pragma once
class DiamondSquare
{
public:
	DiamondSquare();
	DiamondSquare(int, float*);
	void initCorners();
	float random(float, float);
	void squareStep(int, int, int);
	void diamondStep(int, int, int);
	int clamp(int);
	int clampBetween(int, int, int);
};

