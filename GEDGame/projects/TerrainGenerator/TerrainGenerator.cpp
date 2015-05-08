// TerrainGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include "SimpleImage.h"
#include <iomanip>
#include "TextureGenerator.h"
#include "TerrainGenerator.h"
#include <array>
#include <iterator>
#include "DiamondSquare.h"



// access a 2D array of width w at position x / y
#define IDX(x, y, w) ((x) + (y) * (w))

using std::cout;
using std::endl;
using GEDUtils::SimpleImage;
using GEDUtils::TextureGenerator;
using std::vector;
using std::wstring;
using std::begin;
using std::end;

vector<float> arrayToVector(float*, int);

std::wstring output_height_filename;
std::wstring output_color_filename;
std::wstring output_normal_filename;

int resolution;

int _tmain(int argc, _TCHAR* argv[])
{
	checkArguments(argc, argv);

	float* heightfield = new float[resolution*resolution];
	fillArray(heightfield, resolution);


	//funktioniert noch nicht ohne abzuspacken:
	//DiamondSquare(resolution, heightfield);

	//printArray(heightfield, resolution);

	saveHeightfield(heightfield);
	generateNormalsAndColors(heightfield, resolution);


	delete(heightfield);
	return 0;
}

bool checkArguments(const int argc, _TCHAR* argv[])
{
	try
	{

		if (argc != 9)
		{
			throw std::exception("invalid argument count");
		}
		else
		{
			if (_tcscmp(argv[1], TEXT("-r")) != 0)
			{
				throw std::exception("-r missing");
			}
			else
			{
				//resolution+1
				resolution = _tstoi(argv[2])+1;
				if (resolution <= 0)
				{
					throw std::exception("resolution <= 0");
				}
			}

			if (_tcscmp(argv[3], TEXT("-o_height")) != 0)
			{
				throw std::exception("-o_height missing");
			}
			else
			{
				output_height_filename = (argv[4]);
			}

			if (_tcscmp(argv[5], TEXT("-o_color")) != 0)
			{
				throw std::exception("-o_color missing");
			}
			else
			{
				output_color_filename = argv[6];
			}

			if (_tcscmp(argv[7], TEXT("-o_normal")) != 0)
			{
				throw std::exception("-o_normal missing");
			}
			else
			{
				output_normal_filename = argv[8];
			}
		}
	}
	catch (std::exception e)
	{
		cout << "an exception occurred: " << e.what() << endl;
		return false;
	}

	//return true if all arguments valid
	return true;
}

void saveHeightfield(float* heightfieldArr){

	try{

		GEDUtils::SimpleImage heightfield(resolution, resolution);

		//parse heightfield into SimpleImage
		for (int i = 0; i < resolution; i++){
			for (int j = 0; j < resolution; j++){
				heightfield.setPixel(i, j, heightfieldArr[IDX(i, j, resolution)]);
			}
		}

		//save hightfielt to file
		if (!heightfield.save(output_height_filename.c_str()))
			throw "Could not save Heightfield image!";

	} catch (char* exception) {
		printf("Error: %s\n", exception);
	}
}

void generateNormalsAndColors(float* heightfield, int res){

	TextureGenerator tg(wstring(L"..\\..\\..\\..\\external\\textures\\gras15.jpg"),
		wstring(L"..\\..\\..\\..\\external\\textures\\rock3.jpg"),
		wstring(L"..\\..\\..\\..\\external\\textures\\seafloor.png"),
		wstring(L"..\\..\\\..\\..\\external\\textures\\kork07.jpg"));
	
	std::vector<float> heightfieldV;
	heightfieldV.insert(heightfieldV.begin(), heightfield, heightfield + (res*res));
	//vector<float> heightfieldV = arrayToVector(heightfield, resolution);

	/**
	Generate normal and color textures based on the heightfield properties and store them to the output filenames.
	NOTE: resolution is the actual output resolution, thus the heightfield is supposed to be of size resolution + 1!
	**/
	
	tg.generateAndStoreImages(heightfieldV, resolution-1, output_color_filename, output_normal_filename);
}

void fillArray(float* arr, int res){
	for (int i = 0; i < resolution; i++){
		for (int j = 0; j < resolution; j++){
			arr[IDX(i, j, resolution)] = 0.0;
		}
	}
}

void printArray(float* arr, int res){
	for (int i = 0; i < resolution; i++){
		for (int j = 0; j < resolution; j++){
			cout << std::setw(4) << arr[IDX(i, j, resolution)];
		}
		
		cout << endl;
	}
}

vector<float> arrayToVector(float* arr, int res){

	vector<float> v;
	for (int i = 0; i < res*res; i++){		
		v.push_back(arr[i]);
	}
	v.push_back(0);

	return v;
}



