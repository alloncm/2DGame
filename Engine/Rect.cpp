#include"Rect.h"

Rect<int> Cast(Rect<float> r)
{
	return RectI(Cast(r.tLeft), Cast(r.bRight));
}

Rect<float> Cast(Rect<int> r)
{
	return Rect<float>(Cast(r.tLeft), Cast(r.bRight));
}