#include"Vec2.h"

Vec2_<int> Cast(Vec2_<float> v)
{
	return Vec2_<int>(int(v.x), int(v.y));
}

Vec2_<float> Cast(Vec2_<int> v)
{
	return Vec2_<float>(float(v.x), float(v.y));
}