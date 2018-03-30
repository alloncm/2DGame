#pragma once
#include"Surface.h"
#include"SpritesManager.h"
#include<vector>
#include"Vec2.h"
#include"Graphics.h"
#include<algorithm>
class Animation
{
public:
	Animation(std::string source, float HoldTime, int width, int height, Vec2_<int>start, Vec2_<int>stop, Color ch);
	Animation(std::string source, float HoldTime, int width, int height, Color ch);
	void Update(float dt);
	void Draw(Vec2_<int> pos, Graphics& gfx);
	bool FinishedCycle();
	void ResetCycle();
	Rect<int> GetRectToDel()const;
private:
	RectI GetRectToRemove(Rect<int> origin) const;
private:
	Color chroma;
	Surface* source;
	std::vector<RectI> frames;
	int curFrame;
	float holdTime;
	float time;
	int width;
	int height;
	Rect<int> rectToDel;
};