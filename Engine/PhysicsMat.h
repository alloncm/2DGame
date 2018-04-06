#pragma once

#include"Graphics.h"
#include"Rect.h"
#include"Surface.h"
#include"SpritesManager.h"

class PhysicsMat
{
protected:
	Rect<float> rect;
	float fraction;
	Surface* texture;			//optional
	Color chroma;
	Color color;				//if dont have Textrue use color
	Rect<int> drawRect;
public:
	
	PhysicsMat(Rect<float> r, float f, std::string filename,Color ch = Colors::Magenta);
	PhysicsMat(Rect<float> r, float f, std::string filename, Rect<int> toUse, Color ch = Colors::Magenta);
	PhysicsMat(Rect<float> r, float f,Color c);
	bool IsColiding(Rect<float> obj);
	virtual void Draw(Graphics& gfx);
	float GetFraction();
	const Vec2_<int>& GetPosition()const;
	RectI GetRect()const;
	void SetPosition(Vec2_<int> pos);
	virtual ~PhysicsMat()=default;
};
