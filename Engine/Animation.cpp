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
	for (int i = start.y; i < stop.y; i += h)
	{
		for (int j = start.x; j < stop.x; j += w)
		{
			frames.emplace_back(RectI( j,i,w,h ));
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
		if (curFrame >= frames.size())
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
