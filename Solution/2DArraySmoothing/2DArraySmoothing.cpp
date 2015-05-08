// 2DArraySmoothing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <ctime>

// Access a 2D array of width w at position x / y
#define IDX(x, y, w) ((x) + (y) * (w))

#define RAND_MAX = 1.0;

int width;
int height;

float* array = new float[width*height];

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

void fillArrayWithRandom(float* array){
	srand(time(0));
	rand();
}

