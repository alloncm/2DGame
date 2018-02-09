#pragma once
#include"Colors.h"
#include<string>
class Surface
{
public:
	Surface();
	Surface(int w, int h);
	Surface(std::string filename);
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y);
private:
	int width;
	int height;
	Color* pixels;
};