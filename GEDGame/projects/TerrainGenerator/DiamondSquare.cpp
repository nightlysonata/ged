#include "DiamondSquare.h"
#include <random>
#include <Windows.h>
#include "stdafx.h"
#include "ArraySmoothing.h"

// access a 2D array of width w at position x / y
#define IDX(x, y, w) ((x) + (y) * (w))

std::normal_distribution<float> distribution;
std::default_random_engine generator;

int res;
float* arr;
float roughness;

DiamondSquare::DiamondSquare(int resolution, float* array){
	res = resolution;
	arr = array;

	initCorners();

	// set the roughness for the diamond square algorithm
	roughness = 0.60f;
		
	for (int s = res / 2; s >= 1; s /= 2)
	{
		// iterate diamond step
		for (int y = s; y < res; y += (s * 2))
		{
			for (int x = s; x < res; x += (s * 2))
			{
				diamondStep(x, y, s);
			}
		}

		// iterate square step
		for (int y = 0; y < res; y += (s * 2))
		{
			for (int x = 0; x < res; x += (s * 2))
			{
				squareStep(x, y, s);
			}
		}

	}

	// decrease the roughness
	roughness *= 0.55f;
	

	//TODO Natalia's Version einbauen
	// smooth the calculated heightfield array.
	for (int i = 0; i < 20; ++i)
	{
		//ArraySmoothing(arr, res);
	}
}

#pragma region Diamond-Sqare-Algorithm

void DiamondSquare::diamondStep(int x, int y, int step){

	float a = arr[IDX(clamp(x - step), clamp(y - step), res)];
	float b = arr[IDX(clamp(x + step), clamp(y + step), res)];
	float c = arr[IDX(clamp(x - step), clamp(y + step), res)];
	float d = arr[IDX(clamp(x + step), clamp(y - step), res)];

	arr[IDX(x, y, res)] = clampBetween((a + b + c + d) / 4.0 + random(0.3, 0.7), 0.0, 1.0);
}

void DiamondSquare::squareStep(int x, int y, int step){

	float a = arr[IDX(clamp(x - step), clamp(y - step), res)];
	float b = arr[IDX(clamp(x + step), clamp(y + step), res)];
	float c = arr[IDX(clamp(x - step), clamp(y + step), res)];
	float d = arr[IDX(clamp(x + step), clamp(y - step), res)];

	arr[IDX(x, y, res)] = clampBetween((a + b + c + d) / 4.0 + random(0.3,0.7), 0.0, 1.0);
	 
}
#pragma endregion 


void DiamondSquare::initCorners(){

	float vertex = random(0.3f, 0.7f);
	// left top corner
	arr[IDX(0, 0, (res))] = vertex;
	

	// right top corner
	arr[IDX(res, 0, (res))] = vertex;

	// left bottom corner
	arr[IDX(0, res, (res))] = vertex;

	// right bottom corner
	arr[IDX(res, res, (res))] = vertex;
}

/*
* Returns a random number between min and max.
* Random numbers are normaly distributed with mean at min+max / 2.0 and derivation of max-mean / 3.0.
*/
float DiamondSquare::random(float min, float max){
	// make sure roughness didn't get too small.
	if (max < 0.001f || (min < 0.0f && min > -0.001f))
	{
		max = 0.001f;
		min = -0.001f;
	}

	// generate random numbers as long as the result isn't in the range between min and max.
	while (true)
	{
		float number = (float)distribution(generator);
		if (number >= min && number <= max)
		{
			return number;
		}
	}

	return 0;
}

//clamp between 0 & resolution
int DiamondSquare::clamp(int value){

	return min(res, max(0, value));
}

int DiamondSquare::clampBetween(int value, int minValue, int maxValue){

	return min(maxValue, max(minValue, value));
}

