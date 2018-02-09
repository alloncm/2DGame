#pragma once

#include"Vec2.h"

//template class rect
template<typename T>
class Rect
{
private:
	Vec2_<T> tLeft;
	Vec2_<T> bRight;

public:
	Rect(T x, T y, T w, T h)
		:
		tLeft({ x,y }),
		bRight({ x + w,y + h })
	{}

	Rect(Vec2_<T> tLeft, Vec2_<T> bRight)
		:
		tLeft(tLeft),
		bRight(bRight)
	{}

	Rect()=default;

	Rect(const Rect& r) = default;

	Rect(T width, T height, Vec2_<T> center)
		:
		tLeft({ center.x - width / 2,center.y - height / 2 }),
		bRight({ center.x + width / 2,center.y + height / 2 })
	{}
	Rect& operator=(const Rect<T>& r)
	{
		this->tLeft = r.tLeft;
		this->bRight = r.bRight;
		return *this;
	}
	T GetWidth()const
	{
		return bRight.x - tLeft.x;
	}
	T GetHeight()const
	{
		return bRight.y - tLeft.y;
	}
	const Vec2_<T>& GetTopLeft()const
	{
		return this->tLeft;
	}
	const Vec2_<T>& GetBotoomRight()const
	{
		return this->bRight;
	}
	bool IsInside(const Vec2_<T>& l)const
	//not working as intend 
	//needs to fix
	{
		if ((l.x >= tLeft.x&&l.x <= bRight.x) && (l.y >= tLeft.y&&l.y <= bRight.y))
		{
			return true;
		}
		return false;
	}
	bool IsColliding(const Rect<T>& l)const
	{
		if (IsInside(l.tLeft)||l.IsInside(tLeft))
		{
			return true;
		}
		if (IsInside(l.bRight)||l.IsInside(bRight))
		{
			return true;
		}
		if (IsInside({ l.tLeft.x,l.bRight.y })||l.IsInside({ tLeft.x,bRight.y }))
		{
			return true;
		}
		if (IsInside({ l.bRight.x,l.tLeft.y })||l.IsInside({ bRight.x,tLeft.y }))
		{
			return true;
		}
		return false;
	}
	static Rect<int> GetRectI(Vec2_<T> v1, Vec2_<T> v2)
	{
		return RectI({ (int)v1.x,(int)v1.y }, { (int)v2.x,(int)v2.y});
	}

};
typedef Rect<int> RectI;