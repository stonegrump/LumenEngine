#include "Vec3.h"
#include <cmath>
#include "Vec2.h"
#include "Vec4.h"


Vec3::Vec3()
{
	x = y = z = 0;
}

Vec3::Vec3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vec3::Vec3(const Vec4 & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vec3::Vec3(const Vec3 & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vec3::Vec3(const Vec2 & other, float _z)
{
	x = other.x;
	y = other.y;
	z = z;
}

float Vec3::Length() const {
	return  sqrt((x * x) + (y * y) + (z * z));
}

float Vec3::Dot(const Vec3 &other) {
	return (x * other.x) + (y * other.y) + (z * other.z);
}

Vec3 Vec3::Cross(const Vec3 & other) {
	return Vec3((y * other.z) - (other.y * z), (other.x * z) - (x * other.z), (x * other.y) - (other.x * y));
}
Vec3 * Vec3::PCross(const Vec3 * const other) {
	return new Vec3((y * other->z) - (other->y * z), (x * other->z) - (other->x * z), (x * other->y) - (other->x * y));
}

#pragma region Operators

Vec3 & Vec3::operator=(const Vec3 & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

Vec3 & Vec3::operator=(const Vec3 * const other)
{
	x = other->x;
	y = other->y;
	z = other->z;
	return *this;
}

bool Vec3::operator==(const Vec3 & other)
{
	if (x == other.x && y == other.y && z == other.z)
		return true;
	else
		return false;
}

Vec3 & Vec3::operator-()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

Vec3 & Vec3::operator+=(const Vec3 & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vec3 & Vec3::operator+=(float value)
{
	x += value;
	y += value;
	z += value;
	return *this;
}

Vec3 & Vec3::operator-=(const Vec3 & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vec3 & Vec3::operator-=(float value)
{
	x -= value;
	y -= value;
	z -= value;
	return *this;
}

Vec3 & Vec3::operator/=(float value)
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

#pragma endregion

Vec3 &Vec3::operator*=(float value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}




Vec3::~Vec3()
{
}
