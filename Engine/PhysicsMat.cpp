#include "PhysicsMat.h"

PhysicsMat::PhysicsMat(Rect<float> r, float f, std::string  filename)
	:
	rect(r),
	fraction(f),
	texture(SpriteManager::GetManager().Get(filename))
{
	color = 0;
}

PhysicsMat::PhysicsMat(Rect<float> r, float f, Color c)
	:
	rect(r),
	fraction(f),
	color(c)
{
	texture = nullptr;
}

bool PhysicsMat::IsColiding(Rect<float> obj)
{
	return this->rect.IsColliding(obj);
}

void PhysicsMat::Draw(Graphics & gfx)
{
	if (this->texture != nullptr)
	{
		gfx.DrawSprite(rect.GetTopLeft().x,rect.GetTopLeft().y,*texture,[](Color c,int x,int y,Graphics& gfx){
			gfx.PutPixel(x, y, c);
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
