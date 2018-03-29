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
		yEnd = -1;
		yInc = -1;
		this->height = bmpih.biHeight;
	}


	
	fin.seekg(bmpfh.bfOffBits);

	pixels.resize(width*height);

	int padding = (4 - (width * 3) % 4) % 4;
	
	for (int y = yStart; y != yEnd; y += yInc)
	{
		for (int x = 0; x < width; x++)
		{
			pixels[y*width+x] = Color(fin.get(), fin.get(), fin.get());
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
	pixels[y*width+x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	return pixels[y*width+x];
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

void Surface::ToMiror()
{
	for (int xtemp = 0, x = width - 1; xtemp < width/2; xtemp++, x--)
	{
		for (int y = 0; y < height; y++)
		{
			std::swap(pixels[y*width + x], pixels[y*width + xtemp]);
		}
	}
}

Surface Surface::CutRect(Rect<int> r)const 
{
	if (r.GetWidth() > this->width||r.GetHeight()>this->height)
	{
		return *this;
	}
	std::vector<Color> newPixels;
	for (int j = r.GetTopLeft().y; j < r.GetBotoomRight().y; j++)
	{
		for (int i = r.GetTopLeft().x; i < r.GetBotoomRight().x; i++)
		{
			newPixels.emplace_back(pixels[j*this->width + i]);
		}
	}
	Surface s (r.GetWidth(),r.GetHeight());
	s.pixels = newPixels;
	return s;
}

//not working and not even using
/*
void Surface::Save(std::string & filename)
{
	BITMAPINFOHEADER bmpi;
	bmpi.biBitCount = 24;
	bmpi.biSize = sizeof(bmpi);
	bmpi.biWidth = this->width;
	bmpi.biHeight = this->height;
	bmpi.biPlanes = 0;
	bmpi.biCompression = 0;
	bmpi.biSizeImage = 0;
	bmpi.biXPelsPerMeter = 0;
	bmpi.biYPelsPerMeter = 0;
	bmpi.biClrUsed = 0;
	bmpi.biClrImportant = 0;

	BITMAPFILEHEADER bmph;
	bmph.bfType = 'BM';
	bmph.bfReserved1 = 0;
	bmph.bfReserved2 = 0;
	bmph.bfSize = sizeof(bmph) + sizeof(bmpi) + sizeof(this->pixels.size() * 3);
	bmph.bfOffBits = sizeof(bmph) + sizeof(bmpi);

	std::ofstream fout(filename,std::ios::binary);
	fout.exceptions(std::ios::badbit | std::ios::failbit);

	fout.write(reinterpret_cast<char*> (&bmph), sizeof(bmph));
	fout.write(reinterpret_cast<char*> (&bmpi), sizeof(bmpi));

}
*/



