#include "PhysicsMat.h"


PhysicsMat::PhysicsMat(Rect<float> r, float f, std::string filename, Color ch)
	:
	rect(r),
	fraction(f),
	texture((SpriteManager::GetManager().Get(filename))),
	chroma(ch),
	drawRect(texture->GetRect())
{
	color = 0;
}

PhysicsMat::PhysicsMat(Rect<float> r, float f, std::string filename, Rect<int> toUse, Color ch )
	:
	rect(r),
	fraction(f),
	texture(SpriteManager::GetManager().Get(filename)),
	chroma(ch),
	drawRect(toUse)
{
	color = 0;
}

PhysicsMat::PhysicsMat(Rect<float> r, float f, Color c)
	:
	rect(r),
	fraction(f),
	color(c),
	drawRect(0,0,0,0)
{
	texture = nullptr;
}

bool PhysicsMat::IsColiding(Rect<float> obj)
{
	return this->rect.IsColliding(obj);
}

void PhysicsMat::Draw(Graphics & gfx)
{
	if (texture != nullptr)
	{
		gfx.DrawSprite(rect.GetTopLeft().x, rect.GetTopLeft().y,drawRect, *texture, [this](Color c, int x, int y, Graphics& gfx) 
		{
			if (c != chroma)
			{
				gfx.PutPixel(x, y, c);
			}
		});
	}
	else
	{
		gfx.DrawRect(Cast(rect), color);
	}
}

float PhysicsMat::GetFraction()
{
	return fraction;
}

const Vec2_<int>& PhysicsMat::GetPosition() const
{
	return Cast(this->rect.GetTopLeft());
}

RectI PhysicsMat::GetRect() const
{
	return Cast(rect);
}

void PhysicsMat::SetPosition(Vec2_<int> pos)
{
	Rect<int> r(pos.x, pos.y, this->rect.GetWidth(), this->rect.GetHeight());
	this->rect = Cast(r);
}
