#include "Vec4.h"
#include "Vec3.h"
#include "Vec2.h"



Vec4::Vec4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vec4::Vec4(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Vec4::Vec4(const Vec4 & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}


Vec4::Vec4(const Vec3 & other, float _w)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = _w;
}

Vec4::Vec4(const Vec2 & other, float _z, float _w)
{
	x = other.x;
	y = other.y;
	z = _z;
	w = _w;
}

Vec4::~Vec4()
{
}
