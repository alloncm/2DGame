#include "Surface.h"

Surface::Surface()
	:
	width(0),
	height(0),
	pixels(0)
{
}

Surface::Surface(int w, int h):
	width(w),
	height(h)
{
	pixels.resize(w*h);
}

Surface::Surface(std::string filename)
{
	std::ifstream fin(filename,std::ios::binary);
	fin.exceptions(std::ios::failbit | std::ios::badbit);

	BITMAPFILEHEADER bmpfh;
	fin.read(reinterpret_cast<char*> (&bmpfh), sizeof(bmpfh));

	BITMAPINFOHEADER bmpih;
	fin.read(reinterpret_cast<char*>(&bmpih),sizeof(bmpih));


	assert(bmpih.biBitCount == 24 || bmpih.biBitCount == 32);
	assert(bmpih.biCompression == BI_RGB);
	bool Is32 = bmpih.biBitCount == 32;
	this->width = bmpih.biWidth;
	int yStart, yEnd, yInc;
	if (bmpih.biHeight < 0)
	{
		yStart = 0;
		yEnd = -bmpih.biHeight;
		yInc = 1;
		this->height = -bmpih.biHeight;
	}
	else
	{
		yStart = bmpih.biHeight - 1;
		yEnd = 0;
		yInc = -1;
		this->height = bmpih.biHeight;
	}


	
	fin.seekg(bmpfh.bfOffBits);

	pixels.resize(width*height);

	int padding = (4 - (width * 3) % 4) % 4;
	for (int x = 0; x < width; x++)
	{
		for (int y=yStart; y != yEnd; y += yInc)
		{
			pixels[x*height + y] = Color(fin.get(), fin.get(), fin.get());
			if (Is32)
			{
				fin.seekg(1,std::ios::cur);
			}
		}
		if (!Is32)
		{
			fin.seekg(padding, std::ios::cur);
		}
	}
}

Surface::Surface(Surface && s)
{
	*this = s;
}

Surface & Surface::operator=(Surface && s)
{
	this->width = std::move(s.width);
	this->height = std::move(s.height);
	this->pixels = std::move(s.pixels);
	s.width = 0;
	s.height = 0;
	s.pixels.resize(0);
	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	pixels[x*height + y] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	return pixels[x*height + y];
}

int Surface::GetHeight() const
{
	return this->height;
}

int Surface::GetWidth() const
{
	return this->width;
}

void Surface::Fill(Color c)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			pixels[i*height + j] = c;
		}
	}
}

RectI Surface::GetRect() const
{
	return RectI(0,0,width,height);
}



