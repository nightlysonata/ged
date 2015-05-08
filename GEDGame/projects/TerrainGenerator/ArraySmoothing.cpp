#include "ArraySmoothing.h"
#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <Windows.h>
#include <iomanip>

// Access a 2D array of width w at position x / y
#define IDX(x, y, w) ((x) + (y) * (w))

int reso;

ArraySmoothing::ArraySmoothing(float* array, int res){
	reso = res;
	smoothArray(array, res, res);
}

struct pos {

	int x;
	int y;
	pos(int i, int j) { x = i; y = j; };
	pos(){ x = 0; y = 0; };
};

void ArraySmoothing::fillArrayWithRandom(float* array, int height, int width){

	srand(time(0));
	int i = 0;

	for (i; i<width*height; i++){
		array[i] = float(rand()) / RAND_MAX;
	}
}

void ArraySmoothing::printArray(float* array, int height, int width){

	int i = 0;
	for (i; i<height; i++){
		int j = 0;
		for (j; j<width; j++){
			std::cout.precision(4);
			std::cout << std::setw(8) << array[IDX(i, j, width)] << ' ';
		}
		std::cout << "\n";
	}
}

void ArraySmoothing::smoothArray(float* array, int height, int width){

	float* hArray = new float[height*width];

	int i = 0;
	for (i; i < height; i++){

		int j = 0;
		for (j; j < width; j++){
			hSmoothArray(hArray, array, pos(i, j));
		}
	}
	copyArray(array, hArray, width, height);
	delete(hArray);
}

void ArraySmoothing::hSmoothArray(float* hArray, float* array, pos p){

	float sum = 0;

	int i = p.x - 1;
	for (i; i < p.x + 2; i++){

		int j = p.y - 1;
		for (j; j < p.y + 2; j++){
			sum += array[IDX(clamp(i, 0, reso - 1), clamp(j, 0, reso - 1), reso)];
		}
	}

	sum *= 1.0 / 9.0;
	hArray[IDX(p.x, p.y, reso)] = sum;
}

int ArraySmoothing::clamp(int value, int minValue, int maxValue){

	return min(maxValue, max(minValue, value));
}

void ArraySmoothing::copyArray(float* ar1, float* ar2, int width, int height){

	int i = 0;
	for (i; i < height; i++){

		int j = 0;
		for (j; j < width; j++){
			ar1[IDX(j, i, width)] = ar2[IDX(j, i, width)];
		}
	}
}
