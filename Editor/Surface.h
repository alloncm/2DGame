#pragma once
#include"Colors.h"
#include<string>
#include<vector>
#include<fstream>
#include<Windows.h>
#include<cassert>
#include"Rect.h"
class Surface
{
public:
	Surface();
	Surface(int w, int h);
	Surface(std::string filename);
	Surface(const Surface& s) = default;
	Surface(Surface&& s);
	Surface& operator= (const Surface& s) = default;
	Surface& operator= (Surface&& s);
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y)const;
	int GetHeight()const;
	int GetWidth()const;
	void Fill(Color c);
	RectI GetRect()const;
	void ToMiror();
	Surface CutRect(Rect<int> r)const;
	//void Save(std::string& filename );
private:
	int width;
	int height;
	std::vector<Color> pixels;
};