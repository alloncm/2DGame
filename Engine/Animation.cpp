#include "Animation.h"

Animation::Animation(std::string s, float ht, int w, int h, Vec2_<int> start, Vec2_<int>stop,Color ch)
	:
	source(SpriteManager::GetManager().Get(s)),
	holdTime(ht),
	width(w),
	height(h),
	curFrame(0),
	time(0),
	chroma(ch)
{
	for (int i = start.y; i < stop.y+1; i += h)
	{
		for (int j = start.x; j < stop.x; j += w)
		{
			frames.emplace_back(RectI( j,i,w,h ));
		}
	}
}

Animation::Animation(std::string s, float ht, int w, int h, Color ch)
	:
	source(SpriteManager::GetManager().Get(s)),
	holdTime(ht),
	width(w),
	height(h),
	curFrame(0),
	time(0),
	chroma(ch)
{
	for (int i = 0; i < source->GetHeight(); i += h)
	{
		for (int j = 0; j < source->GetWidth(); j += w)
		{
			frames.emplace_back(RectI(j, i, w, h));
		}
	}
}

void Animation::Update(float dt)
{
	time += dt;
	if (time >= holdTime)
	{
		time = 0;
		curFrame++;
		if (curFrame >= int(frames.size()))
		{
			curFrame = 0;
		}
	}
}

void Animation::Draw(Vec2_<int> pos,Graphics & gfx)
{
	Color ch = chroma;
	gfx.DrawSprite(pos.x, pos.y, frames[curFrame], *source, [ch](Color c, int x, int y,  Graphics& gfx){
		if (ch != c)
		{
			gfx.PutPixel(x, y, c);
		}
	});
}

bool Animation::FinishedCycle()
{
	if (curFrame == frames.size()-1)
	{
		return true;
	}
	return false;
}

void Animation::ResetCycle()
{
	curFrame = 0;
}

RectI Animation::GetRectToRemove()const
//gets the leftovers the sides and returns a rect containing all those leftovers to be removed later or gets ignored
{
	RectI originRect = this->frames[this->curFrame];

	int top = 0, left = 0, bottom = 0, right = 0;

	bool found = false;				//terminating the for loops if found
	
	//left
	for (int i = 0; i < originRect.GetWidth()&&!found; i++)
	{
		for (int j = 0; j < originRect.GetHeight()&&!found; j++)
		{
			if (this->source->GetPixel(originRect.GetTopLeft().x + i, originRect.GetTopLeft().y + j)!=this->chroma)
			{
				found = true;
				left = i;
			}
		}
	}

	//top
	found = false;

	for (int j = 0; j < originRect.GetHeight() && !found; j++)
	{
		for (int i = 0; i < originRect.GetWidth() && !found; i++)
		{
			if (this->source->GetPixel(originRect.GetTopLeft().x + i, originRect.GetTopLeft().y + j) != this->chroma)
			{
				found = true;
				top = j;
			}
		}
	}

	//right
	found = false;

	for (int i = 0; i < originRect.GetWidth() && !found; i++)
	{
		for (int j = 0; j < originRect.GetHeight() && !found; j++)
		{
			if (this->source->GetPixel(originRect.GetBotoomRight().x - 1 - i, originRect.GetBotoomRight().y - 1 - j) != this->chroma)
			{
				found = true;
				right = i;
			}
		}
	}

	if (!found)
	{

	}

	//bottom
	found = false;

	for (int j = 0; j < originRect.GetHeight() && !found; j++)
	{
		for (int i = 0; i < originRect.GetWidth() && !found; i++)
		{
			if (this->source->GetPixel(originRect.GetBotoomRight().x - 1 - i, originRect.GetBotoomRight().y - 1 - j) != this->chroma)
			{
				found = true;
				bottom = j;
			}
		}
	}

	return RectI(Vec2_<int>(left, top), Vec2_<int>(right, bottom));
}


